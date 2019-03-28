#include "thread_pool.h"

thread_pool::thread_pool(int thread_num, void*(*pfun)(void *arg)) {
    this->thread_num = thread_num;
    this->run = pfun;
    this->shutdown = false;
    this->me = this;
}

void thread_pool::start_all(void) {
    
    for(int i = 0; i < this->thread_num; i++) {
        pthread_t temp;
        if(pthread_create(&temp, NULL, thread_pool::thread_fun, (void *)(&thread_pool::task_queue)) != 0) {
            throw std::exception();
        }

        #ifdef DEBUG
            cout<< "第" << i << "个线程启动" <<endl;
        #endif
    
    }
}

void* thread_pool::thread_fun(void *arg) {
    while(!shutdown) {
        has_task.wait();    // 等待任务
        task_queue_lock.lock(); // 有任务且进行竞争task_queue_lock
        if(task_queue.empty()) {    // 任务队列为空 则解锁
            task_queue_lock.unlock();
            continue;
        }else {
            void *arg = task_queue.front(); 
            task_queue.pop();
            task_queue_lock.unlock();
            me->run(arg);
        }
    }
    return NULL;
}

void thread_pool::add_task(void *arg) {
    this->task_queue_lock.lock();
    this->task_queue.push(arg);
    this->task_queue_lock.unlock();
}
