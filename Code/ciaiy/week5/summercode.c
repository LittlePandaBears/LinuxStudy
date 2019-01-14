#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define NUMBER_OF_RECORD 10

long CompareTime = 0;
long MoveTime = 0;

void GetRecord(int Record[])
{
    //	srand((unsigned int)time(NULL));
    int i;
    for (i = 1; i <= NUMBER_OF_RECORD; i++)
    {
        Record[i] = rand();
    }
}

void PrintRecord(int r[])
{
    int i;
    for (i = 1; i <= NUMBER_OF_RECORD; i++)
    {
        printf("%d ", r[i]);
        if (i % 20 == 0)
        {
            printf("\n");
        }
    }
}

void Merge(int r1[], int low, int mid, int high, int r2[])
{
    int i = low, j = mid + 1, k = low;
    while ((i <= mid) && (j <= high))
    {
        if (r1[i] <= r1[j])
        {
            r2[k] = r1[i];
            i++;
        }
        else
        {
            r2[k] = r1[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        r2[k] = r1[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        r2[k] = r1[j];
        k++;
        j++;
    }
}

void MSort(int source[], int low, int high, int target[])
{
    int *temp = NULL;
    printf("start : %d %d\n", low, high);
    temp = (int *)malloc(sizeof(int) * (high - low + 1));
    
    if (low == high)
    {
        printf("low = high start\n");
        target[low] = source[low];
        printf("low = high end\n");
    }
    else
    {
        int mid = (low + high) / 2;
        printf("msort 1 start \n");
        MSort(source, low, mid, temp);
        MSort(source, mid + 1, high, temp);
        printf("msort part end\n");
        Merge(temp, low, mid, high, target);
    }
    
    if(temp != NULL) {
    free(temp);
    }
    printf("end fun");
}

void MergeSort(int r[], int n)
{
    MSort(r, 1, n, r);
}

int main()
{
    int r[NUMBER_OF_RECORD + 1];
    GetRecord(r);
    PrintRecord(r);
    printf("\n");
    printf("\n");
    MergeSort(r, NUMBER_OF_RECORD);
    PrintRecord(r);
    printf("\n\n比较次数： %d\n移动次数： %d\n", CompareTime, MoveTime);
    return 0;
}
