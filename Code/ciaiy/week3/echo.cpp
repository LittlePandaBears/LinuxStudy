#include "echo.h"

echo::echo() {
    this->port = 1024;
}

echo::echo(int port) {
    this->port = port;
}

void echo::echoChat(std::string msg) {
    std::cout<<std::to_string(echo::port)+ ":" + msg <<std::endl;
    echo::chatNum++;
}