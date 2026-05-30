#ifndef STRING_MATCH_H
#define STRING_MATCH_H

#include "public.h"

// BF暴力匹配
int BF(char *text, char *pattern);
// 构建KMP前缀Next数组
void BuildNext(char *pattern, int next[]);
// KMP匹配算法
int KMP(char *text, char *pattern);
// 统一查询接口
void VolunteerSearchBF_KMP(char name[],char project[],char key[]);

#endif