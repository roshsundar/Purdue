#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int label; // 'V', 'H', or number for box
	int type; // 0 = branch, 1 = leaf
    int width; // width of box
    int height; // height of box
	struct TreeNode* left; // left child
	struct TreeNode* right; // right child
} TreeNode;

void ReadInputFile(FILE * fpin, TreeNode ** node_arr);
TreeNode * CreateTree(TreeNode ** node_arr, long node_count);

TreeNode * CopyTree(TreeNode * t);
void FreeTree(TreeNode * t);

void Reroot(TreeNode * p, TreeNode * a, TreeNode * b);
void LR(TreeNode * t, FILE * outfp);
void RL(TreeNode * t, FILE * outfp);

int Max(int n1, int n2);
void CalcDim(TreeNode * t);
void Deroot(TreeNode * e_h, TreeNode * e_c1, TreeNode * e_c2);
void CalcTreeDims(FILE * outfp, TreeNode * head, TreeNode * p, TreeNode * a, TreeNode * b);

void PrintTreePreorder(TreeNode * t, FILE * outfp);

void Checkfp(FILE * fp);