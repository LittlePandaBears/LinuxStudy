#ifndef SERVER_H
#define SERVER_H

#include "../common/wrapperFunction.h"
#include "sql_manager.h"
#include "loger.h"
#include "transaction_manager.h"
#include "epoller.h" 
#include "thread_pooler.h"

class server{
    public :
        server(int port);
        void start();
    private :
        int port;
        int serversocketfd;
        struct sockaddr_in addr;
        sql_manager sql; // 负责一系列的数据库操作
        loger log;  // 负责日志记录
        transaction_manager transcation;    // 负责所有的业务逻辑
        epoller epoll;  //  负责所有的IO多路复用
        thread_pooler pool; // 负责线程池的调度等任务


};

#endif // !SERVER_H
