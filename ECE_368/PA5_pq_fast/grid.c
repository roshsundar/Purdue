#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/***
    This function enqueues a PQNode into a linked-list based ascending priority queue, for Dijkstra to run on.
***/
PQNode * Enqueue(PQNode * head, PQNode * pq)
{
    if (pq -> g -> cost < head -> g -> cost)
    {
        pq -> next = head;
        head = pq;
        return head;
    }

    PQNode * pointer = head;
    PQNode * prev = pointer;
    int inserted = 0;
    while (inserted == 0)
    {
        prev = pointer;
        pointer = pointer -> next;

        if (pointer == NULL || (pq -> g -> cost < pointer -> g -> cost))
        {
            prev -> next = pq;
            pq -> next = pointer;
            inserted = 1;
        }
    }
    return head;
}

/***
    This function runs a modified Dijkstra on the graph. Rather than starting from each source node,
    it enqueues the entire bottom row (destination) and traverses to the sources.
***/
void Dijkstra(short m, short n, GNode *** graph)
{
    // Insert bottom row into ascending priority queue
    PQNode * head;
    for (int j = 0; j < n; j++)
    {
        PQNode * pq = malloc(sizeof(PQNode));
        pq -> g = graph[m - 1][j];
        pq -> g -> visited = 1;
        pq -> next = NULL;
        if (j == 0) {head = pq;}
        head = Enqueue(head, pq);
    }
    
    while (head != NULL)
    {
        // first element of priority queue: update neighbors' costs, predecessor, and visited; also update queue
        short row = head -> g -> row; short col = head -> g -> col; short c = head -> g -> cost;

        if (row != 0 && graph[row - 1][col] -> visited != 1) // up
        {
            graph[row - 1][col] -> cost += c;
            graph[row - 1][col] -> visited = 1;
            graph[row - 1][col] -> pred = head -> g;

            PQNode * pq = malloc(sizeof(PQNode));
            pq -> g = graph[row - 1][col];
            pq -> next = NULL;
            head = Enqueue(head, pq);   
        }

        if (col != n - 1 && graph[row][col + 1] -> visited != 1) // right
        {
            graph[row][col + 1] -> cost += c;
            graph[row][col + 1] -> visited = 1;
            graph[row][col + 1] -> pred = head -> g;

            PQNode * pq = malloc(sizeof(PQNode));
            pq -> g = graph[row][col + 1];
            pq -> next = NULL;
            head = Enqueue(head, pq);
        }

        if (row != m - 1 && graph[row + 1][col] -> visited != 1) // down
        {
            graph[row + 1][col] -> cost += c;
            graph[row + 1][col] -> visited = 1;
            graph[row + 1][col] -> pred = head -> g;

            PQNode * pq = malloc(sizeof(PQNode));
            pq -> g = graph[row + 1][col];
            pq -> next = NULL;            
            head = Enqueue(head, pq); 
        }

        if (col != 0 && graph[row][col - 1] -> visited != 1) // left
        {
            graph[row][col - 1] -> cost += c;
            graph[row][col - 1] -> visited = 1;
            graph[row][col - 1] -> pred = head -> g;

            PQNode * pq = malloc(sizeof(PQNode));
            pq -> g = graph[row][col - 1];
            pq -> next = NULL;
            head = Enqueue(head, pq);
        }  

        // Dequeue first element of priority queue
        PQNode * tmp = head;
        head = head -> next;
        free(tmp);
    }
}