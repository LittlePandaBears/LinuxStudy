#include "mission.h"
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/socket.h>

using std::cout;
using std::endl;
using std::string;

#define ERROR_TYPE 0
#define GET_TYPE 1
#define POST_TYPE 2

mission::mission(int socketfd, int epfd)
{
    this->epfd = epfd;
    this->socketfd = socketfd;
}

mission::~mission() {
    struct epoll_event ev;
    ev.data.fd = socketfd;
    ev.events = EPOLL_CTL_DEL;
    epoll_ctl(epfd, EPOLL_CTL_DEL, socketfd, &ev);
}

void mission::process()
{
#ifdef DEBUG
    cout << socketfd << " processing" << endl;
#endif // DEBUG
    analysis();
}

int mission::analysis()
{
#ifdef DEBUG
    cout << "analysis begin" << endl << "getline begin" << endl;
#endif // DEBUG
    string firstline = getline();
    cout << firstline << "getline end" << endl;
    request_type = analysis_request_type(firstline);
    request_path = analysis_request_path(firstline);
    request_path_exist = path_exist(request_path);
#ifdef DEBUG
    cout << "request type : \"" << request_type << "\" request_path \"" << request_path << "\" exist ? " << path_exist(request_path) << endl;
#endif // DEBUG
    if (request_type == GET_TYPE)
    {
        char sendbuf[204800] = {0};
        if (request_path_exist)
        {
            sprintf(sendbuf, "HTTP/1.1 200 OK\r\nDate: Sat, 31 Dec 2005 23:59:59 GMT\r\nContent-Type: text/html;charset=ISO-8859-1\r\nContent-Length: 122\r\n\r\nTHE FIRST WEB SERVER!");
            int ret = write(socketfd, sendbuf, 204800);
            if (ret == -1)
            {
                cout << "err" << endl;
            }
#ifdef DEBUG
            cout << "analysis end" << endl;
#endif // DEBUG
            return 0;
        }
        else
        {
            sprintf(sendbuf, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html;charset=ISO-8859-1\r\nContent-Length: 122\r\n\r\n404 NOT FOUND!");
            int ret = write(socketfd, sendbuf, 204800);
            if (ret == -1)
            {
                cout << "err" << endl;
            }
#ifdef DEBUG
            cout << "analysis end" << endl;
#endif // DEBUG
            return 0;
        }
    }
    else
    {
        return -1;
    }
}

string mission::getline()
{
    char buf[256] = {0};
    char test_char;
    int index = 0;
    while (recv(socketfd, &test_char, 1, MSG_PEEK) > 0)
    {
        if (test_char == '\r')
        { // 如果是\r 则将\r\n去掉
            recv(socketfd, &test_char, 1, 0);
            recv(socketfd, &test_char, 1, 0);
            break;
        }
        else
        {
            recv(socketfd, buf + index, 1, 0);
            index++;
        }
    }
    return string(buf);
}

int mission::analysis_request_type(string str)
{
    if (str.find("GET") != string::npos)
    {
        cout << "GET" << endl;
        return GET_TYPE;
    }
    else if (str.find("POST") != string::npos)
    {
        cout << "POST" << endl;
        return POST_TYPE;
    }
    return ERROR_TYPE;
}

string mission::analysis_request_path(string str)
{
    int first_index = str.find_first_of('/');
    string path = "";

    for (int index = first_index; str.at(index) != ' ' && index < str.length(); index++)
    {
        path += str.at(index);
    }

    return path;
}

bool mission::path_exist(string path)
{
    struct stat s;
    return (stat(path.data(), &s) != -1);
}