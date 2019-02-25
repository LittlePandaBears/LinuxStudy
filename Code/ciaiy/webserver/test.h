#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class test{
    public :
        void process() {
            cout << "测试" << endl;
            sleep(1);
        }
};
