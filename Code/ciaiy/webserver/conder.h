#ifndef _CONDER_H_
#define _CONDER_H_

#include <pthread.h>
#include <iostream>

class conder{
  public:
    conder();
    void signal();
    void wait();
  private:
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

conder::conder() {
    if(pthread_mutex_init(&this->mutex, NULL) != 0) {
        throw std::exception();
    }
    if(pthread_cond_init(&this->cond, NULL) != 0) {
        throw std::exception();
    }
}

void conder::signal() {
    pthread_cond_signal(&this->cond);
}

void conder::wait() {
    pthread_mutex_lock(&this->mutex);
    pthread_cond_wait(&this->cond, &this->mutex);
    pthread_mutex_unlock(&this->mutex);
}


#endif