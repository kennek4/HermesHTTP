#pragma once

#include "http/HMS_Http.h"
#include "mt/HMS_Multithread.h"
#include "socket/HMS_Socket.h"

namespace HMS {

template <class Function, class... Args>
decltype(auto) job(Function &&func, Args &&...args) {
    return std::function<void()>(func)(std::forward<Args>(args)...);
};

void processRequest(const Socket &server, const Socket &client);
void sendResponse(const Socket &server, const Socket &client);

struct ConfigData {
    std::string ip;
    std::string port;
};

class Server {
  private:
    Socket mSocket {};
    ThreadPool mThreadPool {};
    size_t mNumOfClients {0};

    void init();
    void init(const char *configFilePath);
    void shutdown();

  public:
    Server() { init(); };
    Server(const char *configFilePath) { init(configFilePath); };
    ~Server() { shutdown(); };

    void run();
};
}; // namespace HMS
