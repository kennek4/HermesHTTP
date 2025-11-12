#include "HMS_Http.h"

namespace HMS {
namespace HTTP {
void processRequest(const Socket &server, const Socket &client) {
    char buffer[1024];
    ssize_t bytesRecieved = recv(client.fd, buffer, sizeof(buffer), 0);
    if (bytesRecieved < 0) {
        std::cout << "Failed Connection Attempt from IP "
                  << inet_ntoa(client.address.sin_addr) << "\n";
        std::cout << "Error: " << strerror(errno) << "\n\n";
        return;
    };

    std::cout << "Connection from IP " << inet_ntoa(client.address.sin_addr)
              << "\n";

    constexpr const char *response =
        "HTTP/1.1 200 OK\r\nContent-Type: text\r\nContent-Length: "
        "27\r\n\r\n<h1> This is a H1 Tag </h1>";
    constexpr size_t responseLen = std::char_traits<char>::length(response);

    send(client.fd, response, responseLen, 0);
    close(client.fd);
};

void sendResponse(const Socket &server, const Socket &client) {

};
} // namespace HTTP
}; // namespace HMS
