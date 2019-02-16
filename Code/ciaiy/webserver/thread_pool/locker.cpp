#include "locker.h"

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
