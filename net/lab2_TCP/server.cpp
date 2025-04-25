#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <string>

// Функция для завершения зомби-процессов
void reaper(int sig) {
  int status;
  while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}

int main(void) {
  // конвертировать sockaddr в sockaddr_in !!!

  int listening;
  char buffer[2048];
  // создание сокета
  listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening == -1) {
    std::cerr << "Error! Cannot create a socket." << std::endl;
    return -1;
  }

  // создание структуры сервера
  sockaddr_in hint;
  hint.sin_family = AF_INET;  // протокол IPv4
  hint.sin_port = htons(0);   // автоматическая установка порта
  hint.sin_addr.s_addr = INADDR_ANY;

  // привязка сокета к порту
  if (bind(listening, (const sockaddr *)&hint, sizeof(hint)) == -1) {
    std::cerr << "Error! Can't bind socke.";
    return -2;
  }

  socklen_t len = sizeof(hint);
  getsockname(listening, (sockaddr *)&hint, &len);
  std::cout << "Port: " << ntohs(hint.sin_port) << std::endl;

  // прослушка порта
  if (listen(listening, SOMAXCONN) == -1) {
    std::cerr << "Error! Can't listen.";
    return -3;
  }

  // создание структуры клиента
  sockaddr_in client;
  socklen_t client_size = sizeof(client);
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];

  // Установка обработчика сигнала для завершения зомби-процессов
  signal(SIGCHLD, reaper);

  while (true) {
    // Принятие запроса от клиента
    int client_socket = accept(listening, (sockaddr *)&client, &client_size);
    if (client_socket == -1) {
      std::cerr << "Error! Problem with client connecting.";
      continue;
    }

    // Создание нового процесса для обработки клиента
    int f = fork();
    if (f == 0) {
      // Дочерний процесс
      close(listening);

      memset(host, 0, NI_MAXHOST);
      memset(service, 0, NI_MAXSERV);

      int result = getnameinfo((sockaddr *)&client, sizeof(client), host,
                               NI_MAXHOST, service, NI_MAXSERV, 0);
      if (result) {
        std::cout << host << " connected on " << service;
      } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port)
                  << std::endl;
      }

      // TCP
      int n;
      while (true) {
        n = recv(client_socket, buffer, 2048, 0);
        if (n == -1) {
          std::cerr << "Error! Connection is failed.";
          break;
        }

        std::string message(buffer, 0, n);
        std::string ip = inet_ntoa(client.sin_addr);
        int port = ntohs(client.sin_port);
        std::string result("Message: " + message + " | From: " + ip + ":" +
                           std::to_string(port) + '\n');

        if (message == "quit") {
          std::cout << "Client requested to quit." << std::endl;
          break;  // Завершение только текущего клиентского процесса
        }

        if (send(client_socket, result.c_str(), result.size(), 0) == -1) {
          std::cerr << "ERROR! Somehow i can't respond to client.."
                    << std::endl;
        }
      }

      close(client_socket);
      exit(0);
    } else if (f > 0) {
      // Родительский процесс
      close(client_socket);
    } else {
      std::cerr << "Error! Fork failed." << std::endl;
    }
  }

  return 0;
}
