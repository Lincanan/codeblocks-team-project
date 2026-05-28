#ifndef GLIST_H
#define GLIST_H
#include <stdio.h>
#include <string.h>
#include "public.h"

#define ATOM 0
#define LIST 1

// 广义表节点结构
typedef struct GLNode
{
    int tag;
    union{
        char data[MAX_NAME];
        struct GLNode *hp;
    } un;
    struct GLNode *tp;
} GLNode, *GList;

// 函数声明
void CreateGList(GList *L, char *str);
void TraverseGList(GList L);

#endif