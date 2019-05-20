#include "epoller.h"

epoller::epoller() {
    epfd = epoll_create(10000);
}

void epoller::start(int serversocketfd, struct sockaddr_in *addr) {
    socklen_t addrlen = sizeof(*addr);
    // 将serversocket加入到epoll监听
    ev.data.fd = serversocketfd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serversocketfd, &ev);

    while(1) {
        int event_num = epoll_wait(epfd, events, 10000, 100);
        for(int i = 0; i < event_num; i++) {
            if(events[i].data.fd == serversocketfd) {   //  新连接
                int newclientfd = Accept(serversocketfd, (struct sockaddr*)addr, &addrlen);
                ev.data.fd = newclientfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);

                /* 此处为 新用户加入 代码 */
                continue;
            }
            if(events[i].events & EPOLLIN) {    // 新数据
                continue;
            }

            if(events[i].events & EPOLLOUT) {   // 用户退出
                /* 有用户退出 */
                continue;
            }
        }
    }

}