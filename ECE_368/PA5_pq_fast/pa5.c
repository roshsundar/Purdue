#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main(int argc, char ** argv)
{
    // --- Read input file, create first output file and graph representation --- //
    FILE * fpin = fopen(argv[1], "rb");
    FILE * fpout = fopen(argv[2], "w");

    short m; // number of rows
    short n; // number of columns
    fread(&m, sizeof(short), 1, fpin);
    fread(&n, sizeof(short), 1, fpin);
    fprintf(fpout, "%hd %hd\n", m, n);

    GNode *** graph = malloc(m * sizeof(GNode));

    short c;
    for (int i = 0; i < m; i++)
    {
        graph[i] = malloc(n * sizeof(GNode));
        for (int j = 0; j < n; j++)
        {
            fread(&c, sizeof(short), 1, fpin);
            
            fprintf(fpout, "%hd", c);
            if (j != n - 1) {fprintf(fpout, " ");}
            else {fprintf(fpout, "\n");}

            GNode * g = malloc(sizeof(GNode));
            g -> cost = c;
            g -> row = i; g -> col = j;
            g -> visited = 0;
            g -> pred = NULL;
            graph[i][j] = g;
        }
    }
 
    fclose(fpin);
    fclose(fpout);

    // --- Run Dijkstra on graph --- //
    Dijkstra(m, n, graph);

    // --- Second output file --- //
    fpout = fopen(argv[3], "wb");
    fwrite(&n, 1, sizeof(short), fpout);
    GNode * shortest = graph[0][0];
    for (int j = 0; j < n; j++)
    {
        fwrite(&(graph[0][j] -> cost), 1, sizeof(int), fpout);

        if (graph[0][j] -> cost < shortest -> cost)
        {
            shortest = graph[0][j];
        }
    }
    fclose(fpout);

    // --- Third output file --- //
    fpout = fopen(argv[4], "wb");
    fwrite(&(shortest -> cost), 1, sizeof(int), fpout);

    GNode * pointer = shortest;
    int length = 0;
    while (pointer != NULL)
    {
        length++;
        pointer = pointer -> pred;
    }
    fwrite(&length, 1, sizeof(int), fpout);

    pointer = shortest;
    while (pointer != NULL)
    {
        fwrite(&(pointer -> row), 1, sizeof(short), fpout);
        fwrite(&(pointer -> col), 1, sizeof(short), fpout);
        pointer = pointer -> pred;
    }
    fclose(fpout);

    // --- free ---- //
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            free(graph[i][j]);
        }

        free(graph[i]);
    }
    free(graph);

    return 0;
}