#include "rwlocker.h"


rwlocker::rwlocker() {
    rwlock = PTHREAD_RWLOCK_INITIALIZER;
}

void rwlocker::readlock(){
    if(pthread_rwlock_rdlock(&this->rwlock) != 0) {
        throw std::exception();
    }
}

void rwlocker::writelock() {
    if(pthread_rwlock_wrlock(&this->rwlock) != 0) {
        throw std::exception();
    }
}

void rwlocker::unlock() {
    if(pthread_rwlock_unlock(&this->rwlock) != 0) {
        throw std::exception();
    }    
}