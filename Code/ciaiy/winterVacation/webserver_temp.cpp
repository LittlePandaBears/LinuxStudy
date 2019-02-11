#include <iostream>
#include "wrapperFunction.h"
using namespace std;

int main(void) {
    struct sockaddr_in addr;
    int port = 2333;
    int listenfd, httpfd;
    socklen_t addr_len = sizeof(struct sockaddr);

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addr, addr_len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(2333);
    Bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    Listen(listenfd, 100);
    httpfd = Accept(listenfd, (struct sockaddr *)NULL, NULL);

    while(true) {
        char buf[204800] = {0};
        int recvnum = Read(httpfd, buf, 204800);
        cout << recvnum << endl;
        cout << buf << endl;
        char sendbuf[204800] = {0};
        sprintf(sendbuf, "HTTP/1.1 200 OK\r\nDate: Sat, 31 Dec 2005 23:59:59 GMT\r\nContent-Type: text/html;charset=ISO-8859-1\r\nContent-Length: 122\r\n\r\nTHE FIRST WEB SERVER!");
        Write(httpfd, sendbuf, 204800);
    }

}