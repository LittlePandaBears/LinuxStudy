#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

void err(const char *err_msg) {
    char pause;
    perror(err_msg);
    pause = getchar();
}

int Socket(int domain, int type, int protocol) {
    int ret_value = socket(domain, type, protocol);
    
    if(ret_value == -1) {
        err("socket");
    }

    return ret_value;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int ret_value = bind(sockfd, addr, addrlen);

    if(ret_value == -1) {
        err("bind");
    }

    return ret_value;
}

int Listen(int sockfd, int backlog) {
    int ret_value = listen(sockfd, backlog);

    if(ret_value == -1) {
        err("listen");
    }

    return ret_value;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int ret_value = accept(sockfd, addr, addrlen);

    if(ret_value == -1) {
        err("accept");
    }

    return ret_value;
}

ssize_t Read(int fd, void *buf, size_t count) {
    int ret_value = read(fd, buf, count);

    if(ret_value == -1) {
        err("read");
    }

    return ret_value;
}

ssize_t Recv(int sockfd, void *buf, size_t len, int flags) {
    int ret_value = recv(sockfd, buf, len, flags);
    
    if(ret_value == -1) {
        err("recv");
    }

    return ret_value;
}

int Inet_pton(int af, const char* src, void *dst) {
    int ret_value = inet_pton(af, src, dst);
    
    if(ret_value <= 0) {
        err("inet_pton");
    }

    return ret_value;
}

int Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int ret_value = connect(sockfd, addr, addrlen);
    
    if(ret_value == -1) {
        err("connect");
    }

    return ret_value;
}

int Write(int fd, const void *buf, size_t count) {
    int ret_value = write(fd, buf, count);
    
    if(ret_value == -1) {
        err("write");
    }

    return ret_value;
}