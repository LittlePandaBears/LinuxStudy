
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *child;
    struct TreeNode *brother;
} TREENODE, *PTREENODE, TREE, *PTREE;

void createTree(PTREE *tree);
void traverseTree(PTREE tree);
int treeHeight(PTREE tree, int height);

int treeHeight(PTREE tree, int height)
{
    int brotherHeight = 0;

    if (tree->child != NULL) 
    {
        height = treeHeight(tree->child, height + 1);
    }
    if (tree->brother != NULL && height < (brotherHeight = treeHeight(tree->brother, height)))
    {
        height = brotherHeight;
    }
    return height;
}

void traverseTree(PTREE tree)
{
    if (tree != NULL)
    {
        printf("%c ", tree->data);
        traverseTree(tree->child);
        traverseTree(tree->brother);
    }
}

void createTree(PTREE *tree)
{
    char data;
    data = getchar();
    if (data != ' ')
    {
        (*tree) = (PTREE)malloc(sizeof(TREE));
        bzero(*tree, sizeof(TREE));
        (*tree)->data = data;
        createTree(&(*tree)->child);
        createTree(&(*tree)->brother);
    }
}

int main(void)
{
    PTREE tree;
    createTree(&tree);
    traverseTree(tree);
    printf("\n height : %d\n", treeHeight(tree, 0));

    return 0;
}