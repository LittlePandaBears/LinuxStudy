#include <iostream>
#include "thread_pool.h"
#include <unistd.h>

using std::endl;
using std::cout;

void *fun(void *arg) {
    cout << *(int*)arg << endl;
    sleep(10);
    return NULL;
}

int main(void) {
    thread_pool pool = thread_pool(10, fun);
    pool.start_all();
    for(int i = 0; i < 10; i++) {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        pool.add_task((void *)arg);
    }
    return 0;
}