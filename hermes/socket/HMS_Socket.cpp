#include "HMS_Socket.h"

void socketError(int socketFd) {
    close(socketFd);
    std::string errMsg  = "Error: ";
    errMsg             += strerror(errno);
    errMsg             += "\n";
    throw std::runtime_error(errMsg);
};

namespace HMS {
void openSocket(SocketProps props) {
    props.pSocket->fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(props.pSocket->fd != -1);

    if (props.pSocket->fd == -1)
        socketError(props.pSocket->fd);

    props.pSocket->address.sin_family = AF_INET; // IPv4
    props.pSocket->address.sin_addr   = props.ip;
    props.pSocket->address.sin_port   = props.port; // Port 8080

    int opt                           = 1;
    setsockopt(props.pSocket->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(props.pSocket->fd,
             reinterpret_cast<struct sockaddr *>(&props.pSocket->address),
             sizeof(props.pSocket->address)) == -1)
        socketError(props.pSocket->fd);

    if (listen(props.pSocket->fd, MAX_CONNECTIONS) == -1)
        socketError(props.pSocket->fd);

    std::cout << "Started listening on "
              << inet_ntoa(props.pSocket->address.sin_addr) << ":8080"
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
