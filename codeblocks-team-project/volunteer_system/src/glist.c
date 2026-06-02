#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "glist.h"

GList InitGList()
{
    return NULL;
}

int AddVolItem(GList *G,char *vid,char *pname,int hour,int star)
{
    GList p=*G,pre=NULL;
    //1.查找该志愿者是否存在
    while(p!=NULL && my_strcmp(p->u.volId,vid)!=0)
    {
        pre=p;
        p=p->tp;
    }
    //不存在：新建志愿者子表结点
    if(p==NULL)
    {
        p=(GList)malloc(sizeof(GNode));
        p->tag=LIST;
        my_strcpy(p->u.volId,vid);
        p->hp=NULL;
        p->tp=NULL;
        if(pre==NULL) *G=p;
        else pre->tp=p;
    }
    //新建项目原子结点，挂在hp子表
    GList item=(GList)malloc(sizeof(GNode));
    item->tag=ATOM;
    my_strcpy(item->u.item.projName,pname);
    item->u.item.hour=hour;
    item->u.item.star=star;
    item->tp=p->hp;
    p->hp=item;
    return 1;
}

void PrintGList(GList G)
{
    GList p=G;
    if(p==NULL){printf("暂无档案数据\n");return;}
    int allSum=0;
    while(p)
    {
        printf("【志愿者学号：%s】\n",p->u.volId);
        GList sub=p->hp;
        int sum=0;
        while(sub)
        {
            int c=sub->u.item.hour*sub->u.item.star;
            sum+=c;
            printf(" 项目:%s | 时长:%d | 星级:%d | 单项贡献:%d\n",
                sub->u.item.projName,sub->u.item.hour,sub->u.item.star,c);
            sub=sub->tp;
        }
        printf(" 该志愿者总贡献：%d\n\n",sum);
        allSum+=sum;
        p=p->tp;
    }
}

void CalcContributeLevel(GList G)
{
    int S=0,A=0,B=0,C=0;
    GList p=G;
    while(p)
    {
        GList sub=p->hp;
        int sum=0;
        while(sub)
        {
            sum += sub->u.item.hour*sub->u.item.star;
            sub=sub->tp;
        }
        //分级规则
        if(sum>=100) S++;
        else if(sum>=60) A++;
        else if(sum>=30) B++;
        else C++;
        p=p->tp;
    }
    printf("====贡献度分级统计====\n");
    printf("S级(≥100):%d人\nA级(60~99):%d人\nB级(30~59):%d人\nC级(<30):%d人\n",S,A,B,C);
}

//7号菜单
void GListMenu(GList *G)
{
    int op;
    char vid[20],pname[32];
    int h,s;
    while(1)
    {
        printf("\n====7 嵌套志愿档案管理====\n");
        printf("1.新增志愿者项目档案\n2.浏览全部档案\n3.贡献度分级统计\n0.返回主菜单\n请选择：");
        scanf("%d",&op);
        if(op==0) break;
        switch(op)
        {
            case 1:
                printf("输入学号：");scanf("%s",vid);
                printf("输入项目名：");scanf("%s",pname);
                printf("输入服务时长：");scanf("%d",&h);
                printf("输入星级：");scanf("%d",&s);
                AddVolItem(G,vid,pname,h,s);
                printf("档案添加成功\n");
                break;
            case2:PrintGList(*G);break;
            case3:CalcContributeLevel(*G);break;
        }
    }
}