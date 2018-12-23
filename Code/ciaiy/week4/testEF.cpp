#include "EF.h"
#include <iostream>

int main(void) {
    E a(111);
    E b(222);
    E &c = a + b;
    c.show();
    a.show();
    c.modify(1234);
    a.show();
    c.show();
}