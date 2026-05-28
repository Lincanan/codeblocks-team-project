#include <stdio.h>
#include "mystring.h"
#include "string_match.h"

// BF朴素匹配算法
int BF(char *text, char *pattern)
{
    int i = 0, j = 0;
    int n = my_strlen(text);
    int m = my_strlen(pattern);

    if(m == 0) return 0;   // 关键词为空
    if(n == 0) return -1;  // 主串为空

    // 逐个字符比对
    while(i < n && j < m)
    {
        if(text[i] == pattern[j])
        {
            i++; j++;
        }
        else
        {
            // 匹配失败，指针回退
            i = i - j + 1;
            j = 0;
        }
    }

    // 返回匹配结果
    if(j == m)
        return i - j;
    return -1;
}

// KMP算法 构建next数组
void BuildNext(char *pattern, int next[])
{
    int m = my_strlen(pattern);
    int j = 0;
    next[0] = 0;

    for(int i = 1; i < m; i++)
    {
        // 不匹配则回退
        while(j > 0 && pattern[i] != pattern[j])
            j = next[j-1];
        // 匹配则长度+1
        if(pattern[i] == pattern[j])
            j++;
        next[i] = j;
    }
}

// KMP高效匹配算法
int KMP(char *text, char *pattern)
{
    int n = my_strlen(text);
    int m = my_strlen(pattern);

    if(m == 0) return 0;
    if(n == 0) return -1;

    int next[1000];
    BuildNext(pattern, next);
    int j = 0;

    for(int i = 0; i < n; i++)
    {
        // 利用next数组减少无效回溯
        while(j > 0 && text[i] != pattern[j])
            j = next[j-1];

        if(text[i] == pattern[j])
            j++;

        // 匹配完成
        if(j == m)
            return i - m + 1;
    }
    return -1;
}

// 志愿者模糊搜索业务函数
void VolunteerSearchBF_KMP(char name[], char project[], char key[])
{
    int resBF = BF(name, key);
    int resKMP = KMP(project, key);

    printf("\n  BF姓名检索:%s\n", resBF!=-1 ? "匹配成功" : "未找到");
    printf(" KMP项目检索:%s\n", resKMP!=-1 ? "匹配成功" : "未找到");
}