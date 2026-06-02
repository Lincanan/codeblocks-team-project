#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mystring.h"

// 初始化图
void InitGraph(Graph *G)
{
    G->vexNum = 0;
    G->arcNum = 0;
    for (int i = 0; i < GRAPH_MAX; i++)
    {
        G->adjList[i].firstarc = NULL;
        G->adjList[i].name[0] = '\0';
    }
}

// 添加顶点，返回分配的下标
int AddVex(Graph *G, char name[])
{
    if (G->vexNum >= GRAPH_MAX) return -1;

    my_strcpy(G->adjList[G->vexNum].name, name);
    G->adjList[G->vexNum].firstarc = NULL;
    return G->vexNum++;
}

// 添加无向边（协作关系/路径）
void AddArc(Graph *G, int v1, int v2)
{
    if (v1 < 0 || v1 >= G->vexNum || v2 < 0 || v2 >= G->vexNum) return;

    // 添加v1 -> v2的边
    ArcNode *e1 = (ArcNode*)malloc(sizeof(ArcNode));
    e1->adjvex = v2;
    e1->nextarc = G->adjList[v1].firstarc;
    G->adjList[v1].firstarc = e1;

    // 添加v2 -> v1的边（双向协作/路径）
    ArcNode *e2 = (ArcNode*)malloc(sizeof(ArcNode));
    e2->adjvex = v1;
    e2->nextarc = G->adjList[v2].firstarc;
    G->adjList[v2].firstarc = e2;

    G->arcNum++;
}

// BFS求最短路径（服务地点导航）
void BFS(Graph *G, int start, int end)
{
    if (start < 0 || start >= G->vexNum || end < 0 || end >= G->vexNum)
    {
        printf("无效的顶点下标！\n");
        return;
    }
    if (start == end)
    {
        printf("起点和终点相同，无需导航！\n");
        return;
    }

    int visited[GRAPH_MAX] = {0};
    int path[GRAPH_MAX]; // 记录前驱节点
    for (int i = 0; i < GRAPH_MAX; i++) path[i] = -1;

    // 数组模拟队列
    int queue[GRAPH_MAX];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    int found = 0;
    while (front < rear)
    {
        int v = queue[front++];
        ArcNode *e = G->adjList[v].firstarc;
        while (e != NULL)
        {
            int w = e->adjvex;
            if (!visited[w])
            {
                visited[w] = 1;
                path[w] = v;
                queue[rear++] = w;
                if (w == end)
                {
                    found = 1;
                    break;
                }
            }
            e = e->nextarc;
        }
        if (found) break;
    }

    if (!found)
    {
        printf("无路径可达！\n");
        return;
    }

    // 回溯路径
    int stack[GRAPH_MAX], top = -1;
    int cur = end;
    while (cur != -1)
    {
        stack[++top] = cur;
        cur = path[cur];
    }

    printf("最短路径：");
    while (top >= 0)
    {
        printf("%s", G->adjList[stack[top--]].name);
        if (top >= 0) printf(" -> ");
    }
    printf("\n");
}

// 团队协作成员匹配
void TeamMatch(Graph *G)
{
    char name[MAX_NAME];
    printf("请输入志愿者姓名：");
    scanf("%s", name);

    // 查找志愿者下标
    int idx = -1;
    for (int i = 0; i < G->vexNum; i++)
    {
        if (my_strcmp(G->adjList[i].name, name) == 0)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        printf("未找到该志愿者！\n");
        return;
    }

    printf("与%s直接协作的成员/服务地点：\n", name);
    ArcNode *e = G->adjList[idx].firstarc;
    if (e == NULL)
    {
        printf("暂无协作关系！\n");
        return;
    }
    while (e != NULL)
    {
        printf("- %s\n", G->adjList[e->adjvex].name);
        e = e->nextarc;
    }
}