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
    if(type == SS) {
        shellSort();
    }
}

int SORT::binarySearch(int len, int value) {
    int rindex = len;
    int lindex = 0;
    while(rindex >= lindex) {
        int mid = lindex + (rindex - lindex) / 2;
        if(list[mid] > value) {
            rindex = mid - 1;
        }else if(list[mid] <= value) {
            lindex = mid + 1;
        }
    }
    return lindex;
}

void SORT::binaryInsertionSort() {
    if(list[0] > list[1]) {
        swap(list[0], list[1]);
    }

    for(int i = 2; i < LIST_LEN + 1; i++) {
            
            // find
            int index = binarySearch(i - 1, list[i]);

            // move
            int temp = list[i];
            for(int j = i; j > index; j--) {
                list[j] = list[j - 1];
            }
            list[index] = temp;
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

void SORT::shellSort() {
    bool Last = true;
    int index;
    int temp = 0;

    for(int increment = LIST_LEN / 3 + 1; Last == true; increment = 1 + increment / 3) {
        if(increment == 1) {
            Last = false;
        }

        for(int len = 0; len < increment; len ++) {
            for(int i = len + increment; i < LIST_LEN; i += increment) {
                // cout << "i = " << i << endl;
                index = i;
                temp = list[i];
                for(int j = i - increment; j >= 0; j -= increment) {
                    if(list[j] > temp) {
                        list[j + increment] = list[j];
                        index = j;
                    }
                }

                list[index] = temp;
                // // debug
                // for(int x = len; x <= i; x += increment) {
                //     cout << list[x] << " ";
                // }
                // cout<<endl;
            }

            // // debug
            // cout << "doing increment : " << increment << ":";
            // showList();
        }
        


        for(int i = 0; i < LIST_LEN; i++) {

        }
    }
}
