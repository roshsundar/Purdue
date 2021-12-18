#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

#ifndef BUILDTREE_OFF
bool checkValidParenth(Scanner s);
bool checkValidParenth(Scanner s)
{
    bool ret = true;
    int lParen = 0;
    int rParen = 0;

    Scanner * sn = &s;
    sn -> pos = 0;
    Token tok;

    if (strcmp(sn -> buf, "") == 0)
    {
        return false;
    }

    do
    {
        tok = nextToken(sn);
        if (tok.type == '!' && lParen ==0 && rParen == 0)
        {
            return false;
        }
        if (tok.type == '(')
        {
            lParen++;
        }
        if (tok.type == ')')
        {
            rParen++;
        }
    } while (tok.type != '!');

    if (lParen != rParen)
    {
        ret = false;
    }

    return ret;
}

TreeNode * buildExpressionTree(Scanner * s)
{
    if (!checkValidParenth(*s))
    {
        scannerClose(s);
        exit(1);
    }

    Token tok = nextToken(s);
    TreeNode * tree = buildTreeNode(tok);
    TreeNode * res;

    if (tok.type == '(')
    {
        while (tok.type != ')')
        {
            if (tok.type == '@')
            {
                tree = buildTreeNode(tok);
            }
            if (tok.type == '+' || tok.type == '-' || tok.type == '*' || tok.type == '/')
            {
                tree -> t = tok;
            }
            res = buildExpressionTree(s);

            if (tree -> left == NULL)
            {
                tree -> left = res;
            }
            else
            {
                tree -> right = res;
            }

            tok = nextToken(s);
        }
    }

    return tree;
}
#endif

#ifndef POSTFIX_OFF
void makePostFix(TreeNode * t, FILE * fptr)
{
    if (t)
    {
        makePostFix(t -> left, fptr);
        makePostFix(t -> right, fptr);
        if (t -> t.type == '@')
        {
            fprintf(fptr, "%f ", t -> t.value);
        }
        else
        {
            fprintf(fptr, "%c ", t -> t.type);
        }
    }
}
#endif