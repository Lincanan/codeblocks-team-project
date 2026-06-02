#ifndef GLIST_H
#define GLIST_H

#define ATOM 0
#define LIST 1

//项目明细：原子结点数据
typedef struct{
    char projName[32];
    int hour;
    int star;
}ItemData;

//广义表结点
typedef struct GNode{
    int tag;
    union{
        ItemData item;
        char volId[20];
    }u;
    struct GNode *hp; //子表头指针
    struct GNode *tp; //后继结点
}GNode,*GList;

//函数声明
GList InitGList();
//添加志愿者+项目档案，无志愿者新建子表
int AddVolItem(GList *G,char *vid,char *pname,int hour,int star);
//遍历打印全档案
void PrintGList(GList G);
//计算贡献度分级：贡献=时长*星级，S/A/B/C
void CalcContributeLevel(GList G);
void GListMenu(GList *G);

#endif