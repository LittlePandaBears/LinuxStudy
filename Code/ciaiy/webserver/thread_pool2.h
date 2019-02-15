#ifndef _THREAD_POOL2_H_
#define _THREAD_POOL2_H_

#define DEBUG

#include <queue>
#include <iostream>
#include "locker.h"
#include "conder.h"
#include "rwlocker.h"

using std::queue;

class thread_pool2{
    private:

        /* 正在执行任务的工作线程数目 */
        static int doing_num;
        static locker doing_num_lock;

        /* 执行任务的参数队列 */            
        static queue<void *> task_queue;
        static locker task_queue_lock;

        /* 有任务标志 */
        static conder has_task_cond;

        thread_pool2() {}
        void start_all(void *(* fun)(void *));
        static void *(*run)(void *arg);
        static void *thread_fun(void *arg);

    public:
        int thread_max = 2;
        void add_task(void *arg);
        thread_pool2(void *(* fun)(void *));
};

#endif