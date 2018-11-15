#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#define FALSE 0 
#define TRUE !FALSE

jmp_buf toPrint;

static int RegularTree = TRUE;

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TREENODE, *PTREENODE, TREE, *PTREE;

void createTree(PTREE *tree);
void traverseTree(PTREE tree);
int judgeRegularTree(PTREE tree);

int judgeRegularTree(PTREE tree) {
    int lchildIsNULL = tree->lchild == NULL ? TRUE : FALSE;
    int rchildIsNULL = tree->rchild == NULL ? TRUE : FALSE;

    if(tree != NULL) {
        if(lchildIsNULL == FALSE || rchildIsNULL == FALSE) {
            if(lchildIsNULL != TRUE || rchildIsNULL != TRUE) {
                RegularTree = FALSE;
                return FALSE;
            }else {
                judgeRegularTree(tree->lchild);

                if(RegularTree == FALSE) {
                    judgeRegularTree(tree->rchild);
                }
            }
        }
    }
}

void traverseTree(PTREE tree) {
    if(tree != NULL) {
        printf("%c ", tree->data);
        traverseTree(tree->lchild);
        traverseTree(tree->rchild);
    }
}

void createTree(PTREE *tree) {
    char data;
    data = getchar();
    if(data != ' ') {
        (*tree) = (PTREE)malloc(sizeof(TREE));
        bzero(*tree, sizeof(TREE));
        (*tree)->data = data;
        createTree(&(*tree)->lchild);
        createTree(&(*tree)->rchild);
    }
}


int main(void) {
    PTREE tree;
    createTree(&tree);
    traverseTree(tree);
    printf("\n");
    judgeRegularTree(tree);
    printf("该树为%s\n", RegularTree == TRUE ? "正则二叉树" : "非正则二叉树");
    return 0;
}


void findPostNode(PTREE tree, char *data) {
    if(tree == NULL) {
        data = NULL;
    }

    while(tree != NULL) {
        if(tree->lchild != NULL) {
            tree = tree->lchild;
        }else if(tree->rchild != NULL) {
            tree = tree->rchild;
        }
    }

    *data = tree->data;
}

void findNearestFatherNode(PTREE tree, int indexA, int indexB, char *data) {
    while(indexA != indexB) {
        if(indexA > indexB) {
            indexA /= 2;
        }else {
            indexB /= 2;
        }

        *data = tree->treeNode[indexA - 1];
    } 
}