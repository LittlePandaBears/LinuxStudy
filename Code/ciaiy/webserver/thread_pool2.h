#ifndef _THREAD_POOL2_H_
#define _THREAD_POOL2_H_

#define DEBUG

class thread_pool2{
    private:
        thread_pool2() {}
        void start_all(void *(* fun)(void *));
        void *(*run)(void *arg);
        static void *thread_fun(void *arg);
    public:
        thread_pool2(void *(* fun)(void *));
};

#endif