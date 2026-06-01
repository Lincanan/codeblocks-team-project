#include <windows.h>

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

int BF(char *text,char *pattern);
int kmp(char *text,char *pattern);

SqList L;
Stack st;

// 函数声明
void mainMenu();
void listMenu(SqList *L,Stack *s);
void queueMenu();
void stackMenu(Stack *s,SqList *L);
void searchMenu();
void treeMenu(SqList *L);
void graphMenu();
void glistMenu();
void hashMenu();

void clearBuf(){
    while(getchar()!='\n');
}

int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
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
            case 1: listMenu(&L,&st); break;
            case 2: queueMenu(); break;
            case 3: stackMenu(&st,&L); break;
            case 4: searchMenu(); break;
            case 5: treeMenu(&L); break;
            case 6: graphMenu(); break;
            case 7: glistMenu(); break;
            case 8: hashMenu(); break;
            case 0: printf("系统退出，感谢使用！\n"); return;
            default: printf("输入错误，请重新选择！\n");
        }
    }
}

// 线性表子菜单
void listMenu(SqList *L, Stack *s)
{
    int op;
    char stuId[15];
    Volunteer v;

    while (1)
    {
        printf("===== 志愿者记录管理菜单 =====\n");
        printf("1. 新增志愿者（报名）\n");
        printf("2. 按学号删除（可撤销）\n");
        printf("3. 修改信息（时长/星级/姓名等）\n");
        printf("4. 查看所有志愿者（按星级排序）\n");
        printf("0. 返回主菜单\n");
        printf("请选择操作：");

        // 输入校验
        if (scanf("%d", &op) != 1)
        {
            printf("输入无效，请输入数字！\n");
            clearBuf();
            system("pause");
            continue;
        }
        clearBuf();

        // 0. 返回主菜单
        if (op == 0)
        {
            printf("退出志愿者记录菜单...\n");
            break;
        }
        switch (op)
        {
            // 1. 新增志愿者（报名）
            case 1:
                printf("请输入学号：");
                scanf("%s", v.stuId);
                clearBuf();

                printf("请输入姓名：");
                scanf("%s", v.name);
                clearBuf();

                printf("请输入服务项目：");
                scanf("%s", v.project);
                clearBuf();

                printf("请输入服务时长：");
                while (scanf("%d", &v.hour) != 1 || v.hour < 0)
                {
                    printf("输入无效，请输入非负数字！\n");
                    clearBuf();
                    printf("请输入服务时长：");
                }
                clearBuf();

                printf("请输入星级（1-5）：");
                 while (scanf("%d", &v.star) != 1 || v.star < 1 || v.star > 5)
                 {
                     printf("输入无效，请输入1-5之间的数字！\n");
                     clearBuf();
                     printf("请输入星级（1-5）：");
                 }
                 clearBuf();
                 v.status = 0; // 默认状态：待审核
                 RecordOperation(s, v, OP_ENROLL);
                  // 记录插入前的长度
                  int old_len = L->length;
                  if (ListInsert(L, old_len, v)) {
                    printf("插入成功！\n");
                    // 用顺序表里的数据打印，而不是临时变量v！
                    printf("志愿者信息：学号:%s 姓名:%s 项目:%s 时长:%d 星级:%d星 状态:待审核\n",
                        L->data[old_len].stuId,
                        L->data[old_len].name,
                        L->data[old_len].project,
                        L->data[old_len].hour,
                        L->data[old_len].star);
                    } else {
                        printf("插入失败！\n");
                    }
                    break;

            // 2. 按学号删除（可撤销）
            case 2:
                printf("请输入要删除的学号：");
                scanf("%s", stuId);
                clearBuf();

                int idx = LocateElem(L, stuId);
                if (idx == -1)
                {
                    printf("无此志愿者！\n");
                    break;
                }

                // 记录删除前状态，用于撤销
                RecordOperation(s, L->data[idx], OP_ENROLL);

                // 执行删除
                if (ListDelete(L, stuId))
                {
                    printf("删除成功！\n");
                }
                else
                {
                    printf("删除失败！\n");
                }
                break;

            // 3. 修改信息（时长/星级/姓名/审核状态）
            case 3:
                printf("请输入要修改的学号：");
                scanf("%s", stuId);
                clearBuf();

                int pos = LocateElem(L, stuId);
                if (pos == -1)
                {
                    printf("无此志愿者！\n");
                    break;
                }

                // 记录修改前状态，用于撤销
                RecordOperation(s, L->data[pos], OP_ENROLL);

                printf("当前信息：\n");
                printf("姓名:%s  项目:%s 时长:%d 星级:%d星 状态:%s\n",
                       L->data[pos].name, L->data[pos].name, L->data[pos].hour, L->data[pos].star,
                       L->data[pos].status == 0 ? "待审核" : L->data[pos].status == 1 ? "已通过" : "已拒绝");

                printf("\n请选择修改项：\n");
                printf("1. 修改姓名  2. 修改服务项目 3. 修改服务时长  4. 修改审核状态\n请输入：");
                int modOp;
                scanf("%d", &modOp);
                clearBuf();

                if (modOp == 1)
                {
                    printf("请输入新姓名：");
                    scanf("%s", L->data[pos].name);
                    printf("姓名修改成功！\n");
                }
                else if(modOp == 2)
                {
                    printf("请输入新的服务项目：");
                    scanf("%s", L->data[pos].name);
                    printf("项目修改成功！\n");

                }
                else if (modOp == 3)
                {
                    printf("请输入新的服务时长：");
                    while (scanf("%d", &L->data[pos].hour) != 1 || L->data[pos].hour < 0)
                    {
                        printf("输入无效，请输入非负数字！\n");
                        clearBuf();
                        printf("请输入新的服务时长：");
                    }
                    clearBuf();

                    // 自动更新星级
                    if (L->data[pos].hour < 20) L->data[pos].star = 1;
                    else if (L->data[pos].hour < 50) L->data[pos].star = 2;
                    else if (L->data[pos].hour < 100) L->data[pos].star = 3;
                    else if (L->data[pos].hour < 200) L->data[pos].star = 4;
                    else L->data[pos].star = 5;

                    printf("时长修改成功，星级已自动更新为：%d星\n", L->data[pos].star);
                }
                else if (modOp == 4)
                {
                    printf("请输入新状态（0=待审核 1=已通过 2=已拒绝）：");
                    while (scanf("%d", &L->data[pos].status) != 1 || L->data[pos].status < 0 || L->data[pos].status > 2)
                    {
                         printf("输入无效，请输入0-2之间的数字！\n");
                         clearBuf();
                         printf("请输入新状态：");
                     }
                     clearBuf();
                     printf("状态修改成功！\n");
                 }
                 else
                 {
                     printf("选项无效！\n");
                 }
                 break;
             // 4. 查看所有志愿者（按星级降序）
             case 4:{
                if (L->length == 0)
                 {
                     printf("暂无志愿者记录！\n");
                     break;
                 }
                 // 临时数组用于排序
                 Volunteer temp[L->length];
                 memcpy(temp, L->data, L->length * sizeof(Volunteer));
                 // 按星级降序冒泡排序
                 for (int i = 0; i < L->length; i++)
                 {
                     for (int j = i + 1; j < L->length; j++)
                     {
                         if (temp[i].star < temp[j].star)
                         {
                             Volunteer t = temp[i];
                             temp[i] = temp[j];
                             temp[j] = t;
                         }
                     }
                 }
                 printf("===== 志愿者列表（按星级降序）=====\n");
                 for (int i = 0; i < L->length; i++)
                 {
                     printf("学号:%s 姓名:%s 项目:%s 时长:%d 星级:%d星 状态:%s\n",
                            temp[i].stuId, temp[i].name, temp[i].project, temp[i].hour, temp[i].star,
                            temp[i].status == 0 ? "待审核" : temp[i].status == 1 ? "已通过" : "已拒绝");
                 }
                 break;
             }
             default:
                 printf("选项无效，请重新选择！\n");
                 clearBuf();
                 break;
         }
         system("pause");
     }
 }

// 双端队列子菜单
void queueMenu()
{
    DeQueue q;
    initQueue(&q);
    int choice;
    Volunteer v;
    Volunteer outV;

    while (1) {
        printf("\n===== 双端队列子菜单 =====\n");
        printf("1. 紧急项目报名\n");
        printf("2. 普通项目报名\n");
        printf("3. 签到出队\n");
        printf("4. 查看排队\n");
        printf("0. 返回\n");
        printf("请选择：");

        // 菜单输入校验
        if (scanf("%d", &choice) != 1) {
            printf("输入错误！请输入数字选项。\n");
            while (getchar() != '\n'); // 清空缓冲区
            continue;
        }

        switch (choice) {
            case 1:
                printf("请输入 学号 姓名 项目：");
                if (scanf("%s%s%s", v.stuId, v.name, v.project) == 3) {
                    if (enQueueHead(&q, v)) {
                        printf("紧急项目报名成功！已优先排入队头。\n");
                    } else {
                        printf("报名失败，内存不足！\n");
                    }
                } else {
                    printf("输入错误！请按格式输入：学号 姓名 项目\n");
                    while (getchar() != '\n');
                }
                break;

            case 2:
                printf("请输入 学号 姓名 项目：");
                if (scanf("%s%s%s", v.stuId, v.name, v.project) == 3) {
                    if (enQueueTail(&q, v)) {
                        printf("普通项目报名成功！已排入队尾。\n");
                    } else {
                        printf("报名失败，内存不足！\n");
                    }
                } else {
                    printf("输入错误！请按格式输入：学号 姓名 项目\n");
                    while (getchar() != '\n');
                }
                break;

            case 3:
                if (deQueueHead(&q, &outV)) {
                    printf("签到成功！出队信息：学号:%s 姓名:%s 项目:%s\n",
                           outV.stuId, outV.name, outV.project);
                } else {
                    printf("签到失败，队列为空！\n");
                }
                break;

            case 4:
                showQueue(&q);
                break;

            case 0:
                destroyQueue(&q); // 退出前释放内存
                printf("已退出队列管理，队列已清空。\n");
                return;

            default:
                printf("输入错误！请输入0-4之间的数字。\n");
                break;
        }
    }
}

void ShowStack(Stack *s) {
    if (StackIsEmpty(s)) {
        printf("栈为空\n");
        return;
    }
    printf("栈内操作记录数：%d\n", s->top + 1);
}
// DestroyStack 直接清空栈顶即可：
#define DestroyStack(s) ((s)->top = -1)

// BF+KMP 模糊检索菜单
void searchMenu()
{
    char vName[MAX_NAME], vProject[MAX_NAME], key[MAX_SIZE];
    while(1)
    {
        printf("\n===== BF+KMP模糊检索 =====\n");
        printf("1. 输入志愿者信息进行检索\n");
        printf("0. 返回主菜单\n");
        printf("请选择：");

        int op;
        if(scanf("%d", &op) != 1)
        {
            printf("输入错误，请输入数字！\n");
            while(getchar() != '\n');
            continue;
        }

        if(op == 0)
            break;

        if(op == 1)
        {
            printf("输入志愿者姓名：");
            scanf("%s", vName);
            printf("输入服务项目：");
            scanf("%s", vProject);
            printf("输入检索关键词：");
            scanf("%s", key);

            printf("\n===== 检索结果 =====\n");

            int bfName = BF(vName, key);
            int bfProject = BF(vProject, key);
            int kmpName = KMP(vName, key);
            int kmpProject = KMP(vProject, key);

            if(bfName != -1 || bfProject != -1)
                printf("BF算法：匹配到关键词\n");
            else
                printf("BF算法：未匹配到关键词\n");

            if(kmpName != -1 || kmpProject != -1)
                printf("KMP算法：匹配到关键词\n");
            else
                printf("KMP算法：未匹配到关键词\n");
        }
        else
        {
            printf("无效选项，请重新输入！\n");
        }
    }
}

// 多叉树子菜单
void treeMenu(SqList *L)
{
    TreeNode *root = NULL;
    char buf[MAX_NAME];
    char newBuf[MAX_NAME];
    int choice;

    printf("请输入根分类名称（如：志愿项目）：");
    scanf("%s", buf);
    root = CreateRoot(buf);
    printf("根分类创建成功！\n");

    while(1)
    {
        printf("\n===== 志愿项目管理（多叉树）=====\n");
        printf("1. 添加子分类\n");
        printf("2. 修改分类名称\n");
        printf("3. 删除子分类\n");
        printf("4. 遍历查看所有分类\n");
        printf("5. 星级检索（按项目统计）\n");
        printf("6. 服务统计（项目时长汇总）\n");
        printf("0. 返回主菜单\n");
        printf("请选择操作：");

        if(scanf("%d", &choice) != 1)
        {
            printf("输入错误，请输入数字！\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                printf("请输入父分类名称：");
                scanf("%s", buf);
                TreeNode *p = FindNode(root, buf);
                if(p == NULL)
                {
                    printf("未找到该父分类！\n");
                    break;
                }
                printf("请输入新子分类名称：");
                scanf("%s", newBuf);
                AddChild(p, newBuf);
                printf("子分类添加成功！\n");
                break;

            case 2:
                printf("请输入原分类名称：");
                scanf("%s", buf);
                printf("请输入新分类名称：");
                scanf("%s", newBuf);
                ModifyNode(root, buf, newBuf);
                printf("分类名称修改成功！\n");
                break;

            case 3:
                printf("请输入父分类名称：");
                scanf("%s", buf);
                TreeNode *parent = FindNode(root, buf);
                if(parent == NULL)
                {
                    printf("未找到父分类！\n");
                    break;
                }
                printf("请输入要删除的子分类名称：");
                scanf("%s", buf);
                DeleteChild(parent, buf);
                printf("子分类删除成功！\n");
                break;

            case 4:
                printf("\n===== 分类列表（先序遍历）=====\n");
                PreOrderTraverse(root);
                break;

            // 5. 星级检索：按项目统计不同星级的志愿者人数
            case 5:
                printf("请输入要检索的项目名称：");
                scanf("%s", buf);
                printf("\n===== 星级统计 - %s =====\n", buf);
                int starCnt[6] = {0}; // 1-5星
                for(int i = 0; i < L->length; i++)
                {
                    if(strcmp(L->data[i].project, buf) == 0)
                    {
                        int star = L->data[i].star;
                        if(star >= 1 && star <= 5)
                            starCnt[star]++;
                    }
                }
                for(int s = 1; s <= 5; s++)
                {
                    printf("%d星志愿者：%d人\n", s, starCnt[s]);
                }
                break;

            // 6. 服务统计：按项目汇总总服务时长
            case 6:
                printf("请输入要统计的项目名称：");
                scanf("%s", buf);
                int totalHour = 0;
                for(int i = 0; i < L->length; i++)
                {
                    if(strcmp(L->data[i].project, buf) == 0)
                    {
                        totalHour += L->data[i].hour;
                    }
                }
                printf("\n===== 服务统计 - %s =====\n", buf);
                printf("总服务时长：%d小时\n", totalHour);
                break;

            case 0:
                printf("分类树已销毁，返回主菜单\n");
                DestroyTree(root);
                return;

            default:
                printf("选项无效，请重新选择！\n");
                break;
        }
    }
}
// 图BFS子菜单
void graphMenu()
{
    Graph G;
    InitGraph(&G); // 初始化空图
    int choice;
    char name1[MAX_NAME], name2[MAX_NAME];
    int idx1, idx2;

    while(1)
    {
        printf("\n===== 志愿网络图（协作网络/导航）=====\n");
        printf("1. 添加志愿者/地点节点\n");
        printf("2. 添加协作/路径关系\n");
        printf("3. 查询两点间导航最短路径\n");
        printf("0. 返回主菜单\n");
        printf("请输入选择：");

        // 输入校验，防止非数字输入崩溃
        if(scanf("%d", &choice) != 1)
        {
            printf("输入无效，请输入数字！\n");
            while(getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        if(choice == 0) break;

        switch(choice)
        {
            case 1:
                printf("请输入节点名称：");
                scanf("%s", name1);
                AddVex(&G, name1, &idx1);
                printf("节点添加成功！下标：%d\n", idx1);
                break;

            case 2:
                printf("请输入两个节点下标（从0开始）：");
                scanf("%d%d", &idx1, &idx2);
                if(idx1 >= 0 && idx1 < G.vexNum && idx2 >= 0 && idx2 < G.vexNum)
                {
                    AddArc(&G, idx1, idx2);
                    printf("关系添加成功！\n");
                }
                else
                {
                    printf("下标无效，请重新输入！\n");
                }
                break;

            case 3:
                printf("请输入起点和终点下标：");
                scanf("%d%d", &idx1, &idx2);
                if(idx1 >= 0 && idx1 < G.vexNum && idx2 >= 0 && idx2 < G.vexNum)
                {
                    printf("===== BFS导航路径 =====\n");
                    BFS(&G, idx1, idx2);
                }
                else
                {
                    printf("下标无效，请重新输入！\n");
                }
                break;

            default:
                printf("输入错误，请重新选择！\n");
                break;
        }
    }

    // 退出菜单前销毁图，释放所有内存
    DestroyGraph(&G);
}

// 模糊检索效率对比
void fuzzySearchMenu(SqList *L)
{
    char keyword[30];
    printf("请输入要检索的关键词：");
    scanf("%s", keyword);

    int countBF = 0, countKMP = 0;

    // BF算法检索：遍历顺序表，匹配姓名或项目
    printf("===== BF算法检索结果 =====\n");
    for(int i = 0; i < L->length; i++)
    {
        if(BF(L->data[i].name, keyword) != -1 || BF(L->data[i].project, keyword) != -1)
        {
            printf("找到：%s - %s\n", L->data[i].name, L->data[i].project);
            countBF++;
        }
    }
    printf("BF算法共找到 %d 条结果\n", countBF);

    // KMP算法检索：同上
    printf("\n===== KMP算法检索结果 =====\n");
    for(int i = 0; i < L->length; i++)
    {
        if(KMP(L->data[i].name, keyword) != -1 || KMP(L->data[i].project, keyword) != -1)
        {
            printf("找到：%s - %s\n", L->data[i].name, L->data[i].project);
            countKMP++;
        }
    }
    printf("KMP算法共找到 %d 条结果\n", countKMP);
}

// 广义表子菜单
void glistMenu()
{
    GList L;
    InitGList(&L);  // 初始化空表，避免野指针
    char buf[200];
    int choice;

    while(1)
    {
        printf("\n===== 广义表档案存储 =====\n");
        printf("1. 新建档案\n");
        printf("2. 查看档案\n");
        printf("3. 计算贡献度\n");
        printf("0. 返回主菜单\n");
        printf("格式示例：(张三,志愿活动,40h,5星)\n");
        printf("请输入选择：");

        // 输入校验：防止非数字输入导致程序崩溃
        if(scanf("%d", &choice) != 1)
        {
            printf("输入无效，请输入数字！\n");
            while(getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        if(choice == 0)
            break;

        switch(choice)
        {
            case 1:
                printf("请输入广义表字符串：");
                scanf("%s", buf);
                DestroyGList(&L); // 先销毁旧档案，避免内存泄漏
                CreateGList(&L, buf);
                printf("档案录入完成！\n");
                break;
            case 2:
                printf("解析结果：");
                TraverseGList(L);
                printf("\n");
                break;
            case 3:
                printf("===== 贡献度层级统计 =====\n");
                CalcContributionLevel(L);
                break;
            default:
                printf("输入错误，请重新选择！\n");
        }
        system("pause");
    }

    // 退出菜单前销毁广义表，释放所有内存
    DestroyGList(&L);
}

// 哈希表子菜单
void hashMenu()
{
    printf("\n------------------------------\n");
    hashSystemMenu();
    system("pause");
}
