#include "constucter.h"
#include <iostream>

constucter::constucter() {
    std::cout << "()构造函数" << std::endl;
    this->name = "default";
}

constucter::constucter(std::string name) {
    this->name = name;
}

constucter::~constucter() {
    std::cout << this->name << "has delete" << std::endl;
}

void constucter::getOtherObjectPrivateValue(const constucter &otherObject) const {
    int val = otherObject.pri_val;
    std::cout << val << std::endl;
}

constucter constucter::returnType1() {
    constucter ret = constucter("return constucter");
    return ret;
}

