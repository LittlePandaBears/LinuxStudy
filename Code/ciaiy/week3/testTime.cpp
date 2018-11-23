#include "mytime.h"
#include <iostream>
#include <unistd.h>

int main(void)
{
    mytime time1 = mytime(1, 2);
    mytime time2 = mytime(3, 4);
    mytime sum = time1 + time2;

    std::string str = sum;
    std::cout << str << std::endl;
    

    return 0;
}