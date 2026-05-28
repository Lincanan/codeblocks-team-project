#ifndef QUEUE_H
#define QUEUE_H

#include "public.h"

// 循环双端队列结构体
typedef struct{
    Volunteer data[MAX_SIZE];
    int front;
    int rear;
} DeQueue;

// 函数声明
void InitQueue(DeQueue *q);
int EnQueueHead(DeQueue *q, Volunteer v);
int EnQueueTail(DeQueue *q, Volunteer v);
int DeQueueHead(DeQueue *q, Volunteer *v);
void ShowQueue(DeQueue *q);

#endif