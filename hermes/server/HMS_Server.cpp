#include "HMS_Server.h"
#include "socket/HMS_Socket.h"

namespace HMS {
void Server::init() {
    SocketProps socketProps {.pSocket = &mSocket};
    std::cerr << "Loading default config...\n";

    struct in_addr ip;
    const int retVal = inet_aton("127.0.0.1", &ip);
    assert(retVal == 1);

    socketProps.ip = ip;

    openSocket(socketProps);
    assert(mSocket.fd != -1);
};

void Server::init(const char *configFilePath) {
    SocketProps socketProps {.pSocket = &mSocket};

    std::cerr << "Loading " << configFilePath << "\n";

    if (strcmp(configFilePath, "") == 0) {
        throw std::runtime_error("The provided config filepath is empty!");
    };

    if (!std::filesystem::exists(configFilePath)) {
        throw std::runtime_error("The provided config filepath is not valid!");
    };

    YAML::Node yamlData = YAML::LoadFile(configFilePath);
    if (!yamlData["network"] && !yamlData["network"]["type"] &&
        !yamlData["network"]["ip"] && !yamlData["network"]["port"])
        throw std::runtime_error("Could not read the provided config file!");

    int type = yamlData["network"]["type"].as<int>();

    // NOTE: Check if type is in SocketType enum
    if (type < 0 || type > 2)
        throw std::runtime_error("The value for, type, in the provided "
                                 "config file is out of bounds.");

    struct in_addr ip;
    int ipReturnCode =
        inet_aton(yamlData["network"]["ip"].as<std::string>().c_str(), &ip);

    // NOTE: inet_aton returns zero on error
    if (ipReturnCode == 0)
        throw std::runtime_error("The value for, ip, in the provided "
                                 "config file is not a valid IPv4 address.");

    int port = yamlData["network"]["port"].as<int>();

    // NOTE:Check for valid HTTP port
    if (port != 80 && port != 8008 && port != 8080)
        throw std::runtime_error("The value for, port, in the provided "
                                 "config file is out of bounds.");

    socketProps.type = static_cast<SocketType>(type);
    socketProps.ip   = ip;
    socketProps.port = htons(port);

    openSocket(socketProps);
    assert(mSocket.fd != -1);
};

void Server::shutdown() {
    mThreadPool.shutdown();
    closeSocket(mSocket);
};

void Server::run() {
    Socket client {};
    bool isFinished = false;

    while (!isFinished) {
        client = getClient(mSocket.fd);
        mThreadPool.queueJob(
            std::make_tuple(&HTTP::handleConnection, mSocket, client));
    };
};
}; // namespace HMS
