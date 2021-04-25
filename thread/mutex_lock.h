#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <pthread.h>
#include <assert.h>
#include <iostream>

class MutexLock
{
public:
    MutexLock() :holder_(0) { pthread_mutex_init(&mutex_, NULL); }
    ~MutexLock() { assert(holder_ == 0); pthread_mutex_destroy(&mutex_); };

    MutexLock(const MutexLock& ) = delete;
    void operator=(const MutexLock& ) = delete;
public:
    bool IsLockedByThisThread() { return holder_ == pthread_self(); }
    void AssertLocked() { assert(IsLockedByThisThread()); }
    void Lock() { pthread_mutex_lock(&mutex_); holder_ = pthread_self();}
    void UnLock() { holder_ = 0; pthread_mutex_unlock(&mutex_); }
    pthread_mutex_t* GetMutexLock() { return &mutex_; }

private:
    pthread_mutex_t mutex_;
    pthread_t holder_;
};

#endif

