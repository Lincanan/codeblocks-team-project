#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"

// 根据字符串创建广义表
void CreateGList(GList *L, char *str)
{
    *L = NULL;
    if(*str == '\0') return;

    GLNode *head = NULL, *tail = NULL;
    while(*str != '\0' && *str != ')')
    {
        if(*str == '(')
        {
            GList sub;
            str++;
            CreateGList(&sub, str);
            GLNode *p = (GLNode*)malloc(sizeof(GLNode));
            p->tag = LIST;
            p->un.hp = sub;
            p->tp = NULL;
            if(head == NULL) head = tail = p;
            else { tail->tp = p; tail = p; }
        }
        else if((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z') || (*str >= '0' && *str <= '9'))
        {
            GLNode *p = (GLNode*)malloc(sizeof(GLNode));
            p->tag = ATOM;
            int i = 0;
            while(*str != ',' && *str != ')' && *str != '\0')
                p->un.data[i++] = *str++;
            p->un.data[i] = '\0';
            p->tp = NULL;
            if(head == NULL) head = tail = p;
            else { tail->tp = p; tail = p; }
        }
        if(*str == ',') str++;
    }
    if(*str == ')') str++;
    *L = head;
}

// 遍历输出广义表
void TraverseGList(GList L)
{
    if(L == NULL)
    {
        printf("()");
        return;
    }
    if(L->tag == LIST)
    {
        printf("(");
        TraverseGList(L->un.hp);
        printf(")");
    }
    else
    {
        printf("%s", L->un.data);
    }
    if(L->tp != NULL)
    {
        printf(",");
        TraverseGList(L->tp);
    }
}