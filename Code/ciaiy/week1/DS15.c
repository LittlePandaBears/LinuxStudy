#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TREENODE, *PTREENODE, TREE, *PTREE;

void createTree(PTREE *tree);
void traverseTree(PTREE tree);
void delTree(PTREE *tree, char data);
void delTreeNode(PTREE *tree);

void delTreeNode(PTREE *tree) {
    if(*tree != NULL) {
        delTreeNode(&(*tree)->lchild);
        delTreeNode(&(*tree)->rchild);
        free(*tree);
        *tree = NULL;
    }
}


void delTree(PTREE *tree, char data) {
    if(*tree != NULL) {
        if((*tree)->data == data) {
            delTreeNode(tree);
        }else {
            delTree(&(*tree)->lchild, data);
            delTree(&(*tree)->rchild, data);
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

int main(void)
{
    PTREE tree;
    createTree(&tree);
    traverseTree(tree);
    printf("\n");
    delTree(&tree, 'B');
    traverseTree(tree);
    printf("\n");
    return 0;
}