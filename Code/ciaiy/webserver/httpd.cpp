#include "httpd.h"
#include "mission.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;
 
int httpd::epfd = 0;

httpd::httpd(int port) {
    chroot(".");
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
            cout <<"\033[31m epoll :" << event_num<<"\033[0m"<<endl;
            #endif // DEBUG
            if(events[i].data.fd == serverfd) {
                // 新连接
                clientfd = Accept(serverfd, (struct sockaddr*)&clientaddr, &clientlen);
                ev.data.fd = clientfd;
                ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
                Setnonblock(clientfd);
                epoll_ctl(this->epfd, EPOLL_CTL_ADD, clientfd, &this->ev);
                #ifdef DEBUG
                cout << "\033[32m  新连接" << clientfd << "\033[0m" <<endl;
                #endif // DEBUG
            }else {
                char test_char;

                if(recv(ev.data.fd, &test_char, 1, MSG_PEEK) > 0) {
                    #ifdef DEBUG
                    cout<<"\033[33m 新数据 " << ev.data.fd << "\033[0m"<<endl;
                    #endif // DEBUG
                    this->add_task(ev.data.fd);
                }
            }
        }
    }
}

void httpd::add_task(int clientfd) {
    #ifdef DEBUG
        cout<<"add_task begin"<<endl;
    #endif

<<<<<<< HEAD
void *httpd::run(void *arg) {
    int clientfd = *(int *)arg;
    char buf[2] = {0};
    while(recv(clientfd, &buf, 2, 0) > 0) {
        cout << pthread_self() << " : "<< buf[0] << buf[1]<<endl;
        sleep(1);
    }
    struct epoll_event ev;
    ev.data.fd = clientfd;
    ev.events = EPOLL_CTL_DEL
    epoll_ctl(epfd, EPOLL_CTL_MOD, clientfd, &ev);
    return NULL;
} 
=======
    mission *m = new mission(clientfd, epfd);
    pool.add_task(m);
}
>>>>>>> 76e5cf8b3e041cf561d20b421834c41a770f486d
