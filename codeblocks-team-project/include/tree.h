#ifndef TREE_H
#define TREE_H
#include "public.h"
#include "mystring.h"

// 孩子兄弟表示法多叉树节点
typedef struct TreeNode
{
    char type[MAX_NAME];
    struct TreeNode *child;
    struct TreeNode *brother;
} TreeNode;

// 函数声明
TreeNode* CreateRoot(char name[]);
void AddChild(TreeNode *parent, char childName[]);
TreeNode* FindNode(TreeNode *root,char name[]);
void ModifyNode(TreeNode *root,char oldName[],char newName[]);
void DeleteChild(TreeNode *parent,char delName[]);
void PreOrderTraverse(TreeNode *root);
void DestroyTree(TreeNode *root);

#endif