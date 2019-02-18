#ifndef _HTTPD_H_
#define _HTTPD_H_

#define DEBUG

#include "tool.h"
#include <sys/epoll.h>
#include <pthread.h>

class httpd{
    public:
        httpd(int port);
        void start();
    private:
        static int epfd;
        int serverfd;
        int port = 2333;
        struct sockaddr_in serveraddr;
        struct epoll_event ev, events[500];
        static void *run(void *arg);
        static void add_task(int clientfd);
};

#endif // !_HTTPD_H_