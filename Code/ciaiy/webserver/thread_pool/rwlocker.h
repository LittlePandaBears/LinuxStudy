#ifndef _RWLOCKER_H_
#define _RWLOCKER_H_

#include <iostream>
#include <pthread.h>

class rwlocker
{
private:
    pthread_rwlock_t rwlock;
public:
    rwlocker();
    void readlock();
    void writelock();
    void unlock();
};

#endif