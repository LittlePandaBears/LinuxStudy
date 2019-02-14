#ifndef _PTHREAD_POOL2_H_
#define _PTHREAD_POOL2_H_

class pthread_pool2{
    private:
        pthread_pool2() {}
        void start_all();
        static void *thread_fun(void *arg);
    public:
        pthread_pool2(void *(* fun)(void *));
};

#endif