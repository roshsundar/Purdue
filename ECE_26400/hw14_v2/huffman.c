#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "huffman.h"

ListNode * createSortedList(long * asciiCount)
{
    char chrs[ASCII_SIZE];
    long count[ASCII_SIZE];
    int size = 0;
    for (int ch = 0; ch < ASCII_SIZE; ch++)
    {
        if (asciiCount[ch] != 0 && ch >= 9)
        {
            chrs[size] = ch;
            count[size] = asciiCount[ch];
            size++;
        }
    }

    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
            if (count[j] > count[j+1])
            {
                long temp1 = count[j];
                count[j] = count[j+1];
                count[j+1] = temp1;

                long temp2 = chrs[j];
                chrs[j] = chrs[j+1];
                chrs[j+1] = temp2;
            }
        }
    }

    ListNode * head = NULL;
    ListNode * pointer = head;
    for(int i = 0; i < size; i++)
    {
        TreeNode * t = malloc(sizeof(TreeNode));
        t -> label = chrs[i];
        t -> count = count[i];
        t -> left = NULL;
        t -> right = NULL;

        ListNode * l = malloc(sizeof(ListNode));
        l -> ptr = t;
        l -> next = NULL;

        if (head == NULL)
        {
            head = l;
            pointer = l;
        }
        else
        {
            pointer -> next = l;
            pointer = l;
        }
    }

    return head;
}

void printSortedList(ListNode * head)
{
    ListNode * pointer = head;
    while (pointer != NULL)
    {
        printf("%c:%ld\n", pointer -> ptr -> label, pointer -> ptr -> count);
        pointer = pointer -> next;
    }
}

int countNodes(ListNode * head)
{
    ListNode * pointer = head;
    int count = 0;
    while (pointer != NULL)
    {
        count++;
        pointer = pointer -> next;
    }
    return count;
}

bool compare(ListNode * insnode, ListNode * compnode)
{
    bool cond = (insnode -> ptr -> count < compnode -> ptr -> count);
    return cond;
}

ListNode * createHuffmanTree(ListNode * head)
{
    ListNode * p = head;
    while (countNodes(head) > 1)
    {
        ListNode * left = p;
        ListNode * right = p -> next;

        TreeNode * t = malloc(sizeof(TreeNode));
        t -> label = 9999;
        t -> count =  left -> ptr -> count + right -> ptr -> count;
        t -> left = malloc(sizeof(TreeNode));
        *(t -> left) = *(left -> ptr);
        t -> right = malloc(sizeof(TreeNode));
        *(t -> right) = *(right -> ptr);

        ListNode * l = malloc(sizeof(ListNode));
        l -> ptr = t;
        l -> next = NULL;

        p = p -> next -> next;
        
        if (p == NULL)
        {
            return l;
        }

        bool inserted = false;
        ListNode * pointer = p;
        ListNode * prev = p;
        while (pointer != NULL)
        {
            if (compare(l, pointer) == true)
            {
                prev -> next = l;
                l -> next = pointer;
                inserted = true;
                break;
            }
            prev = pointer;
            pointer = pointer -> next;
        }

        if (inserted == false)
        {
            prev -> next = l;
        }
    }

    return p;
}

void printTreeHelper(TreeNode * t, int offset) 
{
	if (t == NULL) return;
	
	for (int i = 0; i < offset; i++)
    {
		printf("  ");
	}
    if (t -> label != 9999)
    {
	    printf("%c,%ld\n", t -> label, t -> count);
    }
    else
    {
        printf("%d,%ld\n", t -> label, t -> count);
    }
	printTreeHelper(t->left, offset + 1);
	printTreeHelper(t->right, offset + 1);
}

void printTree(TreeNode * t)
{
	printTreeHelper(t, 0);
}

void printHuffmanCodes(TreeNode * t, char path[], int step)
{
    if (t -> label != 9999)
    {
        path[step] = '\0';
        printf("%c:%s\n", t -> label, path);
        return;
    }

    path[step] = '0';
    printHuffmanCodes(t -> left, path, step + 1);
    path[step] = '1';
    printHuffmanCodes(t -> right, path, step + 1);
}

void createEncodedStringHelper(TreeNode * t, char enc_str[])
{
    if (t != NULL)
    {
        if (t -> label == 9999)
        {
            sprintf(enc_str + strlen(enc_str), "0");
        }
        else
        {
            sprintf(enc_str + strlen(enc_str), "1%c", t -> label);
        }

        createEncodedStringHelper(t -> left, enc_str);
        createEncodedStringHelper(t -> right, enc_str);
    }
}

void createEncodedString(TreeNode * t, char * enc_str)
{
    createEncodedStringHelper(t, enc_str);
    sprintf(enc_str + strlen(enc_str), "0");
}

void char2bits(char c, unsigned char bits[8])
{
    for (int i = 0; i < 8; i++)
    {
        bits[i] = (c >> (7 - i)) & 1;
    }
}

void createBinaryString(char * enc_str, unsigned char * bin, int * s)
{
    int step = 0;
    
    for (int i = 0; i < strlen(enc_str); i++)
    {
        if (enc_str[i] == '0')
        {
            bin[step] = 0;
            step++;
        }
        else if (enc_str[i] == '1')
        {
            bin[step] = 1;
            step++;

            i++;
            unsigned char chbin[8];
            char2bits(enc_str[i], chbin);
            for (int j = 0; j < 8; j++)
            {
                bin[step] = chbin[j];
                step++;
            }
        }
    }

    if (step % 8 != 0)
    {
        int padnum = 8 - step % 8;
        for (int i = 0; i < padnum; i++)
        {
            bin[step] = 0;
            step++;
        }
    }
    
    *s = step;
}

void printHeader(char * enc_str, char * fname)
{
    int step = 0;
    unsigned char bin[1000000];
    for (int i = 0; i < 1000000; i++) {bin[i] = '\0';}
    createBinaryString(enc_str, bin, &step);

    FILE * fp = fopen(fname, "wb");

    int c = 0;
    for (int i = 0; i < (step / 8); i++)
    {
        unsigned char temp = '\0';
        for (int j = 0; j < 8; j++)
        {
            temp += (1 << (7 - j)) * bin[c];
            c++;
        }
        fputc(temp, fp);
    }

    fclose(fp);
}

void freeList(ListNode * head, bool ishuff)
{
    ListNode * pointer = head;
    while (pointer != NULL)
    {
        if (ishuff == true)
        {
            freeTree(pointer -> ptr);
        }
        else
        {
            free(pointer -> ptr);
        }
        ListNode * freeptr = pointer;
        pointer = pointer -> next;
        free(freeptr);
    }
}


void freeTree(TreeNode * t)
{   
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}