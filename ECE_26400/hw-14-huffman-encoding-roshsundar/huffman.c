	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>
	#include "huffman.h"
	
	void Sorted_Frequencies_File(long *labelCount, char* output, ListNode** pq)
	{
		
		FILE* fp = fopen(output, "w");
		
		long int count = 0;
		int label_num   = 0;
	
		for (int ch = 0; ch < ASCII_SIZE; ch++) 
		{
			if (labelCount[ch] != 0 && ch >= 9) 
			{
				label_num=ch;
				count=labelCount[ch];
				EnQueue(pq, count, label_num, NULL, NULL);	
			}
		}
		Print_Node(*pq, fp);
		fclose(fp);
	}

	char* Encoded_Str_Temp(ListNode** pq, char enc_str[])
	{
		pre_order((*pq) -> ptr, enc_str);  
		sprintf(enc_str + strlen(enc_str), "0");

		return enc_str;
	}
	
	void pre_order(TreeNode* ptr, char enc_str[]){
			if(ptr != NULL)
		{
			if(ptr -> label == ASCII_SIZE) 
			{
				sprintf(enc_str + strlen(enc_str), "0");
			}
			else
			{
				sprintf(enc_str + strlen(enc_str),"1%c", ptr -> label);
			}
			pre_order(ptr -> left, enc_str);
			pre_order(ptr -> right, enc_str);
		}
	}
	
	
	void Huffman_Header_File(char enc_str[], char* output)
	{
		FILE* fp_out = fopen(output, "w");
	
		char temp_ch = '0';
		int counter = 0;
		int i = 0;

		unsigned int bits = 0;
		unsigned int extracted_bits = 0;
	
		while(temp_ch != '\0')
		{
			temp_ch = (char) enc_str[i]; i++;
			if(temp_ch == '\0' && counter != 0)
			{
				while(counter < 8)
				{
					bits = bits | (0 << (8 - counter - 1));
					counter++;
				}
				fputc(bits, fp_out);
			}
			if(temp_ch == '0')
			{
				bits = bits | (0 << (8 - counter - 1)); 
				counter++;
				if(counter == 8)
				{
					fputc(bits, fp_out);
					counter = 0;
					bits = 0;
				}	
			}
			else if(temp_ch == '1')
			{
				bits = bits | (1 << (8 - counter - 1));
				counter++;
				if(counter == 8)
				{
					fputc(bits, fp_out);
					counter = 0;
					bits = 0;
				}
				temp_ch = (char) enc_str[i]; i++;
				extracted_bits = temp_ch >> counter; // MSB
				bits = bits | extracted_bits; 
				fputc(bits, fp_out);
				bits = (temp_ch & (0xFF >> (8 - counter))) << (8 - counter); // LSB
			}	
		}
	
		fclose(fp_out);
	}
		
	void Huffman_Codes_File(ListNode** pq, char* output)
	{
		FILE* fp_out = fopen(output, "w");
	
		if((*pq) == NULL)
		{
			fclose(fp_out);
			return;
		}
		
		while((*pq) -> next != NULL)
		{
			ListNode* pop_node_1 = DeQueue(pq, &pop_node_1);
			ListNode* pop_node_2 = DeQueue(pq, &pop_node_2);
			EnQueue(pq, pop_node_1 -> ptr -> count + pop_node_2  -> ptr -> count, ASCII_SIZE, pop_node_1 -> ptr, pop_node_2 -> ptr);
			free(pop_node_1);
			free(pop_node_2);
		}
	
		char* path = malloc(sizeof(*path) * (*pq) -> ptr -> count);
	
		 Print_Sorted_Tree(fp_out, (*pq) -> ptr, path, 0);
	
		fclose(fp_out);
	
		free(path);
	}
	void Print_Sorted_Tree(FILE* fp, TreeNode* ptr, char* path, int i)
	{
		if(ptr -> label != ASCII_SIZE) 
		{
			fprintf(fp, "%c:", ptr -> label);
			path[i] = '\0';
			fprintf(fp, "%s\n", path);
			return;
		}
		else
		{
			path[i] = '0';
			Print_Sorted_Tree(fp, ptr -> left, path, i + 1);
			path[i] = '1';
			Print_Sorted_Tree(fp, ptr -> right, path, i + 1);
		}	
	}
	
	void Destroy_Node(ListNode* list)
	{
		if(list == NULL)
		{
			return;
		}
		
		ListNode* curr = list;
		while(list != NULL)
		{
			curr = list -> next;
			free(list);
			list = curr;
		}
	}
	void Destroy_Tree_Node(TreeNode* ptr)
	{
		if(ptr == NULL)
		{
			return;
		}
		Destroy_Tree_Node(ptr -> left);
		Destroy_Tree_Node(ptr -> right);
		free(ptr);
		
	}
	
	void Print_Node(const ListNode *list, FILE* output)
	{
	   while (list != NULL) 
	   { 
	      fprintf(output, "%c:%ld\n", list -> ptr -> label, list -> ptr -> count);
	      list = list->next;
	   } 
	   
	}
	void  EnQueue(ListNode** pq, long int count, int label, TreeNode* left_node, TreeNode* right_node)
	{	
	    TreeNode* new_tree_node = malloc(sizeof(*new_tree_node)); 
		new_tree_node -> count = count;
		new_tree_node -> label  = label;
		new_tree_node -> left   = left_node;
		new_tree_node -> right  = right_node;
		ListNode* new_node = malloc(sizeof(*new_node));
		new_node -> ptr = new_tree_node;
	
		if(*pq == NULL)
		{	
			new_node -> next = NULL;
			*pq = new_node;
			return;
		}
		
		ListNode* curr      = *pq;
		ListNode* prev_node = *pq;
	
		long int first = (*pq) -> ptr -> count;
		if(first - new_node ->  ptr -> count > 0)		
		{
			new_node -> next = *pq;
			*pq              = new_node;
			return;
		}
	
		bool prev = true;
		
		while(curr != NULL)
		{
			if(curr -> ptr -> count == new_node ->  ptr -> count) 
			{
				curr = *pq;
				prev = true;
				prev_node = *pq;
				
				while(new_node -> ptr -> count != curr -> ptr -> count) 
				{   
					curr = curr -> next;
					if(prev == false)
					{
						prev_node = prev_node -> next;
					}
					prev = false;
				}
				int first_label = curr -> ptr -> label;
				if(first_label == (*pq) -> ptr -> label && new_node -> ptr -> label < first_label) 
				{
					new_node -> next = curr;
					*pq = new_node;
					return;
				}
				if(first_label - new_node -> ptr -> label > 0) 
				{
					new_node -> next = curr;
					prev_node -> next = new_node;
					return;
				}
				else
				{
					curr = *pq;
					prev = true;
					prev_node = *pq;
	
					while(curr != NULL)
					{
						if(new_node -> ptr -> count == curr -> ptr -> count)
						{
							if(new_node -> ptr -> label < curr -> ptr -> label) 
							{
								new_node -> next = curr;
								prev_node -> next = new_node;
								return;
							}
							else if(new_node -> ptr -> label == curr -> ptr -> label) 
							{
								ListNode* check_end = curr;
	
								while(check_end -> next != NULL)
								{
									check_end = check_end -> next;
								}
								if(new_node -> ptr -> label == check_end -> ptr -> label) 
								{
									check_end -> next = new_node;
									new_node -> next = NULL;
									return;
								}
								while(new_node -> ptr -> label == curr -> next -> ptr -> label)  
								{							
									curr = curr -> next;
								}
								new_node -> next = curr -> next;
								curr -> next = new_node;
								return;
							}
							else
							{
								ListNode* end_label = curr;
								while(new_node -> ptr -> count == end_label -> ptr -> count)
								{
									if(end_label -> next == NULL)
									{
										break;
									}
									if(end_label -> next -> ptr -> count != new_node -> ptr -> count)
									{
										break;
									}
									end_label = end_label -> next;
								}
								if(end_label -> ptr -> label < new_node -> ptr -> label) 
								{	
									ListNode* temp = end_label -> next;
									end_label -> next = new_node;
									new_node -> next = temp;
									
									return;
								}
							}
						}
						if(prev == false)
						{
							prev_node = prev_node -> next;
						}
						curr = curr -> next;
						prev = false;
					
					}
				return;
				}
			}
			
			else if(curr -> ptr -> count - new_node -> ptr -> count > 0)
			{		
				new_node -> next  = curr;
				prev_node -> next = new_node;
				return;
			}
			else
			{	
				ListNode* end_node = *pq;
				while(end_node -> next != NULL) 
				{
					end_node = end_node -> next;
				}
				if(end_node -> ptr -> count - new_node -> ptr -> count < 0)	
				{
					new_node -> next = NULL;
					end_node -> next = new_node;
					return;
				}
			}
			if(prev == false)
			{
				prev_node = prev_node -> next;
			}
			curr = curr -> next;
			prev = false;
		}
	    return;
	}
	ListNode*  DeQueue(ListNode** pq, ListNode** popped_node)  
	{
		if(*pq == NULL)
		{
			return NULL;
		}
		ListNode* temp = *pq;
		*pq = (*pq) -> next;
		temp -> next = NULL;	
		return temp;
	
	}
