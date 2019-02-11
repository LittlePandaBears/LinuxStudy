#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_
#endif // !_PTHREAD_POOL_H_

#define DEBUG

#include <pthread.h>
#include <queue>

using std::queue;

class pthread_pool
{
  private:
    pthread_pool();
    void *arg;  // 任务分发时的参数
    int thread_num; // 线程数
    bool shutdown;  // 终止所有线程的变量
    void *(*pfun)(void *arg); // 工作函数
    pthread_cond_t cond; //  竞争条件变量
    pthread_mutex_t wait_lock;  //　等待队列锁
    pthread_mutex_t doing_lock; //　执行队列锁
    pthread_mutex_t arg_lock;   // 工作函数读取参数锁
    queue<pthread_t> wait_queue;  // 等待队列
    queue<pthread_t> doing_queue; // 执行队列
  public:
    pthread_pool(void *(*pfun)(void *arg), int thread_num);  // 初始化函数, 参数为线程执行函数
    ~pthread_pool();
    void start_all(); // 启动线程
    bool add_task(void *arg);   // 添加任务
    void close_all();   // 停止所有线程
};  