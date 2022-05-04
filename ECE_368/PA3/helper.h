#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int label; // 'V', 'H', or number for box
	int type; // 0 = branch, 1 = leaf
    int width; // width of box
    int height; // height of box
	int blx; // x-coord of bottom-left conrner of box
	int bly; // y-coord of bottom-left conrner of box
	struct TreeNode* left; // left child
	struct TreeNode* right; // right child
} TreeNode;

void ReadInputFile(FILE * fpin, TreeNode * node_arr[]);
TreeNode * CreateTree(TreeNode * node_arr[], long node_count);
void PrintTreePreorder(TreeNode * t, FILE * outfp);
void CalcBLCoord(TreeNode * t, FILE * outfp);
void Checkfp(FILE * fp);