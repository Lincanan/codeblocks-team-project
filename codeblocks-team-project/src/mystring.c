#include "mystring.h"
#include <stdio.h>

int my_strlen(const char *s){
    int len = 0;
    while(s[len] != '\0') len++;
    return len;
}

// 自定义字符串拷贝
void my_strcpy(char *dest,const char *src)
{
    if (dest == NULL || src == NULL)
        return;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// 自定义字符串比较（替代库函数 strcmp）
int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}