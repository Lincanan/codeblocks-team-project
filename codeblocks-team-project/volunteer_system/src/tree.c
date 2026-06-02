#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "tree.h"

TreeNode* CreateRoot(char name[]) {
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (!root) return NULL;

    my_strcpy(root->type, name);
    root->star = 0;
    root->service_hours = 0;
    root->child = NULL;
    root->brother = NULL;
    return root;
}

void AddChild(TreeNode *parent, char childName[], int star, int hours) {
    if (!parent) return;

    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) return;

    my_strcpy(newNode->type, childName);
    newNode->star = star;
    newNode->service_hours = hours;
    newNode->child = NULL;
    newNode->brother = NULL;

    if (parent->child == NULL) {
        parent->child = newNode;
    } else {
        TreeNode *p = parent->child;
        while (p->brother != NULL) {
            p = p->brother;
        }
        p->brother = newNode;
    }
}

TreeNode* FindNode(TreeNode *root, char name[]) {
    if (!root) return NULL;

    if (my_strcmp(root->type, name) == 0) {
        return root;
    }

    TreeNode *foundChild = FindNode(root->child, name);
    if (foundChild != NULL) {
        return foundChild;
    }
    return FindNode(root->brother, name);
}

void PreOrderTraverse(TreeNode *root, int level) {
    if (!root) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    printf("├─ %s", root->type);
    if (root->child == NULL) {
        printf(" | 星级: %d星 | 服务时长: %d小时", root->star, root->service_hours);
    }
    printf("\n");

    PreOrderTraverse(root->child, level + 1);
    PreOrderTraverse(root->brother, level);
}

int CountTotalHours(TreeNode *root) {
    if (!root) return 0;

    int total = 0;
    if (root->child == NULL) {
        total += root->service_hours;
    }

    total += CountTotalHours(root->child);
    total += CountTotalHours(root->brother);
    return total;
}

void QueryByStar(TreeNode *root, int star_count) {
    if (!root) return;

    if (root->child == NULL && root->star >= star_count) {
        printf("项目: %s | 星级: %d星 | 服务时长: %d小时\n",
               root->type, root->star, root->service_hours);
    }

    QueryByStar(root->child, star_count);
    QueryByStar(root->brother, star_count);
}

void DestroyTree(TreeNode *root) {
    if (!root) return;

    DestroyTree(root->child);
    DestroyTree(root->brother);
    free(root);
}