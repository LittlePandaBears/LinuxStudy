#ifndef ECHO_H_
#define ECHO_H_

#include <iostream>

class echo
{
  public:
    echo();
    echo(int port);
    void echoChat(std::string msg);

  private:
    int port;
    std::string clientname;
    int chatNum;
};

#endif // !ECHO_H_#define ECHO_H_
