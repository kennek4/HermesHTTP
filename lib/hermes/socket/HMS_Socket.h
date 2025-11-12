#pragma once

#include "utility/HMS_pch.h"

namespace HMS {

constexpr inline int MAX_CONNECTIONS = 1000;

enum class SocketType {
    OTHER = 0,
    TCP,
    UDP,
};

struct Socket {
    int fd {-1};
    sockaddr_in address;
    socklen_t length;
};

void socketError(int socketFd);

void openSocket(Socket &_socket, SocketType _socketType, const char *ip,
                int port);
void closeSocket(const Socket &_socket);

Socket getClient(int serverFd);

}; // namespace HMS
