#include "CD.h"
#include <iostream>

using std::cout;
using std::endl;

C::C() {

}

C::~C() {

}

C::C(int a, int b) {
    this->a = a;
    this->b = b;
}

void C::showData() {
    cout << this->a << this->b << endl;
}

void C::Fun() {
    cout << "no param fun" << endl;
}

void C::Fun(int i) {
    cout << "int :" << i << "fun" << endl;
}

void C::Fun(char ch) {
    cout << "char :" << ch << "fun" << endl;
}

D::D() {

}

D::~D() {

}

D::D(int a, int b) : C(a, b) {

}

int D::Fun(int d) {
    cout << "double :" << d << "fun" << endl;
    return d;
}