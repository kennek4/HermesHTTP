#pragma once

#include <netinet/in.h>
#include <print>
#include <sys/socket.h>

namespace HMS {
class TCPSocket {
  private:
    int mSocket;
    int mClient;
    sockaddr_in mAddress;

  public:
    explicit TCPSocket(uint16_t port);
    ~TCPSocket();
};
}; // namespace HMS
