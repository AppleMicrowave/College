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

#include <iostream>

int setup_server(short port, int buf) {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    std::cerr << "Error! Cannot create socket." << std::endl;
    return -1;
  }

  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  socklen_t server_size = sizeof(server_addr);

  if (bind(server_socket, (const sockaddr *)&server_addr, server_size) == -1) {
    std::cerr << "Error! Cannot bind a socket." << std::endl;
    return -2;
  }
  if (listen(server_socket, buf) == -1) {
    std::cerr << "Error! Cannot listen to port." << std::endl;
    return -3;
  }

  getsockname(server_socket, (sockaddr *)&server_addr, &server_size);
  std::cout << "Port: " << ntohs(server_addr.sin_port) << std::endl;

  return server_socket;
}

int establish_connection(int server_socket) {
  sockaddr_in client_addr;
  socklen_t client_size = sizeof(client_addr);

  int client_socket =
      accept(server_socket, (sockaddr *)&client_addr, &client_size);
  if (client_socket == -1) {
    std::cerr << "Error! Cannot accept request from client." << std::endl;
    return -4;
  }

  return client_socket;
}

void handle_connection(int socket, fd_set &current_sockets) {
  char buffer[2048];
  int n = recv(socket, buffer, sizeof(buffer), 0);
  if (n <= 0) {
    if (n == 0) {
      std::cout << "Client disconnected." << std::endl;
    } else {
      std::cerr << "Error! Connection is failed." << std::endl;
    }
    close(socket);
    FD_CLR(socket, &current_sockets);
    return;
  }

  std::string message(buffer, 0, n);
  std::string result("Message: " + message + " from client #" +
                     std::to_string(socket) + '\n');
  std::cout << result << std::endl;
  std::string answer{"SERVER: - Message received."};
  if (send(socket, answer.c_str(), answer.size(), 0) == -1) {
    std::cerr << "ERROR! Somehow I can't respond to client.." << std::endl;
  }
}

int main(void) {
  int server_socket = setup_server(0, SOMAXCONN);
  if (server_socket < 0) return -1;

  fd_set current_sockets, ready_sockets;
  FD_ZERO(&current_sockets);
  FD_SET(server_socket, &current_sockets);

  while (true) {
    ready_sockets = current_sockets;

    if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) {
      std::cerr << "Select error!" << std::endl;
      return -5;
    }

    for (int i = 0; i < FD_SETSIZE; ++i) {
      if (FD_ISSET(i, &ready_sockets)) {
        if (i == server_socket) {
          int client_socket = establish_connection(server_socket);
          if (client_socket != -1) {
            FD_SET(client_socket, &current_sockets);
          }
        } else {
          handle_connection(i, current_sockets);
        }
      }
    }
  }

  return 0;
}