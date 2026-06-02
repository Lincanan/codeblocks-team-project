#include <windows.h>

#include <stdio.h>
#include "list.h"
#include "public.h"
#include "queue.h"
#include "stack.h"
#include "string_match.h"
#include "tree.h"
#include "graph.h"
#include "glist.h"
#include "hash.h"

SqList L;
Volunteer v;
char id[20];
int choice;
DeQueue q;
Stack s;
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
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    InitList(&L);
    InitQueue(&q);
    InitStack(&s);
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
        printf("4. 模糊姓名/项目检索 \n");
        printf("5. 志愿项目 \n");
        printf("6. 协作网络 \n");
        printf("7. 嵌套档案 \n");
        printf("8. 学号快速查找\n");
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
    while(1)
    {
        printf("\n===== 线性表子菜单 =====\n");
        printf("1. 添加志愿者  2. 删除志愿者  3. 修改信息\n");
        printf("4. 查看列表    5. 列表逆序    6. 时长统计\n");
        printf("7. 星级排序    0. 返回主菜单\n");
        printf("请选择：");
        scanf("%d",&choice);

        if(choice == 0){
            printf("返回主菜单...\n");
            return;
        }

        switch(choice)
        {
            case 1:
                printf("输入学号：");scanf("%s",v.stuId);
                while(getchar()!='\n');
                printf("输入姓名：");scanf("%s",v.name);
                while(getchar()!='\n');
                printf("输入项目：");scanf("%s",v.project);
                while(getchar()!='\n');
                printf("输入时长：");scanf("%d",&v.hour);
                while(getchar()!='\n');
                printf("输入星级：");scanf("%d",&v.star);
                while(getchar()!='\n');
                ListInsert(&L,v);
                break;
            case 2:
                printf("输入要删除的学号：");
                scanf("%s",id);
                ListDelete(&L,id);
                printf("删除操作执行完毕\n");
                break;
            case 3:
                printf("输入要修改的学号：");
                scanf("%s",id);
                ListUpdate(&L,id);
                printf("修改操作执行完毕\n");
                break;
            case 4: 
                printf("\n=====志愿者全部列表=====\n");
                ListShow(&L); 
                break;
            case 5: 
                ListReverse(&L); 
                printf("列表逆序完成!\n");
                ListShow(&L);
                break;
            case 6: 
                StatHour(&L); 
                break;
            case 7: 
                SortByStar(&L); 
                printf("星级排序完成!\n");
                ListShow(&L);
                break;
        
            default: 
                printf("输入错误!请重新选择!\n");
                break;
             
        }
    }
}

// 双端队列子菜单
void queueMenu()
{
    int choice;
    Volunteer v;
    while(1)
    {
        printf("\n===== 双端队列子菜单 =====\n");
        printf("1. 紧急项目报名  2. 普通项目报名\n");
        printf("3. 签到管理      4. 查看排队  0. 返回\n");
        printf("选择：");scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("请输入学号：");
                scanf("%s",v.stuId);
                printf("请输入姓名:");
                scanf("%s",v.name);
                printf("%s",v.project);
                while(getchar() != '\n');
                EnQueueHead(&q,v);
                printf("紧急项目报名成功 已优先排入队伍!\n");
                break;
            case 2:
                printf("请输入学号：");
                scanf("%s",v.stuId);
                printf("请输入姓名:");
                scanf("%s",v.name);
                printf("%s",v.project);
                while(getchar() != '\n');
                EnQueueTail(&q,v);
                printf("普通项目报名成功 已加入排队!\n");
                break;
            case 3:
                if(q.front == q.rear){
                    printf("当前排队队伍为空，暂无人员需要签到!\n");
                    break;
                }
                DeQueueHead(&q,&v); 
                printf("\n 签到成功!");
                printf("签到志愿者信息:");
                printf("学号:%s | 姓名:%s | 服务项目:%s\n",v.stuId,v.name,v.project);
                printf("该志愿者已完成签到,移出排队列表\n");
                break;
            case 4: 
                printf("\n==== 当前排队列表 ====\n");
                ShowQueue(&q);
                break;
            case 0: 
                printf("返回主菜单\n");
                return;
            default:
                 printf("输入错误！\n");
                 break;
        }
    }
}

// 栈撤销子菜单
void stackMenu()
{
    int choice;
    Volunteer vol;

    while(1)
    {
        printf("\n===== 操作历史回退与撤销系统 =====\n");
        printf("1. 保存(新报名/修改)操作快照\n");
        printf("2. 志愿者报名撤销\n");
        printf("3. 服务时长回退\n");
        printf("4. 志愿者星级重置\n");
        printf("5. 签到打卡记录回滚\n");
        printf("6. 查看当前可撤销的操作步数\n");
        printf("0. 返回主菜单\n");
        printf("请选择功能:");
        scanf("%d", &choice);

        if(choice == 0) break;
        switch(choice)
        {
            case 1:
                printf("===保存当前志愿者操作快照===\n");
                printf("请输入 学号 姓名 项目 时长 星级：\n");
                scanf("%s %s %s %d %d", vol.stuId, vol.name, vol.project, &vol.hour, &vol.star);
                Push(&s, vol);
                printf("操作快照已存档,后续可一键撤销\n");
                break;
            case 2:
                if(StackEmpty(&s)){
                    printf("暂无可撤销的报名记录\n");
                    break;
                }
                Pop(&s, &vol);
                printf("报名撤销完成,已移除: 学号:%s 姓名:%s\n", vol.stuId, vol.name);
                break;
            
            case 3:
                if(StackEmpty(&s)){
                    printf("暂无时长可回退\n");
                    break;
                }
                Pop(&s,&vol);
                printf("时长回退完成! 原记录: %s 原服务时长:%d 小时\n",vol.name,vol.hour);
                printf("已恢复至上一次时长状态\n");
                break;
            case 4:
                if(StackEmpty(&s)){
                    printf("暂无星级可重置\n");
                    break;
                }
                Pop(&s,&vol);
                printf("星级重置完成! %s 原星级 :%d星 已回退\n",vol.name,vol.star);
                break;
            case 5:
                if(StackEmpty(&s)){
                    printf("暂无签到记录可回滚\n");
                    break;
                }
                Pop(&s,&vol);
                printf("签到记录回滚成功! 已撤销 %s 的最近一次签到\n",vol.name);
                break;
            case 6:
                printf("当前栈内存档操作总数: %d 步\n",StackLength(&s));
                printf("最多可连续撤销 %d 次\n",StackLength(&s));
                break;
            default:
                printf("输入有误，请重选！\n");
                break;
        }
    }
}

// BF+KMP检索子菜单
void searchMenu()
{
    char vName[MAX_NAME], vProject[MAX_NAME], key[MAX_NAME];
    while(1)
    {
        printf("\n===== BF+KMP模糊检索 =====\n");
        printf("1. 志愿者/志愿项目 模糊检索\n");
        printf("0. 返回主菜单\n");
        printf("请选择：");

        int op;
        scanf("%d", &op);
        if(op == 0) break;

        printf("输入志愿者姓名：");
        scanf("%s", vName);
        printf("输入服务项目：");
        scanf("%s", vProject);
        printf("输入检索关键词：");
        scanf("%s", key);

        // 调用只传key参数的函数，和你现在的定义完全匹配
        VolunteerSearchBF_KMP(key);

        // 吃掉回车，避免菜单乱跳
        getchar();
        printf("\n检索完成,按回车继续...");
        getchar();
    }
}
// 多叉树子菜单
void treeMenu()
{
    TreeNode *root;
    char buf[MAX_NAME];
    int choice;
    int star,hours;

    printf("\n===== 志愿项目分类树 =====\n");
    printf("请输入根分类名称：");
    scanf("%s", buf);
    root = CreateRoot(buf);
    if(!root)return;

    while(1)
    {
        printf("\n=====志愿项目管理菜单=====\n");
        printf("1.添加项目(类型/主题/子项目)\n");
        printf("2.查看全部分类\n");
        printf("3.统计服务总时长\n");
        printf("4.按星级查询项目\n");
        printf("0.返回上一级\n");
        scanf("%d", &choice);
        if(choice == 0) break;

        switch (choice){
            case 1:{
                char parent_name[MAX_NAME],child_name[MAX_NAME];
                printf("请输入父节点名称:");
                scanf("%s",parent_name);
                printf("请输入子节点名称:");
                scanf("%s",child_name);
                printf("请输入星级:");
                scanf("%d",&star);
                printf("请输入服务时长:");
                scanf("%d",&hours);
                // 用FindNode递归查找任意层级的父节点，不再手动写判断
                TreeNode* parent = FindNode(root, parent_name);
                if (parent != NULL) {
                AddChild(parent, child_name, star, hours);
                printf("添加成功！\n");
                } else {
                 printf("未找到父节点，请先添加父分类\n");
                }
                  break;
                } 
            case 2:
                printf("--- 项目层级列表 ---\n");
                PreOrderTraverse(root, 0);
                break;
            case 3: {
                int total = CountTotalHours(root);
                printf(" 所有项目服务总时长: %d 小时\n", total);
                break;
            }
            case 4: {
                int star_count;
                printf("请输入要查询的星级(1-5,查询>=该星级的项目）: ");
                scanf("%d", &star_count);
                printf("--- %d星及以上项目列表 ---\n", star_count);
                QueryByStar(root, star_count);
                break;
            }
            default:
                printf(" 无效选项，请重新选择！\n");
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
        printf("\n===== 协作网络图与服务导航 =====\n");
        printf("1. 添加志愿者/服务地点节点\n");
        printf("2. 添加协作关系/路径\n");
        printf("3. BFS服务地点最短路径导航\n");
        printf("4. 团队协作成员匹配\n");
        printf("0. 返回上一级\n");
        printf("请选择:");
        scanf("%d", &choice);
        if(choice == 0) break;

         switch (choice) {
            case 1:
                printf("输入节点名称（志愿者/服务地点）：");
                scanf("%s", name1);
                idx1 = AddVex(&G, name1);
                if (idx1 != -1) {
                    printf("节点添加成功，下标：%d\n", idx1);
                } else {
                    printf("节点数已满，添加失败！\n");
                }
                break;
            case 2:
                printf("输入两个节点下标(从0开始):");
                scanf("%d %d", &idx1, &idx2);
                if(idx1 < 0 || idx1 >= G.vexNum || idx2 < 0 || idx2 >= G.vexNum)
                {
                    printf("下标无效,请输入已添加节点的下标\n");
                    break;
                }
                AddArc(&G, idx1, idx2);
                printf("协作关系/路径添加成功！\n");
                break;
            case 3:
                printf("输入起点、终点下标：");
                scanf("%d %d", &idx1, &idx2);
                if(idx1 < 0 || idx1 >= G.vexNum || idx2 < 0 || idx2 >= G.vexNum)
                {
                    printf("下标无效，请输入已添加节点的下标\n");
                    break;
                }
                BFS(&G, idx1, idx2);
                break;
            case 4:
                TeamMatch(&G);
                break;
            default:
                printf("无效选项！\n");
        }
        }
    }

// 广义表子菜单
extern SqList L;   //关联全局顺序表

void glistMenu()
{
    GList g = NULL;
    g = InitGList();
    int choice;
    char vid[20], proj[32];
    int hour, star;

    while(1)
    {
        printf("\n=====7 嵌套志愿档案管理====\n");
        printf("1.新增志愿者项目档案\n");
        printf("2.浏览全部档案明细\n");
        printf("3.贡献度分级统计\n");
        printf("0.返回主菜单\n");
        printf("请输入选择：");

        if(scanf("%d",&choice) != 1)
        {
            printf("输入无效，请输入数字！\n");
            while(getchar()!='\n');
            continue;
        }
        if(choice == 0) break;

        switch(choice)
        {
            case 1:
                printf("输入志愿者学号：");
                scanf("%s",vid);
                printf("输入志愿项目名称：");
                scanf("%s",proj);
                printf("输入服务时长：");
                scanf("%d",&hour);
                printf("输入星级(1~5):");
                scanf("%d",&star);
                AddVolItem(&g, vid, proj, hour, star);
                printf("档案添加成功\n");
                break;
            case 2:
                PrintGList(g);
                break;
            case 3:
                CalcContributeLevel(g);
                break;
            default:
                printf("无此选项\n");
        }
    }
}
// 哈希表子菜单
void hashMenu()
{
    printf("\n------------------------------\n");
    hashSystemMenu();
    system("pause");
}