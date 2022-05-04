#include <stdio.h>
#include <stdlib.h>
#include "reroot.h"

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
    TreeNode ** node_arr = malloc(node_count * sizeof(TreeNode));
    ReadInputFile(fpin, node_arr);
    fclose(fpin);

    // --- Create tree --- //
    TreeNode * t = CreateTree(node_arr, node_count);

    // --- Create first output file --- //
    TreeNode * t1 = CopyTree(t);
    fpout = fopen(argv[2], "w");
    LR(t1, fpout);
    fclose(fpout);

    // --- Create second output file --- //
    TreeNode * t2 = CopyTree(t);
    fpout = fopen(argv[3], "w");
    RL(t2, fpout);
    fclose(fpout);

    // --- Create third output file --- //
    fpout = fopen(argv[4], "w");
    CalcTreeDims(fpout, t, t, t, t);
    fclose(fpout);

    // -- free --- //
    for (int i = 0; i < node_count; i++)
    {
        free(node_arr[i]);
    }
    free(node_arr);

    return 0;
}