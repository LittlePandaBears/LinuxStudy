#include "tool.h"
#include <iostream>

using std::cout;
using std::endl;

int main(void) {
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    addr.sin_port = htons(2333);
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int serverfd = Socket(AF_INET, SOCK_STREAM, 0);
    Connect(serverfd, (struct sockaddr*)&addr, addrlen);
    cout<<"serverfd "<< serverfd<<endl;
    char buf[10] = "123456789";
    int recvnum = Write(serverfd, buf, 10);
    cout << recvnum<<endl;

    sleep(1);
    recvnum = Write(serverfd, buf, 10);
    cout << recvnum<<endl;
    return 0;
}