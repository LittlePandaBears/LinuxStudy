#include "sort.h"

int main(void) {
    SORT s;
    s.showList();
    s.sort(2);
    s.showList();
    s.sort(3);
    return 0;
}