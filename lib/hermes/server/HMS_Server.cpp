#include "HMS_Server.h"
#include "socket/HMS_Socket.h"

namespace HMS {
void Server::run() {
    auto getIP = []() -> const char * {
        char hostName[HOST_NAME_MAX];
        gethostname(hostName, HOST_NAME_MAX);

        struct hostent *host = gethostbyname(hostName);
        return inet_ntoa(
            *reinterpret_cast<struct in_addr *>(host->h_addr_list[0]));
    };

    const char *ip = getIP();
    SocketProps socketProps {
        .pSocket = &mSocket, .type = SocketType::TCP, .ip = ip, .port = 8080};

    openSocket(socketProps);
    assert(mSocket.fd != -1);

    Socket client {};
    bool isFinished = false;

    while (!isFinished) {
        client = getClient(mSocket.fd);
        mThreadPool.queueJob(
            std::make_tuple(&HTTP::processRequest, mSocket, client));
    };
};

void Server::stop() {
    if (!mThreadPool.isBusy()) {
        mThreadPool.shutdown();
        closeSocket(mSocket);
    };
};
}; // namespace HMS
