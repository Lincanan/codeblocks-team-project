#ifndef HASH_H
#define HASH_H

#include "public.h"

#define HASH_SIZE 100
#define HASH_MAX 100

extern int hashTable[HASH_SIZE]; // 哈希表长度

// 哈希函数：除留余数法
int HashFunc(int stu_id, int m);

// 哈希表插入，返回本次查找次数
int HashInsert(int table[], int stu_id,int m);

// 构建哈希表并计算平均查找长度ASL
double BuildHashAndCalcASL(int ids[], int len, int table[]);

// 哈希表查找，返回下标和查找次数
void HashSearch(int table[], int stu_id, int m, int *idx, int *cnt);

// 哈希表功能菜单
void hashSystemMenu();

// 计算平均查找长度
float CalculateASL(int total_probe_cnt, int valid_cnt);
// 打印哈希表效率统计
void printHashEfficiency(int total_probe_cnt, int valid_cnt);

#endif