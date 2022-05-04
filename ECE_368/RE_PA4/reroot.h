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


void Reroot(TreeNode * p, TreeNode * a, TreeNode * b);
void Deroot(TreeNode * e_h, TreeNode * e_c1, TreeNode * e_c2);

void PrintTreePreorder(TreeNode * t, FILE * outfp);
void AltTravReroot(FILE * outfp, TreeNode * head, TreeNode * p, TreeNode * a, TreeNode * b, char dir);

int Max(int n1, int n2);
void CalcDim(TreeNode * t);
void Recalc(TreeNode * head, TreeNode * x, TreeNode * y);
void CalcTreeDims(FILE * outfp, TreeNode * head, TreeNode * p, TreeNode * a, TreeNode * b);

void Checkfp(FILE * fp);