#ifndef GRAPH_H
#define GRAPH_H
#include "public.h"

#define GRAPH_MAX 50

// 边节点
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

// 顶点节点
typedef struct VexNode
{
    char name[MAX_NAME];
    ArcNode *firstarc;
} VexNode;

// 邻接表图结构
typedef struct
{
    VexNode adjList[GRAPH_MAX];
    int vexNum, arcNum;
} Graph;

// 函数声明
void InitGraph(Graph *G);
void AddVex(Graph *G, char name[], int *idx);
void AddArc(Graph *G, int v1, int v2);
void BFS(Graph *G, int start, int end);

#endif