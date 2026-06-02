#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "hash.h"
#include "list.h"
extern SqList L; //引用main全局顺序表

int HashFunc(int id,int m)
{
    return id%m;
}

double BuildHashAndCalcASL(int ids[],int len,int table[])
{
    //初始化哈希：-1为空
    for(int i=0;i<HASH_MAX;i++) table[i]=-1;
    int totalCnt=0;
    //线性探测插入
    for(int i=0;i<len;i++)
    {
        int key=ids[i];
        int pos=HashFunc(key,HASH_MAX);
        int step=0;
        while(table[(pos+step)%HASH_MAX]!=-1) step++;
        pos=(pos+step)%HASH_MAX;
        table[pos]=key;
        totalCnt+=step+1;
    }
    if(len==0) return 1.0;
    return (double)totalCnt/len;
}

void HashSearch(int table[],int id,int m,int *pos,int *cnt)
{
    *cnt=0;
    int start=HashFunc(id,m);
    for(int i=0;i<m;i++)
    {
        (*cnt)++;
        int cur=(start+i)%m;
        if(table[cur]==-1){*pos=-1;return;}
        if(table[cur]==id){*pos=cur;return;}
    }
    *pos=-1;
}

//8号哈希菜单
void hashSystemMenu()
{
    int hashTable[HASH_MAX];
    int tempArr[HASH_MAX]={0};
    int n=L.length;
    //自动把顺序表全部char学号转int存入数组
    for(int i=0;i<n;i++)
    {
        tempArr[i]=atoi(L.data[i].stuId);
    }
    double asl=BuildHashAndCalcASL(tempArr,n,hashTable);
    printf("哈希表构建完成\n平均查找长度ASL = %.2f\n",asl);

    int op,searchId,pos,cnt;
    while(1)
    {
        printf("\n=====哈希学号查找====\n1.查找学号 0.返回\n选择：");
        scanf("%d",&op);
        if(op==0) break;
        printf("输入学号：");
        scanf("%d",&searchId);
        HashSearch(hashTable,searchId,HASH_MAX,&pos,&cnt);
        if(pos!=-1){
            printf("查找成功！下标：%d 探测次数：%d\n",pos,cnt);
            int key = searchId;
            char tmp[20];
            sprintf(tmp,"%d",key);
            for(int i=0;i<L.length;i++){
                if(my_strcmp(L.data[i].stuId,tmp)==0)
                {
                    printf("====志愿者信息====\n");
                    printf("学号：%s 姓名：%s 项目：%s 时长：%d 星级：%d\n",
                    L.data[i].stuId,L.data[i].name,L.data[i].project,L.data[i].hour,L.data[i].star);
                }
            }
        }
        else{
            printf("无此数据，查找失败！探测次数：%d\n",cnt);
        }
    }
}