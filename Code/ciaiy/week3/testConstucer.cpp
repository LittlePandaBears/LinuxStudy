#include "constucter.h"

int main(void) {
    constucter cons = constucter();
    constucter test = cons.returnType1();
    std::cout << test.name << std::endl;
    return 0;
}