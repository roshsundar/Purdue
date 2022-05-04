#include <stdio.h>
#include <stdlib.h>

typedef struct PQNode // Linked-list node for dijkstra priority queue
{
    struct GNode* g;
    struct PQNode* next;
} PQNode;


typedef struct GNode // Node that represents entry in grid
{
    short cost;
    short row;
    short col;
    short visited;
    struct GNode* pred;
} GNode;

PQNode * Enqueue(PQNode * head, PQNode * pq);
void Dijkstra(short m, short n, GNode *** graph);