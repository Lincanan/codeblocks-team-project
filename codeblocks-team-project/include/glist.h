#ifndef GLIST_H
#define GLIST_H

#include "public.h"

#define ATOM 0
#define LIST 1

typedef struct GLNode
{
    int tag;
    union
    {
        char data[MAX_NAME];
        struct GLNode *hp;
    }un;
    struct GLNode *tp;
}GLNode, *GList;
// 基础操作（初始化/销毁必须实现）

void CreateGList(GList *L, char *str);
void TraverseGList(GList L);
void InitGList(GList *L);
void DestroyGList(GList *L);// 新增：递归销毁，释放内存
// 业务功能（对应评分表的“贡献度计算”）
void CalcContributionLevel(GList L);

#endif