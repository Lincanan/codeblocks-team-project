#include <stdio.h>
#include "queue.h"

// 初始化队列
void InitQueue(DeQueue *q)
{
    q->front = q->rear = 0;
}

// 判断队列是否已满
int IsFull(DeQueue *q)
{
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 判断队列是否为空
int IsEmpty(DeQueue *q)
{
    return q->front == q->rear;
}

// 队头入队（紧急项目优先）
int EnQueueHead(DeQueue *q, Volunteer v)
{
    if(IsFull(q)){printf("队列已满！\n");return 0;}
    q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
    q->data[q->front] = v;
    printf("紧急项目入队成功！\n");
    return 1;
}

// 队尾入队（普通项目）
int EnQueueTail(DeQueue *q, Volunteer v)
{
    if(IsFull(q)){printf("队列已满！\n");return 0;}
    q->data[q->rear] = v;
    q->rear = (q->rear + 1) % MAX_SIZE;
    printf("普通项目入队成功！\n");
    return 1;
}

// 队头出队（签到完成）
int DeQueueHead(DeQueue *q, Volunteer *v)
{
    if(IsEmpty(q)){printf("队列为空！\n");return 0;}
    *v = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    printf("签到出队成功！\n");
    return 1;
}

// 遍历展示队列所有排队人员
void ShowQueue(DeQueue *q)
{
    if(IsEmpty(q)){printf("队列无人排队！\n");return;}
    printf("===== 排队列表 =====\n");
    int i = q->front;
    while(i != q->rear)
    {
        printf("学号：%s 姓名：%s 项目：%s\n",
               q->data[i].stuId, q->data[i].name, q->data[i].project);
        i = (i+1) % MAX_SIZE;
    }
}