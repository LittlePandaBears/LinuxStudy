#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int i=1;
typedef struct Node
{
	int num;
	char data;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode,*BiTree;
void CreateTree(BiTree*p)
{
	
	char ch;
	ch=getchar();
	if(ch=='#') *p=NULL;
	else
	{
		*p=(BiTree)malloc(sizeof(BiTNode));
		(*p)->data=ch;
		CreateTree(&((*p)->LChild));	
		CreateTree(&((*p)->RChild));
	}	
}/*
void changenum(Tree p)
{
	
	if(p!=NULL)
	{
		changenum(p->LChild);
		changenum(p->RChild);
		p->num=i;
		i++;
	}
}*/
void showtree(BiTree p,int l)
{
	if(p==NULL)return;
	else
	{
		showtree(p->RChild,l+1);
		for(int i=1;i<=l;i++)
		printf(" ");
		printf("%c\n",p->data);
		showtree(p->LChild,l+1);
	}
}
int main()
{
	BiTree*p;
	CreateTree(p);
	showtree(*p, 1);
	return 0;
}
