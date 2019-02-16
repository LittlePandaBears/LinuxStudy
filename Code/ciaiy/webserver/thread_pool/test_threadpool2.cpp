#include <iostream>
#include "thread_pool2.h"
#include <unistd.h>

using std::cout;
using std::endl;

void *fun(void *arg) {
    cout <<*(int *)arg<<endl;
    return NULL;
}

int main(void) {
    thread_pool2 pool = thread_pool2(fun);
    for(int i = 0; i<10; i++) {
        int *num = new int(i);
        cout<<"loop" << i<<endl;
        pool.add_task((void *)num);
    }
    sleep(100);
    return 0;
}