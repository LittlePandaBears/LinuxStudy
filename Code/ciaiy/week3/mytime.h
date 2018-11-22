#ifndef MYTIME_H_
#define MYTIME_H_

#include <iostream>

class mytime
{
    public:
        mytime();
        mytime(int hours, int minutes);
        mytime operator+(const mytime &data) const;
        friend void operator<<(std::ostream &os, const mytime &Time);
        int getHours();
        int getMinuters();
        void showTime();
        void testFun(const mytime &timeOther);
    private:
        int hours;
        int minuters;
};

#endif // !MYTIME_H_
