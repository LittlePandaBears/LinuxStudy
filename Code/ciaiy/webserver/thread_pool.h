#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#define DEBUG

#include <pthread.h>
#include <queue>
#include "locker.h"
#include "conder.h"

using std::queue;
using std::cout;
using std::endl;

class thread_pool  
{
  private:
    static bool shutdown;
    static int doing_num;
    static int thread_num;
    static locker shutdown_lock;
    static locker doing_num_lock;
    static locker task_queue_lock;
    static conder has_task;
    static queue<void *> task_queue;
    static thread_pool *me;
    static void *( *run)(void *arg);

    thread_pool() {}
    static void *thread_fun(void *);
  public:
    void start_all(void);
    void add_task(void *);
    thread_pool(int thread_num, void*(*pfun)(void *arg));
};  

#endif // !_PTHREAD_POOL_H_