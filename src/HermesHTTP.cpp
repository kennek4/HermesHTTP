#include "HermesHTTP.h"
#include "socket/HMS_Socket.h"
#include <cassert>
#include <tuple>

namespace HMS {
namespace HTTP {
void processRequest(const Socket &server, const Socket &client) {
    char buffer[1024];
    ssize_t bytesRecieved = recv(client.fd, buffer, sizeof(buffer), 0);
    if (bytesRecieved < 0) {
        std::cout << "Failed Connection Attempt from IP "
                  << inet_ntoa(client.address.sin_addr) << "\n";
        std::cout << "Error # " << errno << "\n";
        std::cout << "Error: " << strerror(errno) << "\n\n";
        return;
    };

    std::cout << "Connection from IP " << inet_ntoa(client.address.sin_addr)
              << "\n";

    const char *response  = "<h1> This is a H1 Tag </h1>";

    std::string res       = "HTTP/1.1 200 OK\r\n";
    res                  += "Content-Type: text\r\n";
    res += "Content-Length: " + std::to_string(strlen(response)) + "\r\n";
    res += "\r\n";
    res += response;

    send(client.fd, res.c_str(), res.length(), 0);
    close(client.fd);
};

void sendResponse(const Socket &server, const Socket &client) {

};
} // namespace HTTP

void Server::run() {
    Socket client {};
    bool isFinished = false;

    openSocket(mSocket, SocketType::TCP);

    assert(mSocket.fd != -1);

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
