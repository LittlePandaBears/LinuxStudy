#include "thread_pool2.h"
#include <pthread.h>
#include <iostream>

thread_pool2::thread_pool2(void *(* fun)(void *)) {
    this->start_all(fun);
}

void thread_pool2::start_all(void *(* fun)(void *)) {   // 运行所有线程
    run = fun;    // 运行函数
    for(int i = 0; i < 2; i++) {
        pthread_t thid;
        pthread_create(&thid, NULL, this->thread_fun, NULL);
    }
}

void *thread_pool2::thread_fun(void *arg) { // 
    #ifdef DEBUG
    std::cout << "thread_fun running" << std::endl;
    #endif 
}