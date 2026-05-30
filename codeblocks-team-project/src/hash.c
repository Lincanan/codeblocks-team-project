#include <stdio.h>
#include "mystring.h"
#include "hash.h"

int hashTable[HASH_SIZE];

// 先定义结构体
typedef struct {
    int count;
    int probeCnt;
}HashStat;

float CalculateASL(int total_probe_cnt, int valid_cnt) {
    if (valid_cnt == 0) {
        return 0.0f;
    }
    return (float)total_probe_cnt / valid_cnt;
}

// printHashEfficiency 定义
void printHashEfficiency(int total_probe_cnt, int valid_cnt) {
    float asl = CalculateASL(total_probe_cnt, valid_cnt);
    printf("\n===== 哈希表效率统计 =====\n");
    printf("有效元素数：%d\n", valid_cnt);
    printf("总探测次数：%d\n", total_probe_cnt);
    printf("平均查找长度 ASL = %.2f\n", asl);
}

// 哈希函数：除留余数法
int HashFunc(int stu_id, int m)
{
    return stu_id % m;
}

// 哈希表插入，返回本次查找次数
int HashInsert(int table[], int stu_id, int m)
{
    int index = HashFunc(stu_id, m);
    int search_count = 1;
    int start_index = index;

    // 线性探测解决冲突
    while(table[index] != -1 && table[index] != stu_id && search_count <= m)
    {
        index = (index + 1) % m;
        search_count++;
    }
    if(search_count > m){
        printf("哈希表已满，无法插入学号: %d\n",stu_id);
        return 0;
    }

    if(table[index] == -1)
    {
        table[index] = stu_id;
    }
    return search_count;
}

// 构建哈希表 + 计算平均查找长度ASL
double BuildHashAndCalcASL(int ids[], int len, int table[])
{
    for(int i=0;i<HASH_MAX;i++) table[i] = -1;

    int total_search = 0;
    int valid_cnt = 0;

    for(int i=0;i<len;i++)
    {
        int id = ids[i];
        if(id > 0)
        {
            int cnt = HashInsert(table, id, HASH_MAX);
            total_search += cnt;
            valid_cnt++;
        }
    }

    double ASL;
    if(valid_cnt == 0)
        ASL = 0;
    else
        ASL = (double)total_search / valid_cnt;

    return ASL;
}

// 哈希表查找，返回下标和查找次数
void HashSearch(int table[], int stu_id, int m, int *idx, int *cnt)
{
    int index = HashFunc(stu_id, m);
    int search_count = 1;
    int start = index;

    while(table[index] != -1 && table[index]!=stu_id && search_count <= m)
    {
        if(index == start && search_count > 1)
        {
            break;
        }
        index = (index + 1)%m;
        search_count++;
    }

    if(table[index] == stu_id)
    {
        *idx = index;
        *cnt = search_count;
    }
    else{
        *idx = -1;
        *cnt = search_count;
    }
}

// 哈希表功能菜单
void hashSystemMenu()
{
    // 1. 构建测试数据并计算平均查找长度ASL
    int testIds[] = {2023001, 2023002, 2023015, 2023030, 2023099};
    int idNum = sizeof(testIds) / sizeof(testIds[0]);

    // 构建哈希表并计算ASL（使用全局hashTable）
    double asl = BuildHashAndCalcASL(testIds, idNum, hashTable);
    printf("===== 哈希表构建完成 =====\n");
    printf("平均查找长度 ASL = %.2f\n", asl);

    // 2. 菜单主循环
    int op;
    while (1)
    {
        printf("\n===== 8. 学号快速查找 =====\n");
        printf("1. 查找学号\n");
        printf("2. 查看哈希表平均查找长度ASL\n");
        printf("0. 返回主菜单\n");
        printf("请输入选择：");

        // 输入校验，防止非数字输入崩溃
        if (scanf("%d", &op) != 1)
        {
            printf("输入无效，请输入数字！\n");
            while(getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        if (op == 0)
        {
            printf("退出哈希查找菜单\n");
            break;
        }

        if (op == 1)
        {
            int searchId;
            printf("请输入要查找的纯数字学号：");
            if (scanf("%d", &searchId) != 1)
            {
                printf("学号必须是数字！\n");
                while(getchar() != '\n');
                continue;
            }

            int pos, count;
            HashSearch(hashTable, searchId, HASH_MAX, &pos, &count);

            if (pos != -1)
            {
                printf("查找成功！下标：%d，探测次数：%d\n", pos, count);
            }
            else
            {
                printf("查找失败！探测次数：%d\n", count);
            }
        }
        else if (op == 2)
        {
            printf("当前哈希表的平均查找长度 ASL = %.2f\n", asl);
        }
        else
        {
            printf("选项无效，请重新选择！\n");
        }

        system("pause");
    }
}