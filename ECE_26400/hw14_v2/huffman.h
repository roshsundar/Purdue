#ifndef HUFFMAN_H
#define HUFFMAN_H	 

#define ASCII_SIZE 256
#define ENC_STR_MAX 1024

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

ListNode * createSortedList(long * asciiCount);
void printSortedList(ListNode * head);

int countNodes(ListNode * head);
ListNode * createHuffmanTree(ListNode * head);
void printTreeHelper(TreeNode * t, int offset);
void printTree(TreeNode * t);

void printHuffmanCodes(TreeNode * t, char path[], int step);

void createEncodedStringHelper(TreeNode * t, char enc_str[]);
void createEncodedString(TreeNode * t, char * enc_str);

void char2bits(char c, unsigned char bits[8]);
void createBinaryString(char * enc_str, unsigned char * bin, int * s);
void printHeader(char * enc_str, char * fname);

void freeTree(TreeNode * t);
void freeList(ListNode * head, bool ishuff);

#endif