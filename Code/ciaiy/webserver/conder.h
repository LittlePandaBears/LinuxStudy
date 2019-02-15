#ifndef _CONDER_H_
#define _CONDER_H_

#include <pthread.h>
#include <iostream>

class conder{
  public:
    conder();
    int signal();
    void wait();
  private:
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

#endif