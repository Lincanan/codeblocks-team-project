#include "mystring.h"

int my_strlen(const char *s){
    int len = 0;
    while(s[len] != '\0') len++;
    return len;
}

int my_strcmp(const char *a, const char *b){
    while(*a && *b && *a == *b){ a++; b++; }
    return *a - *b;
}

char* my_strcpy(char *dest, const char *src){
    int i=0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}