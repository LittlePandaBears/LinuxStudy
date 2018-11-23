#include "constucter.h"
#include <iostream>

constucter::constucter() {
    std::cout << "()构造函数" << std::endl;
}

constucter::~constucter() {
    
}

void constucter::getOtherObjectPrivateValue(const constucter &otherObject) const {
    int val = otherObject.pri_val;
    std::cout << val << std::endl;
}
