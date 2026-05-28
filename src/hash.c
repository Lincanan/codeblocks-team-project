#include <stdio.h>
#include <string.h>
#include "hash.h"

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

    // 线性探测解决冲突
    while(table[index] != -1 && table[index] != stu_id)
    {
        index = (index + 1) % m;
        search_count++;
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

    while(table[index] != -1)
    {
        if(table[index] == stu_id)
        {
            *idx = index;
            *cnt = search_count;
            return;
        }
        index = (index + 1) % m;
        search_count++;

        if(index == start) break;
    }

    *idx = -1;
    *cnt = search_count;
}

// 哈希表功能菜单
void hashSystemMenu()
{
    int hashTable[HASH_MAX];
    // 测试学号数据
    int testIds[] = {2023001,2023002,2023015,2023030,2023099};
    int idNum = sizeof(testIds)/sizeof(testIds[0]);

    double asl = BuildHashAndCalcASL(testIds, idNum, hashTable);
    printf("✅ 哈希表构建完成\n");
    printf("📊 平均查找长度ASL = %.2f\n", asl);

    int searchId, pos, count;
    while(1)
    {
        printf("\n===== 哈希表学号查找 =====\n");
        printf("1. 查找学号 0. 返回\n");
        printf("选择：");
        int op; scanf("%d",&op);
        if(op == 0) break;

        printf("输入要查找的纯数字学号：");
        scanf("%d",&searchId);
        HashSearch(hashTable, searchId, HASH_MAX, &pos, &count);

        if(pos != -1)
            printf("查找成功！下标:%d 查找次数:%d\n",pos,count);
        else
            printf("查找失败！探测次数:%d\n",count);
    }
}