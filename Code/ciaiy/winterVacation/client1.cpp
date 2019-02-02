#include <iostream>
#include "wrapperFunction.h"

#define _DEBUG_

using namespace std;

int main(void) {
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addr, addr_len);
    inet_pton(AF_INET, "localhost", &addr.sin_addr);
    addr.sin_port = htons(2333);
    addr.sin_family = AF_INET;
    Connect(sockfd, (struct sockaddr *)&addr, addr_len);

    #ifdef _DEBUG_
        cout<<"连接成功"<<endl;
    #endif

    char buf[204800];
    int write_num;
    for(int i = 0; i < 5; i++) {
        for(int i = 0; i < 204800; i++) {
            buf[i] = i % 10;
        }
        write_num = Write(sockfd, buf, 204800);
        
        #ifdef _DEBUG_
            cout<<"write "<<write_num<<"bytes"<<endl;    
        #endif
    }




    return 0;
}