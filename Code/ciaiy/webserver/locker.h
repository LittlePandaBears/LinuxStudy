#ifndef _LOCKER_H_
#define _LOCKER_H_

#include <pthread.h>
#include <iostream>

class locker{
  public:
    locker();
    void lock();
    void unlock();
  private:
    pthread_mutex_t mutex;
};

locker::locker() {
    if(pthread_mutex_init(&this->mutex, NULL) != 0) {
        throw std::exception();
    }
}

void locker::lock() {
    pthread_mutex_lock(&this->mutex);
}

void locker::unlock() {
    pthread_mutex_unlock(&this->mutex);
}

#endif