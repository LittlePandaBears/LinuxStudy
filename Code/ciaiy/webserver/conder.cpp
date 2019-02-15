#include "conder.h"

conder::conder() {
    if(pthread_mutex_init(&this->mutex, NULL) != 0) {
        throw std::exception();
    }
    if(pthread_cond_init(&this->cond, NULL) != 0) {
        throw std::exception();
    }
}

int conder::signal() {
    return pthread_cond_signal(&this->cond);
}

void conder::wait() {
    pthread_mutex_lock(&this->mutex);
    pthread_cond_wait(&this->cond, &this->mutex);
    pthread_mutex_unlock(&this->mutex);
}
