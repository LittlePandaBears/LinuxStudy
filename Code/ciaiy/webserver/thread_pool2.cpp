#include "thread_pool2.h"
#include <pthread.h>
#include <iostream>
#include <assert.h>
#include <unistd.h>

#ifdef DEBUG

    using std::cout;
    using std::endl;

#endif

/* 正在执行任务的工作线程数目 */
int thread_pool2::doing_num = 0;
locker thread_pool2::doing_num_lock;

/* 执行任务的参数队列 */            
queue<void *> thread_pool2::task_queue;
locker thread_pool2::task_queue_lock;

/* 有任务标志 */
conder thread_pool2::has_task_cond;


void *(*thread_pool2::run)(void *arg);

thread_pool2::thread_pool2(void *(* fun)(void *)) {
    this->start_all(fun);
}

void thread_pool2::start_all(void *(* fun)(void *)) {   // 运行所有线程
    thread_pool2::doing_num = 0;

    run = fun;    // 运行函数 
    for(int i = 0; i < 2; i++) {
        pthread_t thid;
        pthread_create(&thid, NULL, this->thread_fun, NULL);
    }
}

void *thread_pool2::thread_fun(void *arg) { // 工作线程函数
    while(1) {
        void *run_arg;
        #ifdef DEBUG
        cout<<pthread_self()<<"等待"<<endl;
        #endif
        has_task_cond.wait();
        /* 判断退出部分 */


        /* 取参数 */
        task_queue_lock.lock();
        if(!task_queue.empty()) {


            
            /* 从队列中取参数 */
            run_arg = task_queue.front();
            task_queue.pop();
            task_queue_lock.unlock();        
        }else {
            continue;
            task_queue_lock.unlock();
        }
        

        #ifdef DEBUG
            cout << "得到任务" << pthread_self()<<endl;
        #endif
 
        thread_pool2::run(run_arg); 
        doing_num_lock.lock();
        doing_num--;
        doing_num_lock.unlock();
    }
}

void thread_pool2::add_task(void *arg) {
    doing_num_lock.lock();
    while(doing_num >= thread_max) {
        // cout<<"无可用线程"<<endl;
        doing_num_lock.unlock();
        doing_num_lock.lock();
    }
            
    task_queue_lock.lock();
    task_queue.push(arg);
    task_queue_lock.unlock();

    /* 让正在执行工作的线程数目加一 */
    doing_num++;
    doing_num_lock.unlock();
 
    cout<<"已发送信号"<<endl;
    if(has_task_cond.signal() != 0) {
        cout<<"some thing wrong"<<endl;
    }
}