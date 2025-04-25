#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main(void) {
  int sock;
  char buffer[2048];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Error! Cannot create a socket";
    return -1;
  }

  int port;

  std::cout << "Enter server's port: ";
  std::cin >> port;
  std::cin.ignore();

  sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int connect_result =
      connect(sock, (sockaddr*)&server_addr, sizeof(server_addr));
  if (connect_result == -1) {
    std::cerr << "Error! Connection is failed." << std::endl;
    return -2;
  }

  socklen_t len = sizeof(server_addr);
  int n, time{0};

  // Паттерн клиента:
  // 1. socket()
  // 2. connect()
  // 3. send()
  // 4. recv()
  // 5. close()

  std::string line;
  std::cout << "Enter iterator value: ";
  getline(std::cin, line);
  time = std::atoi(line.c_str());

  if (time == 0) {
    std::cerr << "Incorrect iterator." << std::endl;
    close(sock);
    return -1;
  }
  for (int i = 0; i < time; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(time));
    int result = send(sock, line.c_str(), line.size(), 0);

    if (result == -1) {
      std::cerr << "Error! Cannot send a message!" << std::endl;
      break;
    }

    n = recv(sock, buffer, 2048, 0);

    std::cout << std::string(buffer, n) << std::endl;
  }
  close(sock);
  return 0;
}
