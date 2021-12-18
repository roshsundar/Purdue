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


void pre_order(); 
void Print_Node();
void Print_Sorted_Tree();
void binary(char**, char); 
void EnQueue();
ListNode * DeQueue();
void Sorted_Frequencies_File();
void Huffman_Codes_File();
char* Encoded_Str_Temp();
void Huffman_Header_File();
void Destroy_Tree_Node();
void Destroy_Node();

#endif
