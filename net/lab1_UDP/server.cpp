#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

int main(void) {
  int sock;
  char buffer[2048];  // поле для получения СООБЩЕНИЯ
  sockaddr_in server_addr, client_addr;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    std::cerr << "Error! Cannot create a socket." << std::endl;
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(0);  // если 0, то ОС ищет первый свободный порт
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int result = bind(sock, (const sockaddr*)&server_addr, sizeof(server_addr));
  if (result == -1) {
    std::cerr << "Error! Cannot bind to a port: 54000" << std::endl;
    return -2;
  }

  socklen_t len = sizeof(server_addr);

  getsockname(sock, (sockaddr*)&server_addr, &len);  // (новый порт)
  std::cout << "Port: " << ntohs(server_addr.sin_port) << std::endl;
  // net to host перевод порта

  int n;

  //UDP
  while (true) {
    n = recvfrom(sock, buffer, 2048, MSG_WAITALL, (sockaddr*)&client_addr,
                 &len);

    std::string message(buffer, 0, n);
    std::string ip = inet_ntoa(client_addr.sin_addr);
    int port = ntohs(client_addr.sin_port);
    std::string result("Message: " + message + " | From: " + ip + ":" +
                       std::to_string(port) + '\n');

    if (message == "quit") {
      std::cout << "Shutdown server.." << std::endl;
      break;
    }

    // const char* answer = "Message received.";

    sendto(sock, result.c_str(), result.size() + 1, MSG_CONFIRM,
           (const sockaddr*)&client_addr, len);
  }

  close(sock);

  return 0;
}