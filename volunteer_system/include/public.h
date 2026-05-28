#ifndef PUBLIC_H
#define PUBLIC_H
 //宏定义：字符数组最大长度、数组最大容量
#define MAX_NAME 50
#define MAX_SIZE 1000
 //志愿者信息结构体（核心数据单元，全系统共用）
typedef struct {
    char stuId[20];   //学号
    char name[MAX_NAME];   //姓名
    char project[MAX_NAME];   //服务项目
    int hour;   //服务时长
    int star;   //星级（1~5）
} Volunteer;
#endif