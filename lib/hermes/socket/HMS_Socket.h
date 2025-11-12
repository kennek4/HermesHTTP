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

struct SocketProps {
    Socket *pSocket {nullptr};
    SocketType type {SocketType::TCP};
    const char *ip {"localhost"};
    int port {8080};
};

void socketError(int socketFd);

void openSocket(SocketProps props);
void closeSocket(const Socket &_socket);

Socket getClient(int serverFd);

}; // namespace HMS
