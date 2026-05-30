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
    int i = 0,j = -1;
    next[0] = -1;
    while(i < m-1)
    {
        // 不匹配则回退
        if(j == -1 || pattern[i] == pattern[j])
        {
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

// KMP高效匹配算法
int KMP(char *text, char *pattern)
 {
     int n = my_strlen(text);
     int m = my_strlen(pattern);
     int next[MAX_SIZE];
     if (n == 0 || m == 0)
         return -1;
     BuildNext(pattern, next);
     int i = 0, j = 0;
     while (i < n && j < m)
     {
         if (j == -1 || text[i] == pattern[j])
         {
             i++;
             j++;
         }
         else
         {
             j = next[j];
         }
     }
     if (j == m)
         return i - j;
     return -1;
 }
// 统一查询：同时输出 BF、KMP 结果
 void VolunteerSearchBF_KMP(char name[], char project[], char key[])
 {
     int resNameBF = BF(name, key);
     int resProjBF = BF(project, key);
     int resNameKMP = KMP(name, key);
     int resProjKMP = KMP(project, key);
     printf("===== 检索结果 =====\n");
     if (resNameBF != -1 || resProjBF != -1)
         printf("BF算法：匹配成功\n");
     else
         printf("BF算法：未匹配到关键词\n");
     if (resNameKMP != -1 || resProjKMP != -1)
         printf("KMP算法：匹配成功\n");
     else
         printf("KMP算法：未匹配到关键词\n");
 }
