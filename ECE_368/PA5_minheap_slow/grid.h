#include <stdio.h>
#include <stdlib.h>

typedef struct GNode // Node that represents entry in grid
{
    short cost;
    short row;
    short col;
    short visited;
    struct GNode* pred;
} GNode;


void Dijkstra(short m, short n, GNode *** graph);