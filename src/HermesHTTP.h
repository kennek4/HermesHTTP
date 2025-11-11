#pragma once

#include <Hermes.h>

namespace HMS {
namespace HTTP {

template <class Function, class... Args>
decltype(auto) job(Function &&func, Args &&...args) {
    return std::function<void()>(func)(std::forward<Args>(args)...);
};

void processRequest(const Socket &server, const Socket &client);
void sendResponse(const Socket &server, const Socket &client);

}; // namespace HTTP

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
