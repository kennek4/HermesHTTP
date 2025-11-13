#pragma once

#include "socket/HMS_Socket.h"
#include "utility/HMS_pch.h"

namespace HMS {

using JobFunction = std::function<void(const Socket &, const Socket &)>;
using Job         = std::tuple<JobFunction, Socket, Socket>;

class ThreadPool {
  private:
    std::mutex mQueueMutex {};
    std::condition_variable mMutexCondition;

    std::vector<std::thread> mThreads {};
    std::queue<Job> mJobs {};

    bool mIsFinished {false};

    void init();

    void workLoop();

  public:
    ThreadPool();
    ~ThreadPool();

    void shutdown();
    void queueJob(Job job);
    bool isBusy();
};
}; // namespace HMS
