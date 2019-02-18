#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <arpa/inet.h>

void err(const char *err_msg);
int Socket(int domain, int type, int protocol);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
ssize_t Read(int fd, void *buf, size_t count);
ssize_t Recv(int sockfd, void *buf, size_t len, int flags);
int Inet_pton(int af, const char* src, void *dst);
int Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
int Write(int fd, const void *buf, size_t count);
int Setnonblock(int fd);

