#ifndef CONDITION_H
#define CONDITION_H
#include "mutex_lock.h"

class Condition
{
public:
    explicit Condition(MutexLock& mutex) :mutex_(mutex) { pthread_cond_init(&cond_, NULL); }
    ~Condition() { pthread_cond_destroy(&cond_); }
    Condition(const Condition&) = delete;
    void operator=(const Condition& ) = delete;

public:
    void Wait() { pthread_cond_wait(&cond_, mutex_.GetMutexLock()); }
    void Notify() { pthread_cond_signal(&cond_); }
    void NotifyAll() { pthread_cond_broadcast(&cond_); }

private:
    MutexLock& mutex_;
    pthread_cond_t cond_;

};
#endif