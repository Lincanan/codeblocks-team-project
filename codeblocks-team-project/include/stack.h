#ifndef STACK_H
#define STACK_H

#include "list.h"
#include "public.h"

#define STACK_MAX 100

// 操作类型：报名/签到/星级修改
typedef enum {
    OP_ENROLL,    // 报名
    OP_SIGN_IN,   // 签到
    OP_HOUR_RESET,// 服务时长重置
    OP_STAR_RESET // 星级重置
} OpType;

// 栈元素：存储操作前的状态，用于回滚
typedef struct {
    char stuId[15];    // 学号
    int oldHour;       // 原服务时长
    int oldStar;       // 原星级
    OpType opType;     // 操作类型
} StackElem;

// 顺序栈定义
typedef struct {
    StackElem data[STACK_MAX];
    int top; // 栈顶指针，-1 表示空栈
} Stack;

// 栈操作函数声明
void InitStack(Stack *s);
int StackPush(Stack *s, StackElem e);
int StackPop(Stack *s, StackElem *e);
int StackIsEmpty(Stack *s);
void ShowStack(Stack *s);
void RecordOperation(Stack *s, Volunteer v, OpType op);
int UndoOperation(Stack *s, SqList *L);
void stackMenu(Stack *s, SqList *L);
void DestroyStack(Stack *s);

#endif