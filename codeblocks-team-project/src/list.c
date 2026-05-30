#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化顺序表
void InitList(SqList *L) {
    L->length = 0;
}

// 插入元素（按位置）
int ListInsert(SqList *L, int pos, Volunteer v) {
    // 先判断学号是否已存在
    if (LocateElem(L, v.stuId) != -1) {
        printf("该学号已存在，无法重复插入！\n");
        return 0;
    }
    // 判断表是否已满
    if (L->length >= MAX_SIZE) {
        printf("表已满，无法插入！\n");
        return 0;
    }
    // 判断位置是否合法
    if (pos < 0 || pos > L->length || L->length >= MAX_SIZE){
        printf("插入位置不合法！\n");
        return 0;
    }
    // 尾插：不需要移动元素
     if (pos == L->length) {
         L->data[L->length] = v;
         L->length++;
         printf("插入成功！\n");
         return 1;
     }
     // 非尾插：从后往前移动元素，腾出位置
     for (int i = L->length; i > pos; i--) {
         L->data[i] = L->data[i - 1];
     }
     // 插入新元素
     L->data[pos] = v;
     L->length++;
     printf("插入成功！\n");
     return 1;
 }

// 删除元素（按学号）
int ListDelete(SqList *L, char *stuId) {
    int i;
    for (i = 0; i < L->length; i++) {
        if (strcmp(L->data[i].stuId, stuId) == 0) {
            break;
        }
    }
    if (i == L->length) {
        printf("未找到该学号！\n");
        return 0;
    }

    // 元素前移
    for (int j = i; j < L->length - 1; j++) {
        L->data[j] = L->data[j + 1];
    }
    L->length--;
    printf("删除成功！\n");
    return 1;
}

// 修改信息（按学号）
void ListUpdate(SqList *L, char *stuId) {
    int index = LocateElem(L, stuId);
    if (index == -1) {
        printf("无此数据，修改失败！\n");
        return;
    }
    // 声明并初始化 p，指向找到的元素
    Volunteer *p = &L->data[index];

    printf("请选择要修改的字段：\n");
    printf("1. 姓名  2. 项目  3. 时长  4. 星级  5. 全部修改\n");
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');

    switch (choice) {
        case 1:
            printf("新姓名：");
            scanf("%s", p->name);
            break;
        case 2:
            printf("新项目：");
            scanf("%s", p->project);
            break;
        case 3:
            printf("新时长：");
            scanf("%d", &p->hour);
            break;
        case 4:
            printf("新星级：");
            scanf("%d", &p->star);
            break;
        case 5:
            printf("新姓名："); scanf("%s", p->name);
            printf("新项目："); scanf("%s", p->project);
            printf("新时长："); scanf("%d", &p->hour);
            printf("新星级："); scanf("%d", &p->star);
            break;
        default:
            printf("输入选项无效！\n");
            break;
    }
    printf("修改成功！\n");
}

int LocateElem(SqList *L, char *stuId) {
    for (int i = 0; i < L->length; i++) {
        // 假设你的结构体里学号字段是 stuId
        if (strcmp(L->data[i].stuId, stuId) == 0) {
            return i; // 返回下标
        }
    }
    return -1; // 没找到返回 -1
}

// 显示顺序表
void ListShow(SqList *L) {
    if (L->length == 0) {
        printf("顺序表为空！\n");
        return;
    }
    printf("\n===== 志愿者列表 =====\n");
    for (int i = 0; i < L->length; i++) {
        printf("位置%d | 学号:%s | 姓名:%s | 项目:%s | 时长:%d | 星级:%d\n",
               i + 1, L->data[i].stuId, L->data[i].name, L->data[i].project,
               L->data[i].hour, L->data[i].star);
    }
}

// 逆序顺序表
void ListReverse(SqList *L) {
    for (int i = 0; i < L->length / 2; i++) {
        Volunteer temp = L->data[i];
        L->data[i] = L->data[L->length - 1 - i];
        L->data[L->length - 1 - i] = temp;
    }
    printf("逆序成功！\n");
}

// 按时长统计
void StatByHour(SqList *L) {
    int target;
    printf("请输入要统计的时长：");
    scanf("%d", &target);
    clearBuf();

    int count = 0;
    for (int i = 0; i < L->length; i++) {
        if (L->data[i].hour == target) {
            count++;
        }
    }
    printf("时长为 %d 的志愿者共有 %d 人\n", target, count);
}

// 按星级降序排序
void SortByStar(SqList *L) {
    for (int i = 0; i < L->length - 1; i++) {
        for (int j = 0; j < L->length - i - 1; j++) {
            if (L->data[j].star < L->data[j + 1].star) {
                Volunteer temp = L->data[j];
                L->data[j] = L->data[j + 1];
                L->data[j + 1] = temp;
            }
        }
    }
    printf("按星级降序排序完成！\n");
}

// 销毁顺序表（重置长度）
void DestroyList(SqList *L) {
    L->length = 0;
    printf("顺序表已清空！\n");
}