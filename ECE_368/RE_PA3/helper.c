#include <stdio.h>
#include <stdlib.h>
#include "helper.h"


/***
    This function reads the input file containing node info in postorder, and creates nodes out of each line as specified in the readme. These nodes are put into an array.

    FILE * fpin = pointer to input file
    TreeNode * node_arr[] = array of treenodes
***/
void ReadInputFile(FILE * fpin, TreeNode * node_arr[])
{
    int i = 0;
    int endOfFile = 0;
    while(endOfFile == 0)
    {
        int label;
        int width;
        int height;

        int scan_res = fscanf(fpin, "%d(%d,%d)", &label, &width, &height);
        if (scan_res == EOF)
        {
            endOfFile = 1;
        }
        else if (scan_res) // leaf node
        {
            TreeNode * t = malloc(sizeof(TreeNode));
            t -> label = label; t -> type = 1;
            t -> width = width; t -> height = height;
            t -> blx = 0; t -> bly = 0;
            t -> left = NULL; t -> right = NULL;
            node_arr[i] = t;
            i++;
        }
        else // branch node
        {
            char c;
            fscanf(fpin, "%c", &c);
            TreeNode * t = malloc(sizeof(TreeNode));
            t -> label = c; t -> type = 0;
            t -> width = 0; t -> height = 0;
            t -> blx = 0; t -> bly = 0;
            t -> left = NULL; t -> right = NULL;
            node_arr[i] = t;
            i++;
        }
    }
}

/***
    This function creates the tree from the list of nodes in postorder array.

    TreeNode * node_arr[] = array of nodes
    long node_count = count of node_arr
***/
TreeNode * CreateTree(TreeNode * node_arr[], long node_count)
{
    long node_i = node_count - 1;

    TreeNode ** stack = malloc(node_count * sizeof(TreeNode));
    long stack_top = -1;
    
    while (node_i > -1)
    {
        TreeNode * t = node_arr[node_i];
        node_i--;

        if (t -> type == 0) // H or V
        {
            stack_top++;
            stack[stack_top] = t;
        }
        else
        {
            if (stack[stack_top] -> right == NULL) // prioritize right insertion first for postoder
            {
                stack[stack_top] -> right = t;
            }
            else
            {
                stack[stack_top] -> left = t;
            }

            // Update dimensions of H or V node
            if (stack[stack_top] -> label == 72) // if parent is H
            {
                if (t -> width > stack[stack_top] -> width) {stack[stack_top] -> width = t -> width;}
                stack[stack_top] -> height += t -> height;
            }
            else // parent is V
            {
                stack[stack_top] -> width += t -> width;
                if (t -> height > stack[stack_top] -> height) {stack[stack_top] -> height = t -> height;}
            }

            int merge = 1;
            while (merge == 1 && stack_top > 0) // the stack_top > 0 prevents inserting when the final  tree has been created in stack[0]
            {
                if ((stack[stack_top] -> left != NULL) && (stack[stack_top] -> right != NULL)) // if top has both left & right children, merge
                {
                    // Update dimensions of H or V node
                    if (stack[stack_top - 1] -> label == 72) // if parent is H
                    {
                        if (stack[stack_top] -> width > stack[stack_top - 1] -> width) {stack[stack_top - 1] -> width = stack[stack_top] -> width;}
                        stack[stack_top - 1] -> height += stack[stack_top] -> height;
                    }
                    else // parent is V
                    {
                        stack[stack_top - 1] -> width += stack[stack_top] -> width;
                        if (stack[stack_top] -> height > stack[stack_top - 1] -> height) {stack[stack_top - 1] -> height = stack[stack_top] -> height;}
                    }

                    // insert tree at top into previous tree in stack, decrement stack top
                    if (stack[stack_top - 1] -> right == NULL)
                    {
                        stack[stack_top - 1] -> right = stack[stack_top];
                    }
                    else
                    {
                        stack[stack_top - 1] -> left = stack[stack_top];
                    }
                    stack_top--;
                }
                else
                {
                    merge = 0;
                }
            }
        }
    }

    TreeNode * head = stack[0];
    free(stack);
    return head;
}

/***
    This function prints content of tree in preorder as specified in readme. Does NOT print the width,height of 'V' or 'H' nodes

    TreeNode * t = root of tree
    FILE * outfp = pointer to output file
***/
void PrintTreePreorder(TreeNode * t, FILE * outfp)
{
    if (t != NULL)
    {
        if (t -> type == 0)
        {
            fprintf(outfp, "%c\n", t -> label);
        }
        else
        {
            fprintf(outfp, "%d(%d,%d)\n", t -> label, t -> width, t -> height);
        }

        PrintTreePreorder(t -> left, outfp);
        PrintTreePreorder(t -> right, outfp);
    }
}

/***
    This function calculates the bottom-left coordinates of every box in the tree.

    The rules for a given node are:
         H
        / \
        A B
        B(bl) = H(BL)
        A(bl) = H(BL) + (0, height(B))

         V
        / \
        A B
        B(bl) = V(bl) + (width(A), 0)
        A(bl) = V(bl)

    TreeNode * t = pointer to current node in tree
    FILE * outfp = pointer to output file
***/
void CalcBLCoord(TreeNode * t, FILE * outfp)
{
    if (t -> type == 1) // node is box
    {
        fprintf(outfp, "%d((%d,%d)(%d,%d))\n", t -> label, t -> width, t -> height, t -> blx, t -> bly);
        return;
    }
    else if (t -> label == 72) // node is 'H'
    {
        t -> right -> blx = t -> blx; t -> right -> bly = t -> bly;
        t -> left -> blx = t -> blx; t -> left -> bly = (t -> bly) + (t -> right -> height);
    }
    else // node is 'V'
    {
        t -> right -> blx = (t -> blx) + (t -> left -> width); t -> right -> bly = t -> bly;
        t -> left -> blx = t -> blx; t -> left -> bly = t -> bly;
    }

    CalcBLCoord(t -> left, outfp);
    CalcBLCoord(t -> right, outfp);
}

/***
    Checks if a file has been opened correctly

    FILE * fp = pointer to file
***/
void Checkfp(FILE * fp)
{
    if (fp == NULL)
    {
        exit(1);
    }
}