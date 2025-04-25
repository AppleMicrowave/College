#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
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
  char buffer[2048];  // поле для получения ОТВЕТА
  sockaddr_in server_addr;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    std::cerr << "Error! Cannot create a socket." << std::endl;
    return -1;
  }

  std::string ip;
  int port;
  
  std::cout << "Enter server IP & Port: ";
  std::cin >> ip >> port;
  std::cin.ignore();

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

  socklen_t len = sizeof(server_addr);
  int n, time{0}, flag{1};

  while (flag) {
    std::string line;

    std::cout << "Enter iterator value: ";
    getline(std::cin, line);

    time = std::atoi(line.c_str());
    for (int i = 0; i < 2; ++i) {
      std::this_thread::sleep_for(std::chrono::seconds(time));

      if (time == 0 && line != "quit") {
        std::cerr << "Incorrect iterator." << std::endl;
        break;
      }

      int result = sendto(sock, line.c_str(), line.size() + 1, MSG_CONFIRM,
                          (const sockaddr*)&server_addr, sizeof(server_addr));
      if (line == "quit") {
        flag = 0;
        break;
      }

      if (result == -1) {
        std::cerr << "Error! Cannot send a message!" << std::endl;
        flag = 0;
        break;
      }

      n = recvfrom(sock, buffer, 2048, MSG_WAITALL, (sockaddr*)&server_addr,
                   &len);

      std::cout << "Server: " << std::string(buffer, n) << std::endl;
    }
  }

  close(sock);

  return 0;
}
