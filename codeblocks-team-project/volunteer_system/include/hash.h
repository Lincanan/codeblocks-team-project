#ifndef HASH_H
#define HASH_H
#define HASH_MAX 100

//哈希函数：除留余数
int HashFunc(int id,int m);
//构建哈希表+计算ASL平均查找长度
double BuildHashAndCalcASL(int ids[],int len,int table[]);
//查找：pos返回下标，cnt探测次数
void HashSearch(int table[],int id,int m,int *pos,int *cnt);
void hashSystemMenu();

#endif