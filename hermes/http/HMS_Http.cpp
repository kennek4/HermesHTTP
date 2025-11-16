#include "HMS_Http.h"
#include <unistd.h>

namespace HMS {
namespace HTTP {

Request getRequest(std::string &&rl) {
    Request request;

    std::string requestLine = std::move(rl);
    std::string::size_type pos;

    pos = requestLine.find(" ");
    std::string method {requestLine.substr(0, pos)};
    requestLine.erase(0, pos + 1);

    if (method == "GET") {
        request.method = RequestMethod::GET;
    } else if (method == "POST") {
        request.method = RequestMethod::POST;
    } else {
        request.method = RequestMethod::NOT_SUPPORTED;
    };

    pos         = requestLine.find(" ");
    request.url = requestLine.substr(0, pos);
    requestLine.erase(0, pos);

    return request;
};

void handleConnection(const Socket &server, const Socket &client) {
    Request request;
    Response response;
    char buffer[1024];

    ssize_t bytesRecieved = recv(client.fd, buffer, sizeof(buffer), 0);
    if (bytesRecieved < 0) {
        std::cout << "Failed Connection Attempt from IP "
                  << inet_ntoa(client.address.sin_addr) << "\n";
        std::cout << "Error: " << strerror(errno) << "\n\n";
        return;
    };

    std::stringstream reqs(buffer);
    std::string reqLine;
    std::getline(reqs, reqLine);

    // NOTE: Invalid request line
    if (reqLine.empty()) {
        response = {
            .code        = HTTP::Code::BAD_REQUEST,
            .contentType = HTTP::ContentType::TEXT_PLAIN,
            .content     = {.data = "Bad Request", .length = 11}
        };

        std::string responseAsString = response.toString();
        send(client.fd, responseAsString.c_str(), responseAsString.size(), 0);
        close(client.fd);
        return;
    };

    request = getRequest(std::move(reqLine));
    std::cout << "Connection from IP " << inet_ntoa(client.address.sin_addr)
              << "\n";

    if (strcmp(request.url.c_str(), "/home") == 0) {
        response = {
            .code        = HTTP::Code::OK,
            .contentType = HTTP::ContentType::TEXT_PLAIN,
            .content     = {.data = "Hello, Home!", .length = 12}
        };

    } else if (strcmp(request.url.c_str(), "/info") == 0) {
        response = {
            .code        = HTTP::Code::OK,
            .contentType = HTTP::ContentType::TEXT_PLAIN,
            .content     = {.data = "Hello, Info!", .length = 12}
        };

    } else {
        response = {
            .code        = HTTP::Code::NOT_FOUND,
            .contentType = HTTP::ContentType::TEXT_PLAIN,
            .content     = {.data = "Content Not Found", .length = 17}
        };
    }

    std::string responseAsString = response.toString();
    send(client.fd, responseAsString.c_str(), responseAsString.size(), 0);
    close(client.fd);
};

void sendResponse(const Socket &server, const Socket &client) {

};
} // namespace HTTP
}; // namespace HMS
