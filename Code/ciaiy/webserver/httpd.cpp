#include "httpd.h"
#include <iostream>

using std::cout;
using std::endl;

int httpd::epfd = 0;

httpd::httpd(int port) {
    this->port = port;
    this->serverfd = Socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addrlen = sizeof(struct sockaddr);
    Setnonblock(this->serverfd);
    bzero(&this->serveraddr, addrlen);
    this->serveraddr.sin_family = AF_INET;
    this->serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->serveraddr.sin_port = htons(port);
    Bind(serverfd, (struct sockaddr *)&this->serveraddr, addrlen);

    Listen(serverfd, 100);
    #ifdef DEBUG
    cout<<"初始化结束"<<endl;
    #endif // DEBUG
}

void httpd::start() {
    int clientfd;
    socklen_t clientlen;
    struct sockaddr_in* clientaddr;
    #ifdef DEBUG
    cout<<"start epoll" <<endl;
    #endif // DEBUG
    this->epfd = epoll_create(1);
    ev.data.fd = this->serverfd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, this->serverfd, &this->ev);
    while(1) {
        int event_num = epoll_wait(this->epfd, this->events, 500, 20);
        for(int i = 0; i < event_num; i++) {
            #ifdef DEBUG
            cout <<"epoll :" << event_num<<endl;
            #endif // DEBUG
            if(events[i].data.fd == serverfd) {
                // 新连接
                #ifdef DEBUG
                cout<<"新连接"<<endl;
                #endif // DEBUG
                clientfd = Accept(serverfd, (struct sockaddr*)&clientaddr, &clientlen);
                ev.data.fd = clientfd;
                ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
                Setnonblock(clientfd);
                epoll_ctl(this->epfd, EPOLL_CTL_ADD, clientfd, &this->ev);
            }else{
                char test_char;
                if(recv(ev.data.fd, &test_char, 1, MSG_PEEK) > 0) {
                    #ifdef DEBUG
                    cout<<"新数据"<<endl;
                    #endif // DEBUG
                    this->add_task(ev.data.fd);
                }else {
                    #ifdef DEBUG
                    cout<<"有用户离开"<<endl;
                    #endif // DEBUG
                    ev.data.fd = events[i].data.fd;
                    ev.events = EPOLLOUT;
                    epoll_ctl(this->epfd, EPOLL_CTL_DEL, ev.data.fd, &ev);
                }
            }
        }
    }
}

void httpd::add_task(int clientfd) {
    #ifdef DEBUG
        cout<<"add_task begin"<<endl;
    #endif
    int *arg = new int(clientfd);
    pthread_t thid;
    pthread_create(&thid, NULL, run, (void *)arg);
}

void *httpd::run(void *arg) {
    int clientfd = *(int *)arg;
    char buf[2] = {0};
    while(recv(clientfd, &buf, 2, 0) > 0) {
        cout << pthread_self() << " : "<< buf[0] << buf[1]<<endl;
        sleep(1);
    }
    struct epoll_event ev;
    ev.data.fd = clientfd;
    ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epfd, EPOLL_CTL_MOD, clientfd, &ev);
    return NULL;
} 