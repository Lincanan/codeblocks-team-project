#ifndef GLIST_H
#define GLIST_H

#include "public.h"

#define ATOM 0
#define LIST 1

typedef struct GLNode
{
    int tag;
    union
    {
        char data[MAX_NAME];
        struct GLNode *hp;
    }un;
    struct GLNode *tp;
}GLNode, *GList;

void CreateGList(GList *L, char *str);
void TraverseGList(GList L);

#endif