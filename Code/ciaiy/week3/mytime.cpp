#include "mytime.h"
#include <iostream>

mytime::mytime()
{
    this->hours = 5;
    this->minuters = 5;
}

mytime::mytime(int hours, int minuters)
{
    this->hours = hours;
    this->minuters = minuters;
}

int mytime::getHours() const
{
    return this->hours;
}

int mytime::getMinuters() const
{
    return this->minuters;
}

void operator<<(std::ostream &os, const mytime &Time)
{
    os << Time.hours << ":" << Time.minuters;
}

mytime mytime::operator+(const mytime &otherTime) const
{
    int minuters = otherTime.minuters + this->minuters;
    int hours = otherTime.hours + this->hours;

    mytime sum = mytime(hours, minuters);

    return sum;
}

void mytime::showTime() const
{
    std::cout << hours << " h " << minuters << " min " << std::endl;
}

mytime::operator std::string() const
{
    std::cout << "string start " << std::endl;
    std::string str = std::to_string(this->hours) + ":" + std::to_string(this->minuters); 
    std::cout << "string ends : " << str << std::endl;

    return str;
}