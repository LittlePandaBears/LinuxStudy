#ifndef _THREAD_POOL3_H_
#define _THREAD_POOL3_H_

#define DEBUG

#include <queue>
#include <iostream>
#include <assert.h>
#include <pthread.h>
#include "locker.h"

using std::queue;
using std::cout;
using std::endl;

template<typename T>

class thread_pool {
    public:         
        thread_pool<T>(int thread_num = 8);
        /* 添加任务 */
        void add_task(T* request);
        /* 终止线程池 */
        void stop_all();

    private:
        /* 线程池中线程的个数 */
        int thread_num;
        /* 线程池数组 */
        pthread_t *thread_list;
        /* 有任务的信号量 */
        sem has_work;
        /* 保护任务队列的锁 */
        locker task_queue_lock;
        /* 任务队列 */
        std::queue<T*> task_queue;
        /* 终止变量 */
        bool stop;

        /* 线程函数 */
        static void* work(void *arg);
        /* 线程执行函数 */
        void run(void);
};

template<typename T>
void thread_pool<T>::run(void) {
    while(stop == false) { 
        if(has_work.wait()) {
            task_queue_lock.lock(); // 加锁
            if(task_queue.empty() == true){
                task_queue_lock.unlock();   //  如果为空, 则跳过并解锁
                continue;
            }
            T *misson = task_queue.front(); // 得到任务
            task_queue.pop();
            task_queue_lock.unlock();   // 取完任务, 解锁
            // assert(misson == NULL); // 防止下面语句报错
            misson->process();  // 运行任务的process函数
        }
    }
}

template<typename T>
void *thread_pool<T>::work(void *arg) {
    thread_pool *me = (thread_pool*)arg;
    me->run();
    return me;
}

template<typename T>
thread_pool<T>::thread_pool(int thread_num) : thread_num(thread_num) {
    #ifdef DEBUG
    cout<<"thread_pool starting"<<endl;
    cout<<"thread_num : " << thread_num << endl;
    #endif
    stop = false;
    thread_list = new pthread_t[thread_num];
    for(int i = 0; i < thread_num; i++) {
        pthread_t thid;
        pthread_create(&thid, NULL, work, this);
        thread_list[i] = thid;
        pthread_detach(thid);
    }
    #ifdef DEBUG
    cout << "初始化完成" <<endl;
    #endif // DEBUG
}

template<typename T>
void thread_pool<T>::add_task(T *request) {
    task_queue_lock.lock();
    task_queue.push(request);
    task_queue_lock.unlock();
    has_work.post();
}

template<typename T>
void thread_pool<T>::stop_all() {
    stop = true;
}

#endif // !_THREAD_POLL_H_