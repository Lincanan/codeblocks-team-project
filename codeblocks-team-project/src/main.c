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

SqList L;
Stack st;

// 函数声明
void mainMenu();
void listMenu(SqList *L,Stack *s);
void queueMenu();
void stackMenu(Stack *s,SqList *L);
void searchMenu();
void treeMenu();
void graphMenu();
void glistMenu();
void hashMenu();

void clearBuf(void){
    int ch;
    while((ch = getchar())!=EOF && ch !='\n');
}

int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    for (int i = 0; i < HASH_MAX; i++)
    {
        hashTable[i] = -1;
    }

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
void listMenu(SqList *L, Stack *s)
{
    int op;
    char stuId[15];
    Volunteer v;

    while (1)
    {
        printf("\n------------------------------------\n");
        printf("===== 志愿者记录管理菜单 =====\n");
        printf("1. 新增志愿者(报名)\n");
        printf("2. 按学号删除(可撤销)\n");
        printf("3. 修改信息(时长/星级/姓名等)\n");
        printf("4. 签到(增加服务时长)\n");
        printf("5. 重置星级\n");
        printf("0. 返回主菜单\n");
        printf("请选择操作：");

        // 每次循环都重新读取 op，并校验输入
        if (scanf("%d", &op) != 1)
        {
            printf("输入无效，请输入数字！\n");
            clearBuf();
            continue;
        }
        clearBuf();
        if (op == 0)
        {
            printf("返回主菜单...\n");
            break;
        }

        switch (op)
        {
            case 1:
            {
                // 1. 新增志愿者（带哈希表同步，保证不卡）
                printf("请输入学号：");
                scanf("%s", v.stuId);
                while(getchar() != '\n'); // 清空残留

                printf("请输入姓名：");
                scanf("%s", v.name);
                while(getchar() != '\n');

                printf("请输入项目：");
                scanf("%s", v.project);
                while(getchar() != '\n');

                // 服务时长（带校验）
                while (1)
                {
                    printf("请输入服务时长：");
                    if (scanf("%d", &v.hour) == 1)
                    {
                        while(getchar() != '\n');
                        break;
                    }
                    printf("输入无效，请输入数字！\n");
                    while(getchar() != '\n');
                }
                // 星级（带校验）
                while (1)
                {
                    printf("请输入星级：");
                    if (scanf("%d", &v.star) == 1)
                    {
                        while(getchar() != '\n');
                        break;
                    }
                    printf("输入无效，请输入数字！\n");
                    while(getchar() != '\n');
                }
                // 记录操作（用于撤销）
                RecordOperation(s, v, OP_ENROLL);
                // 插入线性表
                if (ListInsert(L, L->length, v))
                {
                    printf("插入成功！\n");
                    printf("志愿者添加成功！\n");
                    // 同步添加到哈希表
                    int stuIdInt = atoi(v.stuId); // 把学号字符串转成整数
                    int probe_cnt = HashInsert(hashTable,stuIdInt,HASH_SIZE);
                    printf("DEBUG:学号%d插入哈希表，探测次数: %d\n",stuIdInt,probe_cnt);
                    if(probe_cnt>0)
                    {
                        printf("志愿者同步添加到哈希表成功！\n");
                    }
                    else
                    {
                        printf("哈希表插入失败，无法支持学号快速查找\n");
                    }
                }
                else
                {
                    printf("添加失败！可能是表已满或位置不合法\n");
                }
                // 关键：只在最后加一次break，不额外加清空代码
                break;
            }

            case 2:
                // 2. 删除记录 —— 压栈 OP_ENROLL
                printf("请输入要删除的学号：");
                scanf("%s", stuId);
                int idx = LocateElem(L, stuId);
                if (idx == -1)
                {
                    printf("无此志愿者！\n");
                    while(getchar() != '\n');
                    break;
                }

                RecordOperation(s, L->data[idx], OP_ENROLL);
                ListDelete(L, stuId);
                printf("删除成功！\n");
                while(getchar() != '\n');
                break;

            case 3:
                // 3. 修改信息
                printf("请输入要修改的学号：");
                scanf("%s", stuId);
                ListUpdate(L, stuId);
                while(getchar() != '\n');
                break;

            case 4:
                // 4. 签到 → 增加服务时长（时长回退）
                printf("请输入签到学号：");
                scanf("%s", stuId);
                int pos = LocateElem(L, stuId);
                if (pos == -1)
                {
                    printf("无此志愿者！\n");
                    while(getchar() != '\n');
                    break;
                }

                // 记录原时长，用于签到回滚
                RecordOperation(s, L->data[pos], OP_SIGN_IN);
                L->data[pos].hour += 1;
                printf("签到成功！时长+1\n");
                while(getchar() != '\n');
                break;

            case 5:
                // 5. 星级重置（星级回退）
                printf("请输入学号：");
                scanf("%s", stuId);
                int p = LocateElem(L, stuId);
                if (p == -1)
                {
                    printf("无此志愿者！\n");
                    while(getchar() != '\n');
                    break;
                }

                // 记录原星级，用于回滚
                RecordOperation(s, L->data[p], OP_STAR_RESET);
                L->data[p].star = 1;
                printf("星级已重置为1\n");
                while(getchar() != '\n');
                break;

            default:
                printf("选项无效！请重新选择\n");
                while(getchar() != '\n');
                break;
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
        printf("1. 紧急项目报名   2. 普通项目报名\n");
        printf("3. 签到出队       4. 查看排队\n");
        printf("0. 返回\n");
        printf("选择：");
        
        // 菜单输入校验，防止非数字输入崩溃
        if (scanf("%d", &choice) != 1) {
            printf("输入错误！请输入数字选项。\n");
            while(getchar() != '\n'); // 清空缓冲区
            continue;
        }

        switch(choice)
        {
            case 1:
                printf("学号 姓名 项目：");
                // 输入校验：确保读取到3个字符串
                if (scanf("%s%s%s", v.stuId, v.name, v.project) != 3) {
                    printf("输入错误！请按格式输入：学号 姓名 项目\n");
                    while(getchar() != '\n');
                    break;
                }
                EnQueueHead(&q, v);
                break;
            case 2:
                printf("学号 姓名 项目：");
                if (scanf("%s%s%s", v.stuId, v.name, v.project) != 3) {
                    printf("输入错误！请按格式输入：学号 姓名 项目\n");
                    while(getchar() != '\n');
                    break;
                }
                EnQueueTail(&q, v);
                break;
            case 3:
                DeQueueHead(&q, &v);
                break;
            case 4:
                ShowQueue(&q);
                break;
            case 0:
                // 退出前销毁队列
                DestroyQueue(&q);
                return;
            default:
                printf("输入错误！\n");
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

            // 调用你原来的业务接口
            VolunteerSearchBF_KMP(vName, vProject, key);
        }
        else
        {
            printf("无效选项，请重新输入！\n");
        }
    }
}

// 多叉树子菜单
void treeMenu()
 {
     TreeNode *root = NULL;
     char buf[MAX_NAME];
     char newBuf[MAX_NAME];
     int choice;
     printf("\n===== 志愿者项目分类（多叉树） =====\n");
     printf("请输入根分类名称：");
     scanf("%s", buf);
     root = CreateRoot(buf);
     printf("根分类创建成功！\n");
     while(1)
     {
         printf("\n1. 添加子分类   2. 修改分类名称\n");
         printf("3. 删除子分类   4. 遍历查看所有分类\n");
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
                 if (p == NULL)
                 {
                     printf("未找到该父分类！\n");
                     break;
                 }
                 printf("请输入新子分类名称：");
                 scanf("%s", buf);
                 AddChild(p, buf);
                 printf("子分类添加成功！\n");
                 break;
             case 2:
                 printf("请输入原分类名称：");
                 scanf("%s", buf);
                 printf("请输入新分类名称：");
                 scanf("%s", newBuf);
                 ModifyNode(root, buf, newBuf);
                 break;
             case 3:
                 printf("请输入父分类名称：");
                 scanf("%s", buf);
                 TreeNode *parent = FindNode(root, buf);
                 if (parent == NULL)
                 {
                     printf("未找到父分类！\n");
                     break;
                 }
                 printf("请输入要删除的子分类名称：");
                 scanf("%s", buf);
                 DeleteChild(parent, buf);
                 break;
             case 4:
                 printf("===== 分类列表（先序遍历） =====\n");
                 PreOrderTraverse(root);
                 break;
             case 0:
                 DestroyTree(root);
                 printf("分类树已销毁，返回主菜单\n");
                 return;
             default:
                 printf("选项无效，请重新选择！\n");
         }
     }
 }

// 图BFS子菜单
void graphMenu()
{
    Graph G;
    InitGraph(&G);  // 初始化空图
    int choice;
    char name1[MAX_NAME], name2[MAX_NAME];
    int idx1, idx2;

    while(1)
    {
        printf("\n===== 6. 图模块（协作网络/导航） =====\n");
        printf("1. 添加志愿者/地点节点\n");
        printf("2. 添加协作/路径关系\n");
        printf("3. 查询两点间最短路径\n");
        printf("0. 返回主菜单\n");
        printf("请输入选择：");

        // 输入校验，防止非数字输入崩溃
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            while(getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        if (choice == 0) break;

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
                if (idx1 >= 0 && idx1 < G.vexNum && idx2 >= 0 && idx2 < G.vexNum) {
                    AddArc(&G, idx1, idx2);
                    printf("关系添加成功！\n");
                } else {
                    printf("下标无效，请重新输入！\n");
                }
                break;
            case 3:
                printf("请输入起点和终点下标：");
                scanf("%d%d", &idx1, &idx2);
                if (idx1 >= 0 && idx1 < G.vexNum && idx2 >= 0 && idx2 < G.vexNum) {
                    BFS(&G, idx1, idx2);
                } else {
                    printf("下标无效，请重新输入！\n");
                }
                break;
            default:
                printf("输入错误，请重新选择！\n");
        }
        system("pause");
    }

    // 退出菜单前销毁图，释放所有内存
    DestroyGraph(&G);
}

// 模糊检索效率对比
void fuzzySearchMenu(SqList *L) {
    char keyword[30];
    printf("请输入要检索的关键词：");
    scanf("%s", keyword);
    int countBF = 0, countKMP = 0;
    int timeBF, timeKMP;

    // BF算法检索
    printf("===== BF算法检索结果 =====\n");
    for (int i = 0; i < L->length; i++) {
        if (BF(L->data[i].name, keyword) != -1 || BF(L->data[i].project, keyword) != -1) {
            printf("找到：%s - %s\n", L->data[i].name, L->data[i].project);
            countBF++;
        }
    }
    printf("BF算法共找到 %d 条结果\n", countBF);

    // KMP算法检索
    printf("\n===== KMP算法检索结果 =====\n");
    for (int i = 0; i < L->length; i++) {
        if (KMP(L->data[i].name, keyword) != -1 || KMP(L->data[i].project, keyword) != -1) {
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
