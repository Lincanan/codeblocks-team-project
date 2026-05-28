#include <stdio.h>
#include "public.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "string_match.h"
#include "tree.h"
#include "graph.h"
#include "glist.h"
#include "hash.h"

// 函数声明
void mainMenu();
void listMenu();
void queueMenu();
void stackMenu();
void searchMenu();
void treeMenu();
void graphMenu();
void glistMenu();
void hashMenu();

int main(){
    printf("===== 校园志愿者服务管理系统 =====\n");
    mainMenu();
    return 0;
}

// 一级主菜单
void mainMenu(){
    int choice;
    while(1){
        printf("\n========== 主功能菜单 ==========\n");
        printf("1. 志愿者记录 \n");
        printf("2. 项目报名 \n");
        printf("3. 操作回退 \n");
        printf("4. 模糊姓名 \n");
        printf("5. 志愿项目 \n");
        printf("6. 协作网络 \n");
        printf("7. 嵌套档案 \n");
        printf("8. 学号 \n");
        printf("0. 退出系统\n");
        printf("请输入功能选项：");
        scanf("%d",&choice);

        switch(choice){
            case 1: listMenu(); break;
            case 2: queueMenu(); break;
            case 3: stackMenu(); break;
            case 4: searchMenu(); break;
            case 5: treeMenu(); break;
            case 6: graphMenu(); break;
            case 7: glistMenu(); break;
            case 8: hashMenu(); break;
            case 0: printf("系统退出，感谢使用！\n"); return;
            default: printf("输入错误，请重新选择！\n");
        }
    }
}

// 线性表子菜单
void listMenu()
{
    SqList L;
    InitList(&L);
    int choice;
    Volunteer v;
    char id[20];

    while(1)
    {
        printf("\n===== 线性表子菜单 =====\n");
        printf("1. 添加志愿者  2. 删除志愿者  3. 修改信息\n");
        printf("4. 查看列表    5. 列表逆序    6. 时长统计\n");
        printf("7. 星级排序    0. 返回主菜单\n");
        printf("请选择：");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("输入学号：");scanf("%s",v.stuId);
                printf("输入姓名：");scanf("%s",v.name);
                printf("输入项目：");scanf("%s",v.project);
                printf("输入时长：");scanf("%d",&v.hour);
                printf("输入星级：");scanf("%d",&v.star);
                ListInsert(&L,v);
                break;
            case 2:
                printf("输入要删除的学号：");scanf("%s",id);
                ListDelete(&L,id);
                break;
            case 3:
                printf("输入要修改的学号：");scanf("%s",id);
                ListUpdate(&L,id);
                break;
            case 4: ListShow(&L); break;
            case 5: ListReverse(&L); break;
            case 6: StatHour(&L); break;
            case 7: SortByStar(&L); break;
            case 0: return;
            default: printf("输入错误！\n");
        }
    }
}

// 双端队列子菜单
void queueMenu()
{
    DeQueue q;
    InitQueue(&q);
    int choice;
    Volunteer v;
    while(1)
    {
        printf("\n===== 双端队列子菜单 =====\n");
        printf("1. 紧急项目报名  2. 普通项目报名\n");
        printf("3. 签到出队      4. 查看排队  0. 返回\n");
        printf("选择：");scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("学号 姓名 项目：");
                scanf("%s%s%s",v.stuId,v.name,v.project);
                EnQueueHead(&q,v);
                break;
            case 2:
                printf("学号 姓名 项目：");
                scanf("%s%s%s",v.stuId,v.name,v.project);
                EnQueueTail(&q,v);
                break;
            case 3: DeQueueHead(&q,&v); break;
            case 4: ShowQueue(&q); break;
            case 0: return;
            default: printf("输入错误！\n");
        }
    }
}

// 栈撤销子菜单
void stackMenu()
{
    Stack s;
    InitStack(&s);
    int choice;
    Volunteer vol;

    while(1)
    {
        printf("\n===== 操作回退栈 =====\n");
        printf("1. 保存志愿者信息(入栈)\n");
        printf("2. 撤销上一步操作(出栈)\n");
        printf("0. 返回主菜单\n");
        printf("请选择：");
        scanf("%d", &choice);

        if(choice == 0) break;
        switch(choice)
        {
            case 1:
                printf("请输入 学号 姓名 项目 时长 星级：\n");
                scanf("%s%s%s%d%d", vol.stuId, vol.name, vol.project, &vol.hour, &vol.star);
                Push(&s, vol);
                printf("信息已保存！\n");
                break;
            case 2:
                Pop(&s, &vol);
                printf("撤销完成，恢复信息：%s %s\n", vol.stuId, vol.name);
                break;
            default:
                printf("输入有误，请重选！\n");
        }
    }
}

// BF+KMP检索子菜单
void searchMenu()
{
    char vName[MAX_NAME], vProject[MAX_NAME], key[50];
    while(1)
    {
        printf("\n===== BF+KMP模糊检索 =====\n");
        printf("1. 输入志愿者信息进行检索\n");
        printf("0. 返回主菜单\n");
        printf("请选择：");
        int op; scanf("%d",&op);
        if(op == 0) break;

        printf("输入志愿者姓名："); scanf("%s",vName);
        printf("输入服务项目："); scanf("%s",vProject);
        printf("输入检索关键词："); scanf("%s",key);

        VolunteerSearchBF_KMP(vName, vProject, key);
    }
}

// 多叉树子菜单
void treeMenu()
{
    TreeNode *root;
    char buf[MAX_NAME];
    int choice;
    printf("\n===== 志愿项目分类树 =====\n");
    printf("请输入根分类名称：");
    scanf("%s", buf);
    root = CreateRoot(buf);

    while(1)
    {
        printf("\n1. 添加子项目  2. 查看全部分类  0. 返回\n");
        printf("请选择：");
        scanf("%d", &choice);
        if(choice == 0) break;

        if(choice == 1)
        {
            printf("输入子项目名称：");
            scanf("%s", buf);
            AddChild(root, buf);
            printf("添加成功！\n");
        }
        else if(choice == 2)
        {
            printf("--- 项目列表 ---\n");
            PreOrderTraverse(root);
        }
    }
    DestroyTree(root);
}

// 图BFS子菜单
void graphMenu()
{
    Graph G;
    InitGraph(&G);
    int idx1, idx2, choice;
    char name1[MAX_NAME], name2[MAX_NAME];

    while(1)
    {
        printf("\n===== 协作网络图BFS =====\n");
        printf("1. 添加志愿者节点  2. 添加协作关系\n");
        printf("3. BFS查询路径     0. 返回\n");
        printf("选择：");
        scanf("%d", &choice);
        if(choice == 0) break;

        if(choice == 1)
        {
            printf("输入志愿者姓名：");
            scanf("%s", name1);
            AddVex(&G, name1, &idx1);
            printf("节点添加成功\n");
        }
        else if(choice == 2)
        {
            printf("输入两个志愿者下标(从0开始)：");
            scanf("%d%d", &idx1, &idx2);
            AddArc(&G, idx1, idx2);
            printf("协作关系添加成功\n");
        }
        else if(choice == 3)
        {
            printf("输入起点、终点下标：");
            scanf("%d%d", &idx1, &idx2);
            BFS(&G, idx1, idx2);
        }
    }
}

// 广义表子菜单
void glistMenu()
{
    GList L;
    char buf[200];
    printf("\n===== 广义表档案存储 =====\n");
    printf("格式示例：(张三,志愿活动,40h,5星)\n");
    printf("请输入广义表字符串：");
    scanf("%s", buf);

    CreateGList(&L, buf);
    printf("解析结果：");
    TraverseGList(L);
    printf("\n");
}

// 哈希表子菜单
void hashMenu(){
    hashSystemMenu();
}