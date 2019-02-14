#ifndef _RWLOCKER_h_
#define _RWLOCKER_H_

#include <pthread.h>

class rwlocker
{
private:
    pthread_rwlock_t rwlock;
public:
    rwlocker();
};

rwlocker::rwlocker() {
    
}

#endif