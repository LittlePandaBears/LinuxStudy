#ifndef CD_H_
#define CD_H_

#include <iostream>

using std::cout;
using std::endl;

class C {
  public:
    C() {
        cout << "imC , hi" << endl;
    }

    ~C() {
        cout << "im C, bye" << endl;
    }
};

class D : public C {
  public:
    D() {
        cout << "im D, hi" << endl;
    }
    
    ~D() {
        cout << "im D, bye" << endl;
    }
};

#endif