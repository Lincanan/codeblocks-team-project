#include <stdio.h>
#include "mystring.h"
#include "string_match.h"
#include "list.h"
#include "public.h"
extern SqList L;

// BF朴素匹配算法
int BF(char *text, char *pattern)
{
    int i = 0, j = 0;
    int n = my_strlen(text);
    int m = my_strlen(pattern);

    if(m == 0) return 0;   // 关键词为空
    if(n == 0) return -1;  // 主串为空
    if(m > n) return -1;  //模式串比主串长，直接匹配失败

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
            return i - m ;
    }
    return -1;
}

// 志愿者模糊搜索业务函数
void VolunteerSearchBF_KMP(char key[])
{
    int total = 0;
    printf("\n========== 检索结果 ==========\n");

    // 遍历整个志愿者数组
    for(int i = 0; i < L.length; i++)
    {
        Volunteer p = L.data[i];
        // 对每个志愿者的姓名和项目分别做BF/KMP匹配
        int resBF_name = BF(p.name, key);
        int resBF_proj = BF(p.project, key);
        int resKMP_name = KMP(p.name, key);
        int resKMP_proj = KMP(p.project, key);

        // 任意一个匹配成功就算命中
        if( (resBF_name != -1 || resBF_proj != -1) || 
            (resKMP_name != -1 || resKMP_proj != -1) )
        {
            total++;
            printf("学号：%s\n", p.stuId);
            printf("姓名：%s\n", p.name);
            printf("项目：%s\n", p.project);
            printf("时长：%d小时\n", p.hour);
            printf("星级：%d星\n\n", p.star);
        }
    }

    if(total == 0)
    {
        printf("BF姓名检索：未找到\n");
        printf("KMP项目检索：未找到\n");
    }
    else
    {
        printf("共找到 %d 条匹配记录\n", total);
    }
}