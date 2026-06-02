#ifndef STACK_H
#define STACK_H
#include "public.h"

// 栈结构体
typedef struct{
    Volunteer data[MAX_SIZE];
    int top;
} Stack;

// 函数声明
void InitStack(Stack *s);        // 初始化栈
int Push(Stack *s, Volunteer v); // 入栈（保存操作）
int Pop(Stack *s, Volunteer *v); // 出栈（撤销操作）
int StackEmpty(Stack *s);        // 判断栈是否为空
int StackLength(Stack *s);

#endif