#include "net.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    int sockfd;
    struct sockaddr_in client_addr, server_addr;
    bzero(&client_addr, sizeof(struct sockaddr_in));
    client_addr.sin_port = INADDR_ANY;

    return 0;
}