#include "sort.h"
#include <cstdlib>
#include <cstring>


SORT::SORT() {
    srand(time(0));
    for(int i = 0; i < LIST_LEN; i++) {
        list[i] = rand() % LIST_LEN;
    }
    setMap(list);
}

SORT::SORT(int list[]) {
    memcpy(list, this->list, sizeof(int) * LIST_LEN);
    setMap(list);
}

void SORT::randList() {

    for(int i = 0; i < LIST_LEN; i++) {
        list[i] = rand() % LIST_LEN;
    }
    setMap(list);
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
    if(type == BS) {
        bubbleSort();
    } 
    if(type == FS) {
        fastSort(0, LIST_LEN - 1);
    }
    if(type == MS) {
        mergeSort(0, LIST_LEN);
    }
    if(type == HS) {
        heapSort(LIST_LEN);
    }
}

void SORT::initHeap(int len) {
    bool flag = true;
    while(flag) {
        for(int i = len - 1; i >= 1 ; i--) {
            int parentIndex = (i + 1) / 2 - 1;
            if(list[i] > list[parentIndex]) {
                swap(list[i], list[parentIndex]);
                break;
            }

            if(i == 1 && list[1] <= list[0]) {
                flag = false;
            }
        }
    }
}

void SORT::heapSort(int len) {
    if(len == 1) {
        return ;
    }
    initHeap(len);
    swap(list[len - 1], list[0]);
    heapSort(len - 1);
}

void SORT::fastSort(int start, int end) {
    int key = list[start];
    int lindex = start;
    int rindex = end;
    int temp = list[lindex];

    if(lindex >= rindex) {
        return;
    }
    
    while(lindex != rindex) {
        while(list[rindex] >= key && lindex < rindex) {
            rindex--;
        }
        if(rindex > lindex) {
            list[lindex] = list[rindex];
        }
        while(list[lindex] <= key && lindex < rindex) {
            lindex++;
        }
        if(lindex < rindex) {
            list[rindex] = list[lindex];
        }
    }
    list[lindex] = temp;
    fastSort(start, lindex - 1);
    fastSort(lindex + 1, end);
}


void SORT::setMap(int list[]) {
    for(int i = 0; i < LIST_LEN; i++) {
        keyValue[i] = 0;
    }

    for(int i = 0; i < LIST_LEN; i++) {
        keyValue[list[i]]++;
    }  
}

bool SORT::check() {
    map<int, int> temp;
    int value = list[0];
    for(int i = 0; i < LIST_LEN; i++) {
        temp[list[i]]++;
    }  
    
    for(int i = 0; i < LIST_LEN; i++) {
        int key1 = keyValue[i];
        int key2 = temp[i];
        if(key1 != key2) {
            cout << "flag 1" << key1 << " " << key2<< endl;
            return false;
        }
    }

    for(int i = 0; i > LIST_LEN; i++) {
        if(list[i] > value) {
            value = list[i];
        }else if(value > list[i]) {
            cout << "flag 2" << endl;
            return false;
        }
    }
    return true;
}

void SORT::mergeSort(int begin, int end)
{
    if (end-begin < 2) return;
    int mid = (begin+end)/2;
    mergeSort(begin,mid);
    mergeSort(mid,end);
    mergeSortCore(begin,mid,end);
}

void SORT::mergeSortCore(int begin, int mid, int end) {
    int i=begin, j=mid, k=0;
    int *temp = new int[end-begin];
    for(; i<mid && j<end; temp[k++]=(list[i]<list[j]?list[i++]:list[j++]));
    for(; i<mid; temp[k++]=list[i++]);
    for(; j<end; temp[k++]=list[j++]);
    for(i=begin, k=0; i<end; list[i++]=temp[k++]);
    free(temp);
}

void SORT::bubbleSort() {
    for(int i = LIST_LEN - 1; i >= 0; i--) { 
        for(int j = 0; j < i; j++) {
            if(list[j] > list[j + 1]) {
                swap(list[j], list[j + 1]);
            }
        }
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

    for(int i = 2; i < LIST_LEN; i++) {
            
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
                index = i;
                temp = list[i];
                for(int j = i - increment; j >= 0; j -= increment) {
                    if(list[j] > temp) {
                        list[j + increment] = list[j];
                        index = j;
                    }
                }
                list[index] = temp;
            }
        }
    }
}
