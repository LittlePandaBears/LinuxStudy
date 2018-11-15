#include <stdio.h>

double f(int i) {
    return 1.0 / i;
}

int main(void) {
    double a,b;

    int i;
    a = f(10);
    b = f(10);
    // c = f(10);
    i = a==b;
    printf("%d\n", i);


    return 0;
}