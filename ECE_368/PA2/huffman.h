#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ASCII_SIZE 256

typedef struct TreeNode {
	int label;
	long int count;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct ListNode {
   struct TreeNode *ptr;
   struct ListNode *next;
} ListNode;


char * DecodeTreeTopology(char * outfile, unsigned char bytes[],  long numTopologyBytes, long * top_count);

TreeNode * CreateCodingTree(char topology[], long top_count);
void Decode(unsigned char bytes[], long numOrigChars, TreeNode * head, char * outfile);

void CreateFreqArr(long decoded_count, long asciiFreqCount[],char * infile, char * outfile);

ListNode * createSortedList(long asciiCount[]);
int countNodes(ListNode * head);
bool compare(ListNode * insnode, ListNode * compnode);
ListNode * createHuffmanTree(ListNode * head);
void CreateTopologyString(TreeNode * t, FILE * outfp);

void CalcTreeEncBits(TreeNode * t, long step, long asciiCount[], long * numBits);
void TreeEval(TreeNode * input_tree, TreeNode * huff_tree, long asciiCount[], char * outfile);

void freeTree(TreeNode * t);
void freeList(ListNode * head, bool ishuff);
void Checkfp(FILE * fp);