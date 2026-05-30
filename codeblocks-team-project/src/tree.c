#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "tree.h"

// 创建根节点
TreeNode* CreateRoot(char name[])
{
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL)
        return NULL;
    my_strcpy(root->type, name);
    root->child = NULL;
    root->brother = NULL;
    return root;
}

// 给父节点添加子节点
void AddChild(TreeNode *parent, char childName[])
{
    if (parent == NULL)
        return;
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    my_strcpy(newNode->type, childName);
    newNode->child = NULL;
    newNode->brother = NULL;

    // 父节点暂无孩子，直接作为第一个孩子
    if (parent->child == NULL)
    {
        parent->child = newNode;
    }
    else
    {
        // 找到最后一个兄弟，挂在后面
        TreeNode *p = parent->child;
        while (p->brother != NULL)
        {
            p = p->brother;
        }
        p->brother = newNode;
    }
}

// 递归查找指定名称节点
TreeNode* FindNode(TreeNode *root, char name[])
{
    if (root == NULL)
        return NULL;

    if (my_strcmp(root->type, name) == 0)
        return root;

    // 先查孩子
    TreeNode *res = FindNode(root->child, name);
    if (res != NULL)
        return res;
    // 再查兄弟
    return FindNode(root->brother, name);
}

// 修改节点名称
void ModifyNode(TreeNode *root, char oldName[], char newName[])
{
    TreeNode *node = FindNode(root, oldName);
    if (node == NULL)
    {
        printf("未找到该分类！\n");
        return;
    }
    my_strcpy(node->type, newName);
    printf("分类名称修改成功！\n");
}

// 删除父节点下指定子节点
void DeleteChild(TreeNode *parent, char delName[])
{
    if (parent == NULL || parent->child == NULL)
    {
        printf("暂无子分类，无法删除！\n");
        return;
    }

    TreeNode *pre = NULL;
    TreeNode *cur = parent->child;

    // 查找要删除的节点
    while (cur != NULL && my_strcmp(cur->type, delName) != 0)
    {
        pre = cur;
        cur = cur->brother;
    }

    if (cur == NULL)
    {
        printf("未找到要删除的子分类！\n");
        return;
    }

    // 移除链表节点
    if (pre == NULL)
        parent->child = cur->brother;
    else
        pre->brother = cur->brother;

    // 递归释放该节点及其子树
    DestroyTree(cur);
    printf("子分类删除成功！\n");
}

// 先序遍历多叉树
void PreOrderTraverse(TreeNode *root)
{
    if (root == NULL)
        return;

    printf("%s\n", root->type);
    PreOrderTraverse(root->child);
    PreOrderTraverse(root->brother);
}

// 递归销毁整棵树，释放内存
void DestroyTree(TreeNode *root)
{
    if (root == NULL)
        return;

    DestroyTree(root->child);
    DestroyTree(root->brother);
    free(root);
}