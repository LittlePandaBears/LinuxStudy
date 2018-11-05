#include "net.h"

void err(int line) {
    if(errno != 0) {
        fprintf(stderr, "line : %d\n", line);
        perror("error : ");
    }else { // errno等于0, 说明当前状态为无异常
        return;
    }
}

int Socket(int domain, int type, int protocol) {
    int ret_value;

    if((ret_value = socket(domain, type, protocol)) < 0) {
        err(__LINE__);
    }

    return ret_value;
}

int Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen) {
    int ret_value;

    if((ret_value = bind(sockfd, my_addr, addrlen)) < 0) {
        err(__LINE__);
    }

    return ret_value;
}