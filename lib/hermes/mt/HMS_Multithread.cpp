#include "HMS_Multithread.h"
#include <tuple>

namespace HMS {
ThreadPool::ThreadPool() { init(); };

ThreadPool::~ThreadPool() { shutdown(); };

void ThreadPool::workLoop() {
    std::tuple<JobFunction, Socket, Socket> job;
    JobFunction jobFunction;
    Socket server;
    Socket client;

    while (true) {
        {
            std::unique_lock<std::mutex> lock(mQueueMutex);
            mMutexCondition.wait(
                lock, [this] { return !mJobs.empty() && !mIsFinished; });

            if (mIsFinished)
                return;

            job = mJobs.front();
            mJobs.pop();
        };

        std::tie(jobFunction, server, client) = job;
        jobFunction(server, client);
    };
};

void ThreadPool::init() {
    uint32_t numOfThreads = std::thread::hardware_concurrency() - 1;
    assert(numOfThreads != 0);

    for (uint32_t i = 0; i < numOfThreads; i++) {
        mThreads.emplace_back(std::thread(&ThreadPool::workLoop, this));
    };

    std::cerr << "Threads Created: " << std::to_string(numOfThreads) << "\n";
};

void ThreadPool::shutdown() {
    {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        mIsFinished = true;
    }

    mMutexCondition.notify_all();
    for (std::thread &activeThread : mThreads) {
        activeThread.join();
    };

    mThreads.clear();
};

void ThreadPool::queueJob(Job job) {
    {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        mJobs.push(job);
    };

    mMutexCondition.notify_one();
};

bool ThreadPool::isBusy() {
    bool isPoolBusy;

    {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        isPoolBusy = !mJobs.empty();
    }

    return isPoolBusy;
};
}; // namespace HMS
