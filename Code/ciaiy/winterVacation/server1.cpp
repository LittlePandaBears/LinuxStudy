#include <iostream>
#include "wrapperFunction.h"

#define _DEBUG_

using namespace std;

int main(void) {
    struct sockaddr_in addr;
    int port = 2333;
    int listenfd, acceptfd;
    socklen_t addr_len = sizeof(struct sockaddr);

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addr, addr_len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(2333);
    Bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    Listen(listenfd, 100);

    #ifdef _DEBUG_
        cout<<"waiting for connection"<<endl;
    #endif


    acceptfd = Accept(listenfd, (struct sockaddr *)NULL, NULL);
    
    #ifdef _DEBUG_
        cout<<"a connection"<<endl;
        int total_num = 0;
    #endif



    while(true) {
        char buf[204800];
        int recv_num = Read(acceptfd, buf, 204800);
        if(recv_num == 0) {
            #ifdef _DEBUG_
                cout<<"total recvnum = " << total_num <<endl;
            #endif
            break;
        }    

        #ifdef _DEBUG_
            cout<<"recv " << recv_num << "bytes data"<<endl;
            cout<<(int)buf[0]<<"-"<<(int)buf[recv_num - 1]<<endl;
            total_num += recv_num;
            bzero(buf, 204800);
        #endif

        sleep(1);
    }

    return 0;
}