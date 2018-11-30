#include <iostream>
#include "AB.h"

using std::cout;
using std::endl;

A::A(int a, int b) {
    cout << "this is A constructer function" << endl;
}

B::B(int a, int b) : A(a, b){
    cout << "this is B constructer function" << endl;
}