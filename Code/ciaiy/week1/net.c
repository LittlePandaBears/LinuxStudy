#include "net.h"

void err(char *err_msg) {
    if(errno != NO_ERROR) {
        fprintf(stderr, "\033[36m%s ", err_msg);
        perror("\033[0m");
    }else { // errno等于0, 说明当前状态为无异常
        return;
    }
}

int Socket(int domain, int type, int protocol) {
    int ret_value;

    if((ret_value = socket(domain, type, protocol)) < 0) {
        err("socket");
    }

    return ret_value;
}

int Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen) {
    int ret_value;

    if((ret_value = bind(sockfd, my_addr, addrlen)) < 0) {
        err("bind");
    }

    return ret_value;
}
 
ssize_t Recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
    ssize_t ret_value;

    if((ret_value = recvfrom(sockfd, buf, len, flags, src_addr, addrlen)) < 0) {
        err("recvfrom");
    }

    return ret_value;
}

ssize_t Sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
    ssize_t ret_value;

    if((ret_value = sendto(sockfd, buf, len, flags, dest_addr, addrlen)) < 0) {
        err("sendto");
    }

    return ret_value;
}