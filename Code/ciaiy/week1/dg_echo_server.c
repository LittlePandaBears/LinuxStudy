#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"

#define BUF_MAX 512

void dg_echo(int sockfd, struct sockaddr *p_client_addr, socklen_t client_len);

void dg_echo(int sockfd, struct sockaddr *p_client_addr, socklen_t client_len) {
    int recv_num = 0;
    socklen_t modify_client_len;
    char buf[BUF_MAX] = {0};

    for(;;) {
        modify_client_len = client_len;

        recv_num = Recvfrom(sockfd, buf, BUF_MAX, 0, p_client_addr, &modify_client_len);
        buf[recv_num] = 0;
        printf("服务器收到了:%s\n", buf);

        Sendto(sockfd, buf, recv_num, 0, p_client_addr, modify_client_len);
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    if (argc == 2)
    {
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(atoi(argv[1]));   // 绑定端口
        Bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
        dg_echo(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));  // 所有业务逻辑都在这个函数里面
    }else {
        fprintf(stderr, "error!\nyou can start the service like this : \033[35m./dg_echo_server <port>\n\033[0m");
        exit(1);
    }

    return 0;
}