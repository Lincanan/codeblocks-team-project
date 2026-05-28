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
void BFS(Graph *G, int start, int end)
{
    int visited[GRAPH_MAX] = {0};
    int queue[GRAPH_MAX];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS遍历路径:");
    while(front < rear)
    {
        int cur = queue[front++];
        printf("%s -> ", G->adjList[cur].name);

        if(cur == end)
        {
            printf("查找完成\n");
            return;
        }

        ArcNode *p = G->adjList[cur].firstarc;
        while(p != NULL)
        {
            if(!visited[p->adjvex])
            {
                visited[p->adjvex] = 1;
                queue[rear++] = p->adjvex;
            }
            p = p->nextarc;
        }
    }
    printf("未找到目标节点\n");
}