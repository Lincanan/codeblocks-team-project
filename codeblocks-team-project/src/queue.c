#include "queue.h"

// 初始化双端队列
void initQueue(DeQueue *q) {
    q->front = q->rear = NULL;
}

// 判断队列是否为空
int isQueueEmpty(DeQueue *q) {
    return q->front == NULL;
}

// 队头入队（紧急项目）
int enQueueHead(DeQueue *q, Volunteer v) {
    QNode *p = (QNode *)malloc(sizeof(QNode));
    if (!p) return 0;
    p->data = v;
    p->prev = NULL;
    p->next = q->front;

    if (isQueueEmpty(q)) {
        q->rear = p;
    } else {
        q->front->prev = p;
    }
    q->front = p;
    return 1;
}

// 队尾入队（普通项目）
int enQueueTail(DeQueue *q, Volunteer v) {
    QNode *p = (QNode *)malloc(sizeof(QNode));
    if (!p) return 0;
    p->data = v;
    p->next = NULL;
    p->prev = q->rear;

    if (isQueueEmpty(q)) {
        q->front = p;
    } else {
        q->rear->next = p;
    }
    q->rear = p;
    return 1;
}

// 队头出队（签到）
int deQueueHead(DeQueue *q, Volunteer *v) {
    if (isQueueEmpty(q)) return 0;
    QNode *p = q->front;
    *v = p->data;

    if (q->front == q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = p->next;
        q->front->prev = NULL;
    }
    free(p);
    return 1;
}

// 查看所有排队
void showQueue(DeQueue *q) {
    if (isQueueEmpty(q)) {
        printf("当前排队队列为空！\n");
        return;
    }
    printf("\n===== 当前排队列表 =====\n");
    printf("序号\t学号\t\t姓名\t\t项目\n");
    QNode *p = q->front;
    int i = 1;
    while (p) {
        printf("%d\t%s\t\t%s\t\t%s\n", i++, p->data.stuId, p->data.name, p->data.project);
        p = p->next;
    }
    printf("=========================\n");
}

// 销毁队列
void destroyQueue(DeQueue *q) {
    Volunteer temp;
    while (!isQueueEmpty(q)) {
        deQueueHead(q, &temp);
    }
    q->front = q->rear = NULL;
}