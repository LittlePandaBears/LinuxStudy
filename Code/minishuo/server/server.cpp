#include "server.h"

server::server(int port) {
    // 进行serversocketfd的绑定等一系列操作
    this->port = port;
    socklen_t addrlen = sizeof(addr);
    serversocketfd = Socket(AF_INET, SOCK_STREAM, AF_INET);
    bzero(&addr, addrlen);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    Bind(serversocketfd, (struct sockaddr *)&addr, addrlen);
    Listen(serversocketfd, 1000);
}

void server::start() {
    epoll.start(serversocketfd);
}