#include "HMS_Socket.h"
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

namespace HMS {

void socketError(int socketFd) {
    close(socketFd);
    std::string errMsg  = "Error: ";
    errMsg             += strerror(errno);
    errMsg             += "\n";
    throw std::runtime_error(errMsg);
};

void openSocket(Socket &_socket, SocketType _socketType, const char *ip,
                int port) {
    _socket.fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(_socket.fd != -1);

    if (_socket.fd == -1)
        socketError(_socket.fd);

    _socket.address.sin_family      = AF_INET; // IPv4
    _socket.address.sin_addr.s_addr = inet_addr(ip);
    _socket.address.sin_port        = htons(port); // Port 8080

    int opt                         = 1;
    setsockopt(_socket.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(_socket.fd, reinterpret_cast<struct sockaddr *>(&_socket.address),
             sizeof(_socket.address)) == -1)
        socketError(_socket.fd);

    if (listen(_socket.fd, MAX_CONNECTIONS) == -1)
        socketError(_socket.fd);

    std::cout << "Started listening on " << inet_ntoa(_socket.address.sin_addr)
              << ":8080"
              << "\n";
};

void closeSocket(const Socket &_socket) { close(_socket.fd); };

Socket getClient(int serverFd) {
    Socket client;

    client.fd =
        accept(serverFd, reinterpret_cast<struct sockaddr *>(&client.address),
               &client.length);
    assert(client.fd != -1);

    return client;
};

}; // namespace HMS
