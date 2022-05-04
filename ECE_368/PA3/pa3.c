#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

int main(int argc, char** argv)
{
    FILE * fpin;
    FILE * fpout;

    // --- Get number of nodes from input file --- //
    fpin = fopen(argv[1], "r");
    Checkfp(fpin);
    long node_count = 0;
    char ch;
    do
    {
        ch = fgetc(fpin);
        if (ch == '\n') {node_count++;}
    } while (ch != EOF);
    fclose(fpin);

    if (node_count == 0)
    {
        return 1;
    }

    // --- Get list of all nodes from input file --- //
    fpin = fopen(argv[1], "r");
    Checkfp(fpin);
    TreeNode * node_arr[node_count];
    ReadInputFile(fpin, node_arr);
    fclose(fpin);

    // --- Create tree and print preorder traversal --- //
    TreeNode * t = CreateTree(node_arr, node_count);
    fpout = fopen(argv[2], "w");
    Checkfp(fpout);
    PrintTreePreorder(t, fpout);
    fclose(fpout);

    // --- Print tree in postorder --- //
    // Does print width,height for 'V' and 'H' nodes
    fpout = fopen(argv[3], "w");
    Checkfp(fpout);
    for (int i = 0; i < node_count; i++)
    {
        if (node_arr[i] -> type == 0)
        {
            fprintf(fpout, "%c(%d,%d)\n", node_arr[i] -> label, node_arr[i] -> width, node_arr[i] -> height);
        }
        else
        {
            fprintf(fpout, "%d(%d,%d)\n", node_arr[i] -> label, node_arr[i] -> width, node_arr[i] -> height);
        }
    }
    fclose(fpout);

    // --- Calculate the bottom left corner coordinates for every box --- //
    fpout = fopen(argv[4], "w");
    Checkfp(fpout);
    CalcBLCoord(t, fpout);
    fclose(fpout);

    // -- free --- //
    for (int i = 0; i < node_count; i++)
    {
        free(node_arr[i]);
    }

    return 0;
}