#include "locker.h"

int main(void) {
    locker lock;
    lock.lock();
    lock.lock();
    lock.unlock();
    return 0;
}