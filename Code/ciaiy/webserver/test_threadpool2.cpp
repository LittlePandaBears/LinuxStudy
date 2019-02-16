#include <iostream>
#include "thread_pool2.h"
#include <unistd.h>

using std::cout;
using std::endl;

void *fun(void *arg) {
    cout <<"xx" << *(int *)arg<<endl;
    sleep(1);
    return NULL;
}

int main(void) {
    thread_pool2 pool = thread_pool2(fun);
    sleep(1);
    for(int i = 0; i< 5; i++) {
        int *num = new int(i);
        pool.add_task((void *)num);
    }
    sleep(100);
    return 0;
}