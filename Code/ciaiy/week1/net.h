#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>

/* 错误处理函数 */
void err(int line);

/* 加了错误处理的socket函数 */
int Socket(int domain, int type, int protocol);

/* 加了错误处理的bind函数 */
int Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);