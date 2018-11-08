#include "net.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_MAX 512

void dg_cli(int sockfd, struct sockaddr *server_addr, socklen_t addr_len);

void dg_cli(int sockfd, struct sockaddr *server_addr, socklen_t addr_len) {
    int recv_num;
    char recv_buf[BUF_MAX], send_buf[BUF_MAX];

    while(fgets(send_buf, BUF_MAX, stdin)) {
        Sendto(sockfd, send_buf, strlen(send_buf), 0, server_addr, addr_len);
        printf("已发送\n");
        recv_num = Recvfrom(sockfd, recv_buf, BUF_MAX, 0, NULL, NULL);
        recv_buf[recv_num] = 0;

        printf("server : %s\n", recv_buf);
    }
}

int main(int argc, char *argv[]) {
    int sockfd;
    
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(struct sockaddr_in));
    
    if(argc == 3) {
        server_addr.sin_family = AF_INET;
        inet_pton(AF_INET, argv[1], &server_addr.sin_addr.s_addr);
        server_addr.sin_port = htons(atoi(argv[2]));
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

        for(;;) {
            dg_cli(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
        }
    }else {
        fprintf(stderr, "error!\nyou can start the service like this : \033[35m./dg_echo_client <ip address> <port>\n\033[0m");
        exit(0);
    }

    return 0;
}