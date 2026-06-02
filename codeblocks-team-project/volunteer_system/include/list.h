#ifndef LIST_H
#define LIST_H

#include "public.h"

// 顺序线性表结构体
typedef struct{
    Volunteer data[MAX_SIZE];
    int length;
} SqList;

// 函数声明
void InitList(SqList *L);
int ListInsert(SqList *L, Volunteer v);
int ListDelete(SqList *L, char* stuId);
int ListUpdate(SqList *L, char* stuId);
void ListShow(SqList *L);
void ListReverse(SqList *L);
void StatHour(SqList *L);
void SortByStar(SqList *L);
extern SqList L;
#endif