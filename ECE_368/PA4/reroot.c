#include <stdio.h>
#include <stdlib.h>
#include "reroot.h"


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

            int merge = 1;
            while (merge == 1 && stack_top > 0) // the stack_top > 0 prevents inserting when the final  tree has been created in stack[0]
            {
                if ((stack[stack_top] -> left != NULL) && (stack[stack_top] -> right != NULL)) // if top has both left & right children, merge
                {
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
    This function copies a tree
***/
TreeNode * CopyTree(TreeNode * t)
{
    if (t == NULL) {return NULL;}

    TreeNode * n = malloc(sizeof(TreeNode));
    n -> label = t -> label; n -> type = t -> type;
    n -> width = t -> width; n -> height = t -> height;

    n -> left = CopyTree(t -> left);
    n -> right = CopyTree(t -> right);

    return n;
}

/***
    This function frees a tree
***/
void FreeTree(TreeNode * t)
{   
    if (t == NULL) return;
    FreeTree(t->left);
    FreeTree(t->right);
    free(t);
}

/***
    This function performs a generic re-root on a given edge.
    i.e. (sample arrangement, the function works for any left-right config)
         p (parent to edge)
        /
       a (root of edge)         ->       a
      /                                 / \
     b (child of edge)                 b   p
***/
void Reroot(TreeNode * p, TreeNode * a, TreeNode * b)
{
    if (p -> right == a)
    {
        p -> right = NULL;
    }
    else
    {
        p -> left = NULL;
    }

    TreeNode * tmp;
    if (a -> right == b)
    {
        tmp = a -> left;
        a -> left = p;
    }
    else
    {
        tmp = a -> right;
        a -> right = p;
    }

    if (p -> right == NULL)
    {
        p -> right = tmp;
    }
    else
    {
        p -> left = tmp;
    }
}

/***
    This function alternates left-right down the tree and reroots at every step, until it reaches a leaf node.

    TreeNode * t = head of tree
    FILE * outfp = output file
***/
void LR(TreeNode * t, FILE * outfp)
{
    TreeNode * p = NULL;
    TreeNode * a = t;
    TreeNode * b = t -> left;

    while(b -> type == 0)
    {
        p = a;
        a = a -> left;
        b = b -> right;
        Reroot(p, a, b);

        if (b -> type == 1) {break;}

        p = a;
        a = a -> right;
        b = b -> left;
        Reroot(p, a, b);
    }

    t = a;
    PrintTreePreorder(t, outfp);
    FreeTree(t);
}

/***
    This function alternates right-left down the tree and reroots at every step, until it reaches a leaf node.

    TreeNode * t = head of tree
    FILE * outfp = output file
***/
void RL(TreeNode * t, FILE * outfp)
{
    TreeNode * p = NULL;
    TreeNode * a = t;
    TreeNode * b = t -> right;

    while(b -> type == 0)
    {
        p = a;
        a = a -> right;
        b = b -> left;
        Reroot(p, a, b);

        if (b -> type == 1) {break;}

        p = a;
        a = a -> left;
        b = b -> right;
        Reroot(p, a, b);
    }

    t = a;
    PrintTreePreorder(t, outfp);
    FreeTree(t);
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
    This function finds the max of 2 ints.
***/
int Max(int n1, int n2)
{
    if (n1 >= n2) {return n1;}
    return n2;
}

void CalcDim(TreeNode * t)
{
    if (t -> left == NULL && t -> right == NULL) {return;}

    CalcDim(t -> left);
    CalcDim(t -> right);

    if (t -> label == 'V')
    {
        t -> width = t -> left -> width + t -> right -> width;
        t -> height = Max(t -> left -> height, t -> right -> height);
    }
    if (t -> label == 'H')
    {
        t -> height = t -> left -> height + t -> right -> height;
        t -> width = Max(t -> left -> width, t -> right -> width);
    }

    return;
}

/***
    This function is reverses a reroot operation
    i.e. sample configuration
        a                                   o
       / \                                 / \
      b   o     after deroot ->           a   .
         / \                             / \
        c   .                           b   c
    where a is head of edge, and b is child of edge. o is the original parent of a (computed in functon from a,b info).
    c is the original child of a
***/
void Deroot(TreeNode * a, TreeNode * b, TreeNode * c)
{
    TreeNode * o;
    if (a -> left == b)
    {
        o = a -> right;
        a -> right = NULL;
    }
    else
    {
        o = a -> left;
        a -> left = NULL;
    }

    if (o -> left == c)
    {
        o -> left = NULL;
    }
    else
    {
        o -> right = NULL;
    }

    if (o -> left == NULL)
    {
        o -> left = a;
    }
    else
    {
        o -> right = a;
    }

    if (a -> left == NULL)
    {
        a -> left = c;
    }
    else
    {
        a -> right = c;
    }
}

/***
    This function calculates the dimension for every edge in tree (excluding the root edges).

    FILE * outfp = pointer to output file
    TreeNode * head = head of original (un-maninpulated) tree
    TreeNode * p = parent of a, used for rerooting
    TreeNode * a = parent of b, used for rerooting
    TreeNode * b = main pointer used to traverse tree, reroot, and deroot
***/
void CalcTreeDims(FILE * outfp, TreeNode * head, TreeNode * p, TreeNode * a, TreeNode * b)
{
    if (b != NULL) // if b hasn't reached the end of a leaf node
    {
        if (b == head || b == head -> left || b == head -> right) // if b is head or edge of head
        {
            // Don't reroot on edge of head, just print instead
            if (b -> type == 0)
            {
                fprintf(outfp, "%c\n", b -> label);
            }
            else
            {
                fprintf(outfp, "%d\n", b -> label);
            }
        }
        else // b is a regular edge
        {
            Reroot(p, a, b); // reroot along a-b edge, head is a after reroot
            CalcDim(a); // calculate width,height dimensions
            // print width,height
            if (b -> type == 0)
            {
                fprintf(outfp, "%c(%d,%d)\n", b -> label, a -> width, a -> height);
            }
            else
            {
                fprintf(outfp, "%d(%d,%d)\n", b -> label, a -> width, a -> height);
            }
        }
        
        TreeNode * tmp = b -> right; // store child of b that will be used to deroot
        CalcTreeDims(outfp, head, a, b, b -> left); // b move left
        if (b -> left != NULL && b != head) // if b is not in a leaf node and not head
        {
            Deroot(b, b -> left, tmp); // deroot
        }
        
        tmp = b -> left; // store child of b that will be used to deroot
        CalcTreeDims(outfp, head, a, b, b -> right); // b move right
        if (b -> right != NULL && b != head) // if b is not in a leaf node and not head
        {
            Deroot(b, b -> right, tmp); // deroot
        }
    }
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