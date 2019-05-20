#ifndef EPOLLER_H
#define EPOLLER_H

#include <sys/epoll.h>
#include "../common/wrapperFunction.h"

class epoller
{
  public:
    epoller();
    void start(int serversocketfd, struct sockaddr_in *addr);

  private:
    int epfd;
    struct epoll_event ev;
    struct epoll_event events[10000];
};

#endif // !EPOLLER_H
