#include <iostream>
#include "thread_pool2.h"

void *fun(void *arg) {

}

int main(void) {
    thread_pool2 pool = thread_pool2(fun);
    return 0;
}