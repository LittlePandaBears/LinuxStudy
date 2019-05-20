#ifndef _HTTPD_H_
#define _HTTPD_H_

#define DEBUG

#include "tool.h"
#include <sys/epoll.h>
#include "thread_pool3.h"
#include "mission.h"

class httpd{
    public:
        httpd(int port);
        void start();
    private:
        static int epfd;
        int serverfd;
        int port = 2333;
        thread_pool<mission> pool;
        struct sockaddr_in serveraddr;
        struct epoll_event ev, events[500];
        void add_task(int clientfd);
};

#endif // !_HTTPD_H_