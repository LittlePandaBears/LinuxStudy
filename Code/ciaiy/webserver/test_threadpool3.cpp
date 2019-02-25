#include "thread_pool3.h"
#include "test.h"
#include <unistd.h>

int main(void) {
    thread_pool<test> tp = thread_pool<test>(10);
    cout<<"!!"<<endl;
    test *t = new test();
    for(int i = 0; i < 10; i++) {
        cout<<i<<endl;
        tp.add_task(t);
    }
    sleep(100);
}