#ifndef _MISSION_H_
#define _MISSION_H_ 

#define DEBUG

#include <iostream>
#include <cstring>

using std::string;

class mission{
    public:
        mission(int socketfd, int epfd);
        void process();
        ~mission();
    private:
        int epfd;
        int socketfd;
        int request_type;   // 请求类型
        string request_path;    //  需要读取的目标文件/路径
        bool request_path_exist;    //  目标文件/路径是否存在
        mission() {}
        int analysis();
        string getline();
        int analysis_request_type(string str);  // 得到请求类型
        string analysis_request_path(string str);   // 得到目标文件/路径
        bool path_exist(string path);   // 判断目标文件/路径是否存在
};

#endif // !_MISSION_H_
