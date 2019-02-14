#include "pthread_pool2.h"

pthread_pool2::pthread_pool2(void *(* fun)(void *)) {
    this->run = fun;    // 运行函数
    this->start_all();
}

pthread_pool2::start_all() {
    for(int i = 0; i < 2; i++) {
        pthread_t thid;
        pthread_create(&thid, NULL, this->thread_fun, NULL);
    }
}