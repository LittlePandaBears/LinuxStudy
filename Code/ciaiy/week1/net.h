#ifndef __NET_H__

#define __NET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>

#define NO_ERROR 0

/* 错误处理函数 */
void err(char *err_msg);

/* 加了错误处理的socket函数 */
int Socket(int domain, int type, int protocol);

/* 加了错误处理的bind函数 */
int Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);

/* 加了错误处理的recvfrom函数 */
ssize_t Recvfrom(int sockfd, void *buf, size_t len, int flags
    , struct sockaddr *src_addr, socklen_t *addrlen);

/* 加了错误处理的sendto函数 */
ssize_t Sendto(int sockfd, const void *buf, size_t len, int flags
    , const struct sockaddr *dest_addr, socklen_t addrlen);

#endif