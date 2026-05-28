#ifndef HASH_H
#define HASH_H
#include "public.h"

#define HASH_MAX 100

// 函数声明
int HashFunc(int stu_id, int m);
int HashInsert(int table[], int stu_id, int m);
double BuildHashAndCalcASL(int ids[], int len, int table[]);
void HashSearch(int table[], int stu_id, int m, int *idx, int *cnt);
void hashSystemMenu();

#endif