#ifndef TREE_H
#define TREE_H
#include "public.h"

// 孩子兄弟表示法多叉树节点
typedef struct TreeNode
{
    char type[MAX_NAME];
    int star;
    int service_hours;
    struct TreeNode *child;
    struct TreeNode *brother;
} TreeNode;

// 函数声明
TreeNode* CreateRoot(char name[]);
void AddChild(TreeNode *parent, char childName[],int star,int hours);
TreeNode* FindNode(TreeNode *root, char name[]);
void PreOrderTraverse(TreeNode *root, int level);
int CountTotalHours(TreeNode *root);
void QueryByStar(TreeNode *root, int star_count);
void DestroyTree(TreeNode *root);

#endif