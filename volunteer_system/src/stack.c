#include <stdio.h>
#include "stack.h"

// 初始化栈：栈顶指针置为-1
void InitStack(Stack *s)
{
    s->top = -1;
}

// 入栈操作
int Push(Stack *s, Volunteer v)
{
    // 判断栈满
    if(s->top >= MAX_SIZE - 1)
    {
        printf("栈已满，无法保存操作！\n");
        return 0;
    }
    s->data[++s->top] = v;
    return 1;
}

// 出栈操作
int Pop(Stack *s, Volunteer *v)
{
    // 判断栈空
    if(StackEmpty(s))
    {
        printf("暂无历史操作，无法撤销！\n");
        return 0;
    }
    *v = s->data[s->top--];
    return 1;
}

// 判断栈空
int StackEmpty(Stack *s)
{
    return s->top == -1;
}