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

#endif