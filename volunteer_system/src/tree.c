#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "tree.h"

void my_StrCpy(char *dest, char *src)
{
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// 创建根节点
TreeNode* CreateRoot(char name[])
{
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    my_strcpy(root->type, name);
    root->child = NULL;
    root->brother = NULL;
    return root;
}

// 给父节点添加子节点
void AddChild(TreeNode *parent, char childName[])
{
    if(parent == NULL) return;
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    my_strcpy(newNode->type, childName);
    newNode->child = NULL;
    newNode->brother = NULL;

    if(parent->child == NULL)
    {
        parent->child = newNode;
    }
    else
    {
        TreeNode *p = parent->child;
        while(p->brother != NULL)
            p = p->brother;
        p->brother = newNode;
    }
}

// 先序遍历整棵树
void PreOrderTraverse(TreeNode *root)
{
    if(root == NULL) return;
    printf("项目分类：%s\n", root->type);
    PreOrderTraverse(root->child);
    PreOrderTraverse(root->brother);
}

// 递归销毁树，释放内存
void DestroyTree(TreeNode *root)
{
    if(root == NULL) return;
    DestroyTree(root->child);
    DestroyTree(root->brother);
    free(root);
}