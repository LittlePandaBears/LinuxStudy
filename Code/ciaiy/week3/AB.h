#ifndef AB_H_
#define AB_H_

#include <iostream>

class A {
    public : 
        A() {};
        ~A() {};
        virtual void Fun() {
            std::cout << "这是A类" << std::endl;
        }
};

class B : public A {
    public :
        B() {};
        ~B() {};
        void Fun() {
            std::cout << "这是B类" << std::endl;
        }
};

#endif