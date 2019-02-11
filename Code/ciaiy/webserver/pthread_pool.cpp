#include "pthread_pool.h"
#include <iostream>

using std::cout;
using std::endl;

pthread_pool::pthread_pool() {
    this->shutdown = false;
    this->cond = PTHREAD_COND_INITIALIZER;
    this->doing_lock = PTHREAD_MUTEX_INITIALIZER;
    this->wait_lock = PTHREAD_MUTEX_INITIALIZER;
    thread_num = thread_num == 0 ? 10 : thread_num;
    this->start_all();
}