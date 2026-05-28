#include <stdio.h>
#include <string.h>
#include "list.h"

// 初始化线性表：有效长度置0
void InitList(SqList *L)
{
    L->length = 0;
}

// 尾部插入志愿者信息
int ListInsert(SqList *L, Volunteer v)
{
    if(L->length >= MAX_SIZE)
    {
        printf("线性表已满，无法插入！\n");
        return 0;
    }
    L->data[L->length] = v;
    L->length++;
    printf("插入成功！\n");
    return 1;
}

// 根据学号删除志愿者
int ListDelete(SqList *L, char* stuId)
{
    int i,j;
    for(i=0; i<L->length; i++)
    {
        if(strcmp(L->data[i].stuId, stuId) == 0)
        {
            // 后续元素前移覆盖
            for(j=i; j<L->length-1; j++)
            {
                L->data[j] = L->data[j+1];
            }
            L->length--;
            printf("删除成功！\n");
            return 1;
        }
    }
    printf("未找到该学号，删除失败！\n");
    return 0;
}

// 根据学号修改志愿者信息
int ListUpdate(SqList *L, char* stuId)
{
    int i;
    for(i=0; i<L->length; i++)
    {
        if(strcmp(L->data[i].stuId, stuId) == 0)
        {
            printf("请输入新姓名：");
            scanf("%s",L->data[i].name);
            printf("请输入新项目：");
            scanf("%s",L->data[i].project);
            printf("请输入新时长：");
            scanf("%d",&L->data[i].hour);
            printf("请输入新星级：");
            scanf("%d",&L->data[i].star);
            printf("修改成功！\n");
            return 1;
        }
    }
    printf("未找到该学号！\n");
    return 0;
}

// 遍历打印所有志愿者信息
void ListShow(SqList *L)
{
    if(L->length == 0)
    {
        printf("线性表暂无数据！\n");
        return;
    }
    printf("===== 志愿者列表 =====\n");
    for(int i=0; i<L->length; i++)
    {
        printf("学号：%s 姓名：%s 项目：%s 时长：%d 星级：%d\n",
               L->data[i].stuId, L->data[i].name, L->data[i].project,
               L->data[i].hour, L->data[i].star);
    }
}

// 线性表整体逆序
void ListReverse(SqList *L)
{
    int i,j;
    Volunteer temp;
    for(i=0, j=L->length-1; i<j; i++,j--)
    {
        temp = L->data[i];
        L->data[i] = L->data[j];
        L->data[j] = temp;
    }
    printf("逆序完成！\n");
}

// 统计总时长、平均时长
void StatHour(SqList *L)
{
    int sum = 0;
    if(L->length == 0)
    {
        printf("无数据可统计！\n");
        return;
    }
    for(int i=0; i<L->length; i++)
    {
        sum += L->data[i].hour;
    }
    printf("总服务时长：%d 小时\n",sum);
    printf("平均服务时长：%.2f 小时\n",(float)sum / L->length);
}

// 冒泡排序：按星级降序
void SortByStar(SqList *L)
{
    int i,j;
    Volunteer temp;
    for(i=0; i<L->length-1; i++)
    {
        for(j=0; j<L->length-1-i; j++)
        {
            if(L->data[j].star < L->data[j+1].star)
            {
                temp = L->data[j];
                L->data[j] = L->data[j+1];
                L->data[j+1] = temp;
            }
        }
    }
    printf("按星级排序完成！\n");
}