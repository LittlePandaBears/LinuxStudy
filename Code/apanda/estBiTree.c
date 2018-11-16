/*前序建立二叉树并用前序,中序,后序输出二叉树*/

#include<stdio.h>
#include<stdlib.h>

int LeafCount = 0, depth = 0, h = 1;

typedef struct Node{
  int date;
  struct Node *LChild, *RChild;
}TreeNode,*PTree;

/*1.前序建树*/
void estTree(PTree *p){
  int e;
  scanf("%d",&e);
  if(e == 0)
    *p = NULL;
  else {
    *p = (PTree)malloc(sizeof(TreeNode));
    (*p)->date = e;
    printf("输入%d左子树\n",e);
    estTree(&((*p)->LChild));
    printf("输入%d右子树\n",e);
    estTree(&((*p)->RChild));
  }
}

/*2.1前序遍历*/
void PreOrderPrintTree(PTree p){
  if(p != NULL){
    printf("%d ",p->date);
    PreOrderPrintTree(p->LChild);
    PreOrderPrintTree(p->RChild);}
}

/*2.2中序遍历*/
void InOrderPrintTree(PTree p){
  if(p != NULL){
    InOrderPrintTree(p->LChild);
    printf("%d ",p->date);
    InOrderPrintTree(p->RChild);}
}

/*2.3后序遍历*/
void PostOrderPrintTree(PTree p){
  if(p != NULL){
    PostOrderPrintTree(p->LChild);
    PostOrderPrintTree(p->RChild);
    printf("%d ",p->date);}
}

/*3.输出叶子点*/
void PrintLeafNode(PTree p){
  if(p != NULL){
    if(p->LChild == NULL && p->RChild == NULL)
      printf("%d ",p->date);
    PrintLeafNode(p->LChild);
    PrintLeafNode(p->RChild);
  }
}

/*4.1前序遍历输出叶子点的个数(全局变量法)*/
void LeafCount1(PTree p){
  if(p != NULL){
    if(p->LChild == NULL && p->RChild == NULL)
      LeafCount++;
    LeafCount1(p->LChild);
    LeafCount1(p->RChild);
  }
}

/*4.2后序遍历输出叶子点的个数(分治算法:叶子树是左右子树的叶子数目之和)*/
int LeafCount2(PTree p){
  int LeafCount;
  if(p == NULL)
    LeafCount = 0;
  else if(p->LChild == NULL && p->RChild == NULL)
    LeafCount = 1;
  else
    LeafCount = LeafCount2(p->LChild) + LeafCount2(p->RChild);
  return LeafCount;
}

/*5.1后序遍历求树的高度(本层根高度1 加上 左右子树的最大高度)*/
int PostTreeDepth(PTree p){
  int hl, hr, max;
  if(p == NULL)
    return 0;
  else {
    hl = PostTreeDepth(p->LChild);
    hr = PostTreeDepth(p->RChild);
    max = hl>hr?hl:hr;
    return (max+1);
  }
}

/*5.2前序遍历求树的高度(每进一层高度加一)*/
void PreTreeDepth(PTree p, int h){
  if(p != NULL){
    if(h > depth)
      depth = h;
    PreTreeDepth(p->LChild, h+1);
    PreTreeDepth(p->RChild, h+1);
  }
}

/*6.1树状打印二叉树(横打)*/
void PrintTree(PTree p, int h){
  if(p != NULL){
    PrintTree(p->RChild, h+1);
    for(int i = 0; i < h; i++)
      printf(" ");
    printf("%d\n",p->date);
    PrintTree(p->LChild, h+1);
  }
}

/*主函数*/   
void main(){
  PTree bt;
  estTree(&bt);
  printf("前序:");
  PreOrderPrintTree(bt);
  printf("\n");
  printf("中序:");
  InOrderPrintTree(bt);
  printf("\n");
  printf("后序:");
  PostOrderPrintTree(bt);
  printf("\n");
  printf("Leaf:");
  PrintLeafNode(bt);
  printf("\n");
  LeafCount1(bt);
  printf("LeafCount = %d\n",LeafCount);
  int leafcount = LeafCount2(bt);
  printf("LeafCount = %d\n",leafcount);
  int depth1 = PostTreeDepth(bt);
  printf("depth = %d\n",depth1);
  PreTreeDepth(bt, h);
  printf("depth = %d\n",depth);
  h = 1;
  PrintTree(bt, h);
  printf("\n");
}
