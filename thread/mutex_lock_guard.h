#ifndef MUTEX_LOCK_GUARD_H
#define MUTEX_LOCK_GUARD_H

#include "mutex_lock.h"

class MutexLockGuard
{
public:
    explicit MutexLockGuard(MutexLock& mutex) :mutex_(mutex)  { mutex.Lock(); }
    ~MutexLockGuard() { mutex_.UnLock(); }

    MutexLockGuard(const MutexLockGuard& ) = delete;
    void operator=(const MutexLockGuard& ) = delete;

private:
    MutexLock& mutex_;
};

#endif