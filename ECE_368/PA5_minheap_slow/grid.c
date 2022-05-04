#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/***
    This function swaps 2 nodes in the min-heap array.

    int i1 = index1
    
***/
void Swap(int i1, int i2, GNode ** minheap)
{
    GNode * temp = minheap[i2];
    minheap[i2] = minheap[i1];
    minheap[i1] = temp;
}

void Heapify(int size, int i, GNode ** minheap)
{
    if (size != 1)
    {
        int smallest_i = i;
        int li = 2 * i + 1;
        int ri = 2 * i + 2;

        if (li < size && minheap[li] -> cost < minheap[smallest_i] -> cost)
        {
            smallest_i = li;
        }
        if (ri < size && minheap[ri] -> cost < minheap[smallest_i] -> cost)
        {
            smallest_i = ri;
        }
        if (smallest_i != i)
        {
            Swap(i, smallest_i, minheap);
            Heapify(size, smallest_i, minheap);
        }
    }
}

void Enqueue(int * size, GNode * g, GNode ** minheap)
{
    if (*size == 0)
    {
        minheap[0] = g;
        *size += 1;
    }
    else
    {
        minheap[*size] = g;
        *size += 1;
        for (int i = *size / 2 - 1; i >= 0; i--)
        {
            Heapify(*size, i, minheap);
        }
    }
}

void Dequeue(int * size, GNode ** minheap)
{
    Swap(0, *size - 1, minheap);
    *size -= 1;
    for (int i = *size / 2 - 1; i >= 0; i--)
    {
        Heapify(*size, i, minheap);
    }
}

void Dijkstra(short m, short n, GNode *** graph)
{
    // Insert bottom row into minheap
    GNode ** minheap = malloc(m * n * sizeof(GNode)); // array-based minheap
    int size = 0;
    for (int j = 0; j < n; j++)
    {
        graph[m - 1][j] -> visited = 1;
        Enqueue(&size,  graph[m - 1][j], minheap);
    }
    
    while (size != 0)
    {
        // Head of minheap: update neighbors' costs, predecessor, and visited; also update minheap
        short row = minheap[0]-> row; short col = minheap[0] -> col; short c = minheap[0] -> cost;

        if (row != 0 && graph[row - 1][col] -> visited != 1) // up
        {
            graph[row - 1][col] -> cost += c;
            graph[row - 1][col] -> visited = 1;
            graph[row - 1][col] -> pred = minheap[0];
            Enqueue(&size,  graph[row - 1][col], minheap);   
        }

        if (col != n - 1 && graph[row][col + 1] -> visited != 1) // right
        {
            graph[row][col + 1] -> cost += c;
            graph[row][col + 1] -> visited = 1;
            graph[row][col + 1] -> pred = minheap[0];
            Enqueue(&size,  graph[row][col + 1], minheap); 
        }

        if (row != m - 1 && graph[row + 1][col] -> visited != 1) // down
        {
            graph[row + 1][col] -> cost += c;
            graph[row + 1][col] -> visited = 1;
            graph[row + 1][col] -> pred = minheap[0];
            Enqueue(&size,  graph[row + 1][col], minheap); 
        }

        if (col != 0 && graph[row][col - 1] -> visited != 1) // left
        {
            graph[row][col - 1] -> cost += c;
            graph[row][col - 1] -> visited = 1;
            graph[row][col - 1] -> pred = minheap[0];
            Enqueue(&size,  graph[row][col - 1], minheap); 
        }  

        // Dequeue head of minheap
        Dequeue(&size, minheap);
    }

    free(minheap);
}