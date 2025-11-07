#include <Hermes.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Create server socket
    HMS::TCPSocket *serverSocket = new HMS::TCPSocket(8080);

    int x;
    std::cout << "Type a num: ";
    std::cin >> x;

    delete serverSocket;
}
