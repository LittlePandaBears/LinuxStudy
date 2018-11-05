#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in addr;

    if (argc == 2)
    {
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = atoi(argv[1]);
        Bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    }
}