#include "sort.h"
#include <cstdlib>
#include <cstring>

SORT::SORT() {
    srand(time(0));
    for(int i = 0; i < LIST_LEN; i++) {
        list[i] = rand() % LIST_LEN;
    }
}

SORT::SORT(int list[]) {
    memcpy(list, this->list, sizeof(int) * LIST_LEN);
}

void SORT::showList() {
    for(int i  = 0; i < LIST_LEN; i++) {
        cout<<list[i]<< " ";
    }
    cout<<endl;
}

void SORT::sort(int type) {
    if(type == SSS) {
        straightSelectSort();
    }
    if(type == SIS) {
        straightInsertionSort();
    }
    if(type == BIS) {
        binaryInsertionSort();
    }
}

int binarySearch(int list[], int len, int value) {
    int rindex = len;
    int lindex = 0;
    while(rindex != lindex) {
        int mid = (rindex + lindex) / 2;
        if(list[mid] > value) {
            lindex = 0;
            rindex = mid;
        }else if(list[mid] < value) {
            lindex = mid + 1;
            rindex = len;
        }else {
            return mid;
        }
    }
    return lindex;
}

void SORT::binaryInsertionSort() {
    for(int i = 2; i < LIST_LEN - 1; i++) {
        for(int j = i - 1; j >= 1; j--) {
            binarySearch(list, i, list[j]);
        }
    }
}

void SORT::straightInsertionSort() {
    int tempList[LIST_LEN + 1] = {0};
    memcpy(tempList + 1, list, sizeof(int) * LIST_LEN);

    for(int i = 2; i < LIST_LEN + 1; i++) {
        // i - 1 为已排好序的数列的元素个数
        int index = i;
        tempList[0] = tempList[i];
        
        for(int j = i - 1; j >= 1; j--) {
            if(tempList[j] > tempList[0]) {
                index = j;
                tempList[j+1] = tempList[j];
            }
        }
        
        tempList[index] = tempList[0];
    }

    memcpy(list, tempList + 1, sizeof(int) * LIST_LEN);
}

void SORT::straightSelectSort() {
    for(int i = 0 ; i < LIST_LEN - 2; i++) {
        for(int j = i + 1; j < LIST_LEN - 1; j++) {
            if(list[i] > list[j]) {
                swap(list[i], list[j]);
            }
        }
    }
}

void SORT::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int bubbleSort() {
    for(int i = LIST_LEN - 1; i >= 0; i--) {
        for(int j = LIST_LEN - 1; j >= i; j--) {
            if(xxx) {
                swap;
            }
        }
    }
}