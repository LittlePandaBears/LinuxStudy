#ifndef SORT_H_

#define SORT_H_

#include <iostream>
#include <map>

/*


*/

using std::cout;
using std::endl;
using std::cin;
using std::map;

class SORT {
    public : 
        enum{LIST_LEN = 10, SSS = 1, SIS = 2, BIS = 3, SS = 4, BS = 5, MS = 6, FS = 7, HS = 8};
        SORT();
        SORT(int list[]);
        void showList();
        void sort(int type);
        bool check();
        void randList();
    private :
        int list[LIST_LEN];
        map<int, int> keyValue;
        void swap(int &a, int &b);
        void straightSelectSort();
        void straightInsertionSort();
        void binaryInsertionSort();
        int binarySearch(int len, int value);
        void shellSort();
        void bubbleSort();
        void mergeSort(int begin, int end);
        void mergeSortCore(int begin, int mid, int end);
        void setMap(int list[]);
        void fastSort(int start, int end);
        void heapSort(int len);
        void initHeap(int len);
};

#endif