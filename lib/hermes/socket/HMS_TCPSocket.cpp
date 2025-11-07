#include "HMS_TCPSocket.h"
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <print>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace HMS {
TCPSocket::TCPSocket(uint16_t port) {
    mSocket                  = socket(AF_INET, SOCK_STREAM, 0);
    mAddress.sin_family      = AF_INET;
    mAddress.sin_port        = htons(port);
    mAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(mSocket, reinterpret_cast<struct sockaddr *>(&mAddress),
             sizeof(mAddress)) == -1) {
        close(mSocket);
        throw std::runtime_error("Failed to bind socket to address!");
    };

    if (listen(mSocket, 2) == -1) {
        close(mSocket);
        throw std::runtime_error("Failed to start listening on server socket!");
    };

    std::println("Started listening on: {}:{}", inet_ntoa(mAddress.sin_addr),
                 port);

    sockaddr_in clientAddr;
    socklen_t clientAddrSize;
    mClient = accept(mSocket, reinterpret_cast<struct sockaddr *>(&clientAddr),
                     &clientAddrSize);

    std::println("Client Connected from IP Address: {}",
                 inet_ntoa(clientAddr.sin_addr));

    // recieving data
    char buffer[1024]     = {0};
    ssize_t bytesRecieved = recv(mClient, buffer, sizeof(buffer) - 1, 0);
    buffer[bytesRecieved] = '\0';
    std::println("Client Recieved Data: {}", buffer);

    // Send HTTP response
    const char *response =
        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
        "<html><h1>HTML Response</h1><p>The server works!</p></html>";
    send(mClient, response, strlen(response), 0);
};

TCPSocket::~TCPSocket() {
    close(mSocket);
    close(mClient);
};
}; // namespace HMS
