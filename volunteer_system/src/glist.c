#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "glist.h"

// 根据字符串创建广义表（修复卡死+中文兼容版）
void CreateGList(GList *L, char *str)
{
    *L = NULL;
    // 空字符串直接返回
    if(str == NULL || *str == '\0') return;

    GLNode *head = NULL, *tail = NULL;

    while(*str != '\0' && *str != ')')
    {
        // 遇到左括号：递归创建子广义表（多叉树嵌套）
        if(*str == '(')
        {
            GList sub;
            str++;
            CreateGList(&sub, str);

            // 申请列表节点
            GLNode *p = (GLNode*)malloc(sizeof(GLNode));
            p->tag = LIST;
            p->un.hp = sub;
            p->tp = NULL;

            // 尾插法加入链表
            if(head == NULL) {
                head = tail = p;
            } else {
                tail->tp = p;
                tail = p;
            }
        }
        // 普通原子节点（姓名、项目、时长、星级，支持中文）
        else if(*str != ',' && *str != ' ')
        {
            GLNode *p = (GLNode*)malloc(sizeof(GLNode));
            p->tag = ATOM;

            int i = 0;
            // 读取直到逗号/括号/结束，停止截取
            while(*str != ',' && *str != ')' && *str != '\0')
            {
                p->un.data[i++] = *str++;
            }
            p->tp = NULL;

            // 尾插
            if(head == NULL) {
                head = tail = p;
            } else {
                tail->tp = p;
                tail = p;
            }
        }

        // 跳过逗号和空格分隔符
        if(*str == ',') str++;
        while(*str == ' ') str++;
    }

    // 返回构建好的广义表头
    *L = head;
}
  // 广义表遍历打印函数
void TraverseGList(GList L) 
{
    if (L == NULL) return;

    // 打印原子节点（你的姓名、活动、时长、星级）
    if (L->tag == ATOM)
    {
        printf("%s  |  ", L->un.data);
    }
    // 递归遍历子表
    else
    {
        TraverseGList(L->un.hp);
    }

    // 遍历后继兄弟节点
    TraverseGList(L->tp);
}