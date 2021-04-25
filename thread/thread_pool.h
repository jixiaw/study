#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <functional>
#include <list>
#include <thread>
#include <string>
#include <iostream>
#include <memory>

#include "mutex_lock.h"
#include "condition.h"
#include "mutex_lock_guard.h"


class ThreadPool
{
public:
    typedef std::function<void ()> Task;
    ThreadPool();
    ThreadPool(const std::string& name, size_t threadNum, size_t maxQueueSize);
    ~ThreadPool();

public:
    bool Start();
    bool Init(const std::string& name, size_t threadNum, size_t maxQueueSize);
    void Stop();
    bool Run(Task task);

public:
    const std::string& GetName() { return name_; }
    size_t GetThreadNum() { return threadNum_; }
    size_t GetMaxQueueSize() { return maxQueueSize_; }
    size_t GetTaskNum() { return taskNum_; }
    size_t GetFinishTashNum() { return finishTaskNum_; }

private:
    Task PopTask();
    void RunInThread();

private:
    size_t maxQueueSize_;
    size_t threadNum_;
    std::list<Task> taskQueue_;
    std::vector<std::unique_ptr<std::thread>> threads_;
    
    mutable MutexLock mutex_;
    Condition cond_;
    bool isRun_;
    std::string name_;
    size_t taskNum_;
    size_t finishTaskNum_;
};

ThreadPool::ThreadPool()
: mutex_(),
  cond_(mutex_),
  name_("Thread Pool"),
  threadNum_(8),
  maxQueueSize_(32),
  taskNum_(0),
  finishTaskNum_(0),
  isRun_(false)
{
}

ThreadPool::ThreadPool(const std::string& name, size_t threadNum, size_t maxQueueSize)
: mutex_(),
  cond_(mutex_),
  name_(name),
  threadNum_(threadNum),
  maxQueueSize_(maxQueueSize),
  taskNum_(0),
  finishTaskNum_(0),
  isRun_(false)
{
}

ThreadPool::~ThreadPool() {
    if (isRun_) {
        Stop();
    }
}

bool ThreadPool::Start() {
    if (isRun_) {
        std::cout << "Thread pool is running, init failed." << std::endl;
        return false;
    }
    isRun_ = true;
    threads_.reserve(threadNum_);
    for (size_t i = 0; i < threadNum_; ++i) {
        threads_.emplace_back(new std::thread(&ThreadPool::RunInThread, this));
    }
    return true;
}

bool ThreadPool::Init(const std::string& name, size_t threadNum, size_t maxQueueSize) {
    name_ = name;
    threadNum_ = threadNum;
    maxQueueSize_ = maxQueueSize;
    return Start();
}


bool ThreadPool::Run(ThreadPool::Task task) {
    if (!isRun_) {
        std::cout << "Thread Pool is not running!" << std::endl;
        return false;
    }
    MutexLockGuard lock(mutex_);
    if (taskQueue_.size() >= maxQueueSize_) {
        std::cout << "Thread Pool's task queue is full!" << std::endl;
        return false;
    }
    taskQueue_.push_back(task);
    ++taskNum_;
    cond_.Notify();
    return true;
}

void ThreadPool::Stop() {
    if (isRun_) {
        MutexLockGuard lock(mutex_);
        isRun_ = false;
        cond_.NotifyAll();
    }
    for (auto& it: threads_) {
        it->join();
    }
}

ThreadPool::Task ThreadPool::PopTask() {
    MutexLockGuard lock(mutex_);
    while(taskQueue_.empty() && isRun_) {
        cond_.Wait();
    }
    Task task;
    if (!taskQueue_.empty()) {
        task = taskQueue_.front();
        taskQueue_.pop_front();
        --taskNum_;
        ++finishTaskNum_;
    }
    return task;
}

void ThreadPool::RunInThread() {
    while(isRun_) {
        Task task = PopTask();
        if (task) {
            task();
        }
    }
}

#endif