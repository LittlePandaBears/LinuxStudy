#ifndef _SERVER_H_
#define _SERVER_H_

class server {
    public :
    server(int port);
    private :
    fileTransport ts; // 文件传输类
    socketManage sm;    // socket管理类
}

#endif