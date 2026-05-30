#include "queue.h"

// 初始化队列
void InitQueue(DeQueue *q) {
    q->front = 0;
    q->rear = 0;
}

// 判断队列是否已满
int IsFull(DeQueue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 判断队列是否为空
int IsEmpty(DeQueue *q) {
    return q->front == q->rear;
}

// 队头入队（紧急项目优先）
int EnQueueHead(DeQueue *q, Volunteer v) {
    if (IsFull(q)) {
        printf("队列已满，无法加入紧急项目！\n");
        return 0;
    }
    // 队头前一位，就是新的队头位置
    q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
    q->data[q->front] = v;
    printf("紧急项目加入队列成功！\n");
    return 1;
}

// 队尾入队（普通项目）
int EnQueueTail(DeQueue *q, Volunteer v) {
    if (IsFull(q)) {
        printf("队列已满，无法加入普通项目！\n");
        return 0;
    }
    q->data[q->rear] = v;
    q->rear = (q->rear + 1) % MAX_SIZE;
    printf("普通项目加入队列成功！\n");
    return 1;
}

// 队头出队（签退）
int DeQueueHead(DeQueue *q, Volunteer *v) {
    if (IsEmpty(q)) {
        printf("队列为空，无法签退！\n");
        return 0;
    }
    *v = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    printf("已完成项目成功签退！\n");
    return 1;
}

// 遍历展示队列所有排队人员
void ShowQueue(DeQueue *q)
{
    if(IsEmpty(q)){
        printf("队列无人排队！\n");
        return;}
    printf("===== 排队列表 =====\n");
    int i = q->front;
    int cnt = 1;
    while(i != q->rear)
    {
        printf("%d学号：%s 姓名：%s 项目：%s时长: %d 星级: %d\n",
               cnt++, q->data[i].stuId, q->data[i].name, q->data[i].project, q->data[i].hour, q->data[i].star);
        i = (i+1) % MAX_SIZE;
    }
}

// 销毁队列（满足课程“销毁”要求，数组实现仅重置）
void DestroyQueue(DeQueue *q) 
{
    q->front = 0;
    q->rear = 0;
    printf("队列已清空销毁\n");
}