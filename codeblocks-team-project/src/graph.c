#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "graph.h"

// 初始化图
void InitGraph(Graph *G) {
    G->vexNum = 0;
    G->arcNum = 0;
    for(int i = 0; i < GRAPH_MAX; i++)
        G->adjList[i].firstarc = NULL;
}

// 添加顶点
void AddVex(Graph *G, char name[], int *idx)
{
    my_strcpy(G->adjList[G->vexNum].name, name);
    *idx = G->vexNum;
    G->vexNum++;
}

// 添加无向边
void AddArc(Graph *G, int v1, int v2)
{
    ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));
    p1->adjvex = v2;
    p1->nextarc = G->adjList[v1].firstarc;
    G->adjList[v1].firstarc = p1;

    ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
    p2->adjvex = v1;
    p2->nextarc = G->adjList[v2].firstarc;
    G->adjList[v2].firstarc = p2;

    G->arcNum++;
}

// BFS广度优先遍历，查询路径
void BFS(Graph *G, int start, int end) {
    int visited[GRAPH_MAX] = {0};       // 访问标记
    int queue[GRAPH_MAX];               // 遍历队列
    int path[GRAPH_MAX];                // 路径回溯数组
    int front = 0, rear = 0;
    int found = 0;

    // 初始化路径数组
    for (int i = 0; i < GRAPH_MAX; i++) {
        path[i] = -1;
    }

    // 起点入队
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int cur = queue[front++];

        // 找到终点，回溯并打印路径
        if (cur == end) {
            found = 1;
            printf("导航路径：");
            int temp = end;
            while (temp != -1) {
                printf("%s", G->adjList[temp].name);
                if (path[temp] != -1) printf(" -> ");
                temp = path[temp];
            }
            printf("\n");
            break;
        }

        // 遍历当前节点的所有邻接点
        ArcNode *p = G->adjList[cur].firstarc;
        while (p != NULL) {
            if (!visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                path[p->adjvex] = cur;  // 记录前驱节点
                queue[rear++] = p->adjvex;
            }
            p = p->nextarc;
        }
    }

    if (!found) {
        printf("两点之间无可达路径！\n");
    }
}

void DestroyGraph(Graph *G) {
    for (int i = 0; i < G->vexNum; i++) {
        ArcNode *p = G->adjList[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
        G->adjList[i].firstarc = NULL;
    }
    G->vexNum = 0;
    G->arcNum = 0;
}

