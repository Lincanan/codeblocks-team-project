#include "../include/stack.h"
#include <stdio.h>
#include <string.h>

// 初始化栈
void InitStack(Stack *s) {
    s->top = -1;
}

// 压栈
int StackPush(Stack *s, StackElem e) {
    if (s->top >= STACK_MAX - 1) {
        printf("栈已满，无法记录操作！\n");
        return 0;
    }
    s->data[++s->top] = e;
    return 1;
}

// 出栈
int StackPop(Stack *s, StackElem *e) {
    if (StackIsEmpty(s)) {
        printf("栈为空，无可撤销操作！\n");
        return 0;
    }
    *e = s->data[s->top--];
    return 1;
}

// 判断栈是否为空
int StackIsEmpty(Stack *s) {
    return s->top == -1;
}

// 记录操作前状态（压栈）
void RecordOperation(Stack *s, Volunteer v, OpType op) {
    StackElem e;
    strcpy(e.stuId, v.stuId);
    e.oldHour = v.hour;
    e.oldStar = v.star;
    e.opType = op;
    StackPush(s, e);
}

// 撤销上一次操作（回退）
int UndoOperation(Stack *s, SqList *L) {
    StackElem e;
    if (!StackPop(s, &e)) {
        return 0;
    }

    // 查找该志愿者在顺序表中的位置
    int index = LocateElem(L, e.stuId);
    if (index == -1) {
        printf("未找到该志愿者记录，无法回退！\n");
        return 0;
    }

    // 根据操作类型执行回退
    switch (e.opType) {
        case OP_ENROLL:
            // 报名撤销：删除该记录
            ListDelete(L, e.stuId);
            printf("报名撤销成功！已删除学号 %s 的记录\n", e.stuId);
            break;

        case OP_SIGN_IN:
            // 签到回退：恢复原服务时长
            L->data[index].hour = e.oldHour;
            printf("签到记录回退成功！学号 %s 的服务时长恢复为 %d 小时\n", e.stuId, e.oldHour);
            break;

        case OP_STAR_RESET:
            // 星级重置回退：恢复原星级
            L->data[index].star = e.oldStar;
            printf("星级重置回退成功！学号 %s 的星级恢复为 %d 星\n", e.stuId, e.oldStar);
            break;
    }
    return 1;
}

// 栈操作菜单
void stackMenu(Stack *s, SqList *L) {
    int choice;
    while (1) {
        printf("\n----------------------------------------\n");
        printf("==== 3. 操作回退菜单 ====\n");
        printf("1. 撤销上一次操作\n");
        printf("2. 查看可撤销操作记录数\n");
        printf("0. 返回主菜单\n");
        printf("请输入选择：");
        if(scanf("%d", &choice)!=1){
            printf("输入无效，请输入数字! \n");
            while(getchar() != '\n');
            continue;
        };

        switch (choice) {
            case 1:
                if (UndoOperation(s, L)) {
                    printf("操作回退完成！\n");
                }
                break;
            case 2:
                printf("当前可撤销操作数：%d\n", s->top + 1);
                break;
            case 0:
                if(choice==0){
                    printf("退出操作回退菜单\n");
                    break;
                }
            default:
                printf("选项无效，请重新选择！\n");
                break;
        }
        system("pause");
    }
}
void DestroyStack(Stack *s){
    s->top = -1;
}