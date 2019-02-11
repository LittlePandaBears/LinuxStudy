#include <pthread.h>
int main(void) {
    pthread_mutex_t x;
    pthread_mutex_init(&x, NULL);
    return 0;
}