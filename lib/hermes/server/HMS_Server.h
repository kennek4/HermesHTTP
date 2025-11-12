#pragma once

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

  public:
    Server() { run(); };
    ~Server() { stop(); };

    void run();
    void stop();
};
}; // namespace HMS
