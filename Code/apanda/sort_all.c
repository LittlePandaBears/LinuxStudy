#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define     MAX      100   //用于控制产生的随机数的个数, 可直接修改, 默认设置为100
#define     FALSE    0
#define     TRUE     1

/*产生随机数, 范围：0~20000, 个数：20000个 */
void produce_random_number(int number[]) {
  int i;
  
  srand(1);
  for(i = 0; i < MAX; i++) {
    number[i] = rand() % (MAX);
  }
}

/*求希尔排序法中数组delta的长度*/
int length_delta(int len) {
  int i;

  for(i = 0; pow(2, i) < len; i++);
  return i-1;
}
    
/*输出数组(包含下标为0的元素)*/
void show_array(int number[]) {
  int i;
  
  for(i = 0; i < MAX; i++) {
    printf("%d ", number[i]);
  }
  printf("\n");
}

/*输出数组(不包含下标为0的元素)*/
void show_array_noZero(int number[]) {
  int i;
  
  for(i = 1; i < MAX; i++) {
    printf("%d ", number[i]);
  }
  printf("\n");
}
/*冒泡排序法*/
void maopao_sort(int number[]) {
  int i, j, temp;

  for(i = 0; i < MAX-1; i++) {
    for(j = 0; j < MAX-1-i; j++) {
      if(number[j] > number[j+1]) {
	temp = number[j];
	number[j] = number[j+1];
	number[j+1] = temp;
      }
    }
  }
}

/*选择排序法*/
void select_sort(int number[]) {
  int i, j, temp;
  
  for(i = 0; i < MAX-1; i++) {
    for(j = i+1; j < MAX; j++) {
      if(number[i] > number[j]) {
	temp = number[i];
	number[i] = number[j];
	number[j] = temp;
      }
    }
  }
}

/*插入排序*/
void insert_sort(int number[]) {    //将 number[0] 当做无用数据, 不算作待排序元素
  int i, j, length;

  length = MAX - 1;                 //length 是数组中待排序元素的个数
  for(i = 2; i <= length; i++) {
    number[0] = number[i];          //将 number[i] 设置成监视哨 
    j = i - 1;
    while(number[j] > number[0]) {
      number[j+1] = number[j];
      j--;
    }
    number[j+1] = number[0];
  }
}

/*折半插入排序*/
void half_insert_sort(int number[]) {
  int i, j, x, low, high, mid;

  for(i = 1; i < MAX; i++) {
    x = number[i];
    low = 0;
    high = i - 1;
    while(low < high) {
      mid = (low + high) / 2;
      if(x < number[mid])
	high = mid - 1;
      else
	low = mid + 1;
    }
    for(j = i-1; j >= low; j--) {
      number[j+1] = number[j];
    }
    number[low] = x;
  }
}

/*一趟快速排序法*/
int quick_pass(int number[], int low, int high) {
  int x;
  
  x = number[low];
  while(low < high) {
    while(low < high && number[high] >= x) {
      high--;
    }
    if(low < high) {
      number[low] = number[high];
      low++;
    }
    while(low < high && number[low] < x) {
      low++;
    }
    if(low < high) {
      number[high] = number[low];
      high--;
    }
  }
  number[low] = x;
  return low;
}

/*完整快速排序法*/
void quick_sort(int number[], int low, int high) {      //对数组number[low, high]用快速排序法进行排序
  int pos;
  if(low < high) {
    pos = quick_pass(number, low, high);                //调用一次快速排序, 以枢轴元素为界, 划分成两个子表, 并得到枢轴元素的下标
    quick_sort(number, low, pos-1);
    quick_sort(number, pos+1, high);
  }
}

/*一趟希尔排序*/
void shell_pass(int number[], int length, int delta) {  //将 number[0] 当做无用数据, 不算作待排序元素
  int i, j;

  for(i = 1+delta; i <= length; i++) {
    if(number[i] < number[i-delta]) {
      number[0] = number[i];                            //备份待插入元素number[i], (不做监视哨)
      for(j = i-delta; j > 0 && number[0] < number[j]; j -= delta) {
	number[j+delta] = number[j];
      }
      number[j+delta] = number[0];
    }
  }
}

/*希尔排序*/
void shell_sort(int number[], int length, int delta[], int n) {
  int i;
  
  for(i = 0; i <= n-1; i++) {
    shell_pass(number, length, delta[i]);
  }
}

/*重建堆算法*/
void sift(int number[], int k, int m) {                 //调整数组number[k..m], 使之成为大根堆
  int i, j, x, finished;

  x = number[k];
  i = k;
  j = 2 * i;
  finished = FALSE;
  while(j <= m && !finished) {
    if(j + 1 <= m && number[j+1] > number[j])           //如果结点number[i]的右分支存在, 且右分支比左分支大, 则沿右分支筛选
      j = j + 1;
    if(x > number[j])      //筛选完毕
      finished = TRUE;
    else {                         
      number[i] = number[j];
      i = j;
      j = 2 * i;
    }                      //继续筛选
  }
  number[i] = x;           //将number[k]填到适当的位置
}

/*建初堆算法*/
void create_heap(int number[], int n) {          //n为数组的长度
  int i;
  
  for(i = n / 2; i >= 1; i--) {                  // n/2 处是最后一个非叶子点
    sift(number, i, n);
  }
}

/*堆排序算法*/
void heap_sort(int number[], int n) {           //n是数组的长度
  int i, temp;
  
  create_heap(number, n);
  for(i = n; i >= 2; i--) {
    temp = number[1];                           //将堆顶记录与堆尾记录交换
    number[1] = number[i];
    number[i] = temp;
    sift(number, 1, i-1);                       //将数组剩下的元素重新调整为大根堆
  }
}

/*相邻两个有序子序列合并算法*/
void merge(int number[], int low, int mid, int high, int temp[]) {
  int i = low, j = mid + 1, k = 0;             //i, j, k分别是number[low..mid], number[mid+1..high], temp[low..high]数组的计数器
  while(i <= mid && j <= high) {
    if(number[i] <= number[j]) 
      temp[k++] = number[i++];
    else
      temp[k++] = number[j++];
  }
  
  while(i <= mid)
    temp[k++] = number[i++];
  
  while(j <= high)
    temp[k++] = number[j++];
  
  for(i = 0; i < k; i++)
    number[low + i] = temp[i];
}

/*2-路归并递归算法*/
void mergeSort(int number[], int low, int high, int temp[]) {
  if(low < high) {
    int mid = (low + high) / 2;
    mergeSort(number, low, mid, temp);         //左边有序
    mergeSort(number, mid + 1, high, temp);    //右边有序
    merge(number, low, mid, high, temp);       //再将两个有序数列合并
  }
}

/*调用2-路递归算法*/
void merge_sort(int number[], int length) {    //length是number数组的长度
  int *temp = (int *)malloc(sizeof(int) * length);
  
  if(temp != NULL)
    mergeSort(number, 0, length - 1, temp);
  else
    printf("malloc failed!\n");
  free(temp);
}

/*主函数 (删除注释, 即可调用对应的排序方法)*/
void main() {   
  int number[MAX];

  /*1.冒泡排序*/
  produce_random_number(number);      
  show_array(number);
  maopao_sort(number);                 
  printf("maopao_sort:\n");
  show_array(number);

  /*2.选择排序*/
  /*produce_random_number(number);      
  show_array(number);
  select_sort(number);               
  printf("select_sort:\n");
  show_array(number);*/
  
  /*3.插入排序*/
  /*produce_random_number(number);      
  show_array_noZero(number);
  insert_sort(number);                 
  printf("insert_sort:\n");
  show_array_noZero(number);*/
  
  /*4.折半插入排序*/
  /*produce_random_number(number);      
  show_array(number);
  half_insert_sort(number);            
  printf("half_insert_sort:\n");
  show_array(number);*/

  /*5.快速排序*/
  /*produce_random_number(number);      
  show_array(number);
  quick_sort(number, 0, MAX-1);       
  printf("quick_sort:\n");
  show_array(number);*/

  /*6.希尔排序*/
  /*produce_random_number(number);      
  show_array_noZero(number);
  int n = length_delta(MAX);
  int delta[n];
  int temp = MAX;
  for(i = 0; i < n; i++) {   //生成delta数组
    delta[i] = temp / 2;
    temp = temp / 2;
  }
  shell_sort(number, MAX-1, delta, n);
  printf("shell_sort:\n");
  show_array_noZero(number);*/

  /*7.堆排序*/
  /*produce_random_number(number);      
  show_array_noZero(number);
  heap_sort(number, MAX - 1);          
  printf("heap_sort:\n");
  show_array_noZero(number);*/

  /*8.归并排序*/
  /*produce_random_number(number);      
  show_array(number);
  merge_sort(number, MAX);          
  printf("merge_sort:\n");
  show_array(number);*/
}
