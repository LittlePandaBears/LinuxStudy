#ifndef SORT_H_

#define SORT_H_

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class SORT {
    public : 
        enum{LIST_LEN = 10, SSS = 1, SIS = 2, BIS = 3, SS = 4};
        SORT();
        SORT(int list[]);
        void showList();
        void sort(int type);
    private :
        int list[LIST_LEN];
        void swap(int &a, int &b);
        void straightSelectSort();
        void straightInsertionSort();
        void binaryInsertionSort();
        int binarySearch(int len, int value);
        void shellSort();
};

#endif