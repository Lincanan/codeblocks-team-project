#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/**
 * @brief 初始化广义表（创建空表）
 * @param L 广义表指针
 */
void InitGList(GList *L) {
    *L = NULL;
}

/**
 * @brief 递归销毁广义表，释放所有节点内存
 * @param L 广义表指针
 */
void DestroyGList(GList *L) {
    if (*L == NULL) return;

    // 如果是子表节点，先销毁它的表头子表
    if ((*L)->tag == LIST) {
        DestroyGList(&((*L)->un.hp));
    }

    // 递归销毁所有后继兄弟节点
    if ((*L)->tp != NULL) {
        DestroyGList(&((*L)->tp));
    }

    // 释放当前节点
    free(*L);
    *L = NULL;
}

// 业务功能：贡献度计算
void CalcContributionLevel(GList L) {
    if (L == NULL) return;

    // 原子节点：解析志愿者档案数据
    if (L->tag == ATOM) {
        // 解析数据（格式示例："张三-志愿活动-40h-5星"）
        char *starStr = strrchr(L->un.data, '-');
        char *hourStr = strstr(L->un.data, "-");

        if (starStr != NULL && hourStr != NULL) {
            // 提取星级和时长
            int star = atoi(starStr + 1);
            int hour = atoi(hourStr + 1);
            
            // 贡献度规则：星级*10 + 时长/20
            int level = star * 10 + hour / 20;
            
            // 输出档案和贡献度
            printf("档案：%s | 贡献度层级：%d\n", L->un.data, level);
        } else {
            // 格式不匹配时的容错处理
            printf("档案格式错误：%s\n", L->un.data);
        }
    }
    // 子表节点：递归遍历子表
    else {
        // 遍历子表的所有元素
        GList p = L->un.hp;
        while (p != NULL) {
            CalcContributionLevel(p);
            p = p->tp;
        }
    }

    // 递归遍历后继兄弟节点
    if (L->tp != NULL) {
        CalcContributionLevel(L->tp);
    }
}