#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

struct args {
  int socket;
  sockaddr_in addr;
};

void* funky_town(void* arg) {
  args* args = static_cast<struct args*>(arg);
  sockaddr_in client = args->addr;
  int client_socket = args->socket;

  char buf[4096];

  char host[NI_MAXHOST];
  char service[NI_MAXSERV];

  memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);

  int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST,
                           service, NI_MAXSERV, 0);
  if (result) {
    std::cout << host << " connected on " << service << std::endl;
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected on " << ntohs(client.sin_port)
              << std::endl;
  }

  int n;
  while (true) {
    // Ожидание сообщения от клиента
    std::fill(buf, buf + 4096, 0);
    n = recv(client_socket, buf, 4096, 0);
    if (n == -1) {
      std::cout << "Buggy-Boo: There's no message from client." << std::endl;
      return (void*)-1;
    }

    std::string message(buf, 0, n);
    std::string ip = inet_ntoa(client.sin_addr);
    int port = ntohs(client.sin_port);
    std::string result("Message: " + message + " | From: " + ip + ":" +
                       std::to_string(port) + '\n');

    if (message == "quit") {
      std::cout << "Client requested to quit." << std::endl;
      break;
    }

    if (send(client_socket, result.c_str(), result.size(), 0) == -1) {
      std::cerr << "ERROR! Somehow i can't respond to client.." << std::endl;
      break;
    }
  }

  delete args;
  return NULL;
}

int main(void) {
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == -1) {
    std::cerr << "Error! Can't create socket." << std::endl;
    return -1;
  }

  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(0);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(listening, (const sockaddr*)&server_addr, sizeof(server_addr)) ==
      -1) {
    std::cout << "Error! Can't bind to the port." << std::endl;
    return -2;
  }

  socklen_t len = sizeof(server_addr);
  getsockname(listening, (sockaddr*)&server_addr, &len);
  std::cout << "Port: " << ntohs(server_addr.sin_port) << std::endl;

  if (listen(listening, SOMAXCONN) == -1) {
    std::cout << "Error! Can't listen to the port." << std::endl;
    return -3;
  }

  // Работа с клиентом
  sockaddr_in client;
  socklen_t client_size = sizeof(client);

  int* result;
  while (true) {
    int client_socket = accept(listening, (sockaddr*)&client, &client_size);
    if (client_socket == -1) {
      std::cout << "Error! Can't accept client." << std::endl;
      return -4;
    }

    args* arg = new args{client_socket, client};
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, funky_town, arg);
    pthread_detach(tid);
  }

  close(listening);
  return 0;
}
