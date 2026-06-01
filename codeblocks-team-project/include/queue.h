#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"public.h"

// 双端队列节点
typedef struct QNode {
    Volunteer data;
    struct QNode *prev;
    struct QNode *next;
} QNode;

// 双端队列结构体
typedef struct DeQueue {
    QNode *front;
    QNode *rear;
} DeQueue;

// 函数声明（必须和queue.c里的定义完全一致！）
void initQueue(DeQueue *q);
int isQueueEmpty(DeQueue *q);
int enQueueHead(DeQueue *q, Volunteer v);
int enQueueTail(DeQueue *q, Volunteer v);
int deQueueHead(DeQueue *q, Volunteer *v);
void showQueue(DeQueue *q);
void destroyQueue(DeQueue *q);

#endif