#include "net.h"

void err(int line) {
    if(errno != NO_ERROR) {
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
 
ssize_t Recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
    ssize_t ret_value;

    if((ret_value = recvfrom(sockfd, buf, len, flags, src_addr, addrlen)) < 0) {
        err(__LINE__);
    }

    return ret_value;
}

ssize_t Sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
    ssize_t ret_value;

    if((ret_value = sendto(sockfd, buf, len, flags, dest_addr, addrlen)) < 0) {
        err(__LINE__);
    }

    return ret_value;
}