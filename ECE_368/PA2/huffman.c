#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "huffman.h"

/*** 
    This function decodes a topology (preorder traversal of coding tree) from an encoded file.

    char * outfile == the string corresponding to the file the decoded topology will be output to.
    unsigned char bytes[] == the bytes from the input file storing the encoded topology.
    long numTopologyBytes == count of bytes[].
    long * top_count == count of decoded topology string that will be determined in this function.

    returns the decoded topology string.
***/
char * DecodeTreeTopology(char * outfile, unsigned char bytes[],  long numTopologyBytes, long * top_count)
{
    char * topology = malloc(sizeof(char) * 10000);
    long t_count = 0;
    unsigned char buff[8]; // temporary buffer to store bits for proper characters for leaf nodes
    long b_count = 7;

    int getting_char = 0;

    // --- Create the decoded topology string --- //
    for(int b = 0; b < numTopologyBytes; b++)
    {
        unsigned char byte = bytes[b];

        for (int i = 0; i < 8; i++)
        {
            unsigned char bit = (byte >> i) & 1; // Gets the bits of a given byte one-at-a-time in reverse order

            if (b_count == -1) // buffer is full and a character must by synthesized from bits to add to topology
            {
                int buff_byte = 0;
                for (int j = 0; j < 8; j++) // loop extracts individual bits in reverse order from the byte (necessary since encoded input given backwards beforehand)
                {
                    buff_byte |= (buff[j] == '1') << (7 - j);
                }

                b_count = 7;
                getting_char = 0;
                topology[t_count] = buff_byte;
                t_count++;
            }
            else if (getting_char == 1 && bit == 0)
            {
                buff[b_count] = '0';
                b_count--;
            }
            else if (getting_char == 1 && bit == 1)
            {
                buff[b_count] = '1';
                b_count--;
            }

            if (bit == 0 && getting_char == 0 && b != (numTopologyBytes - 1)) // add a branch node to topology // b != (numTopologyBytes - 1) ignores padding 0s on last byte
            {
                topology[t_count] = '0';
                t_count++;
            }
            else if (bit == 1 && getting_char == 0) // found leaf node. set getting_char = 1 so next 8 bits are synthezised into character
            {
                topology[t_count] = '1';
                t_count++;
                getting_char = 1;
            }
        }
    }

    // --- Output the decoded topology string to a file and return it --- //
    topology[t_count] = '\0';
    FILE * fp_out = fopen(outfile, "wb");
    Checkfp(fp_out);
    fwrite(topology, sizeof(topology[0]) * t_count, 1, fp_out);
    fclose(fp_out);

    *top_count = t_count;
    return topology;
}

/***
    This function creates a coding tree based on a (preorder) topology string.
    It uses an array-based stack with the following general rules:
    1. For each char from topology:
    2. if 0 push to stack
    3. if 1, attach to top of stack (preference given to left before right)
    4. if after adding one, top has left & right children, pop from stack and attatch to prev tree in stack (preference given to left before right). 
    5. Continue process in 4. until the new stack top no longer has both a left & right child.

    char topology[] = preorder-traversel-based topology string.
    long top_count = length of topology string

    returns head of tree
***/
TreeNode * CreateCodingTree(char topology[], long top_count)
{
    long top_index = 0;

    TreeNode * stack[top_count];
    long stack_top = -1;
    
    while (top_index < top_count) // ensures every char in topology is covered
    {
        unsigned char val = topology[top_index];
        top_index++;

        TreeNode * t = malloc(sizeof(TreeNode));
        t -> left = NULL;
        t -> right = NULL;
        
        if (val == '0')
        {
            t -> label = 9999;
            // push onto stack
            stack_top++;
            stack[stack_top] = t;
        }
        else
        {
            val = topology[top_index];
            top_index++;
            t -> label = val;

            // insert leaf node into top
            if (stack[stack_top] -> left == NULL)
            {
                stack[stack_top] -> left = t;
            }
            else
            {
                stack[stack_top] -> right = t;
            }

            int merge = 1;
            while (merge == 1 && stack_top > 0) // the stack_top > 0 prevents inserting when the final coding tree has been created in stack[0]
            {
                if ((stack[stack_top] -> left != NULL) && (stack[stack_top] -> right != NULL)) // if top has both left & right children
                {
                    // insert tree at top into previous tree in stack, decrement stack top
                    if (stack[stack_top - 1] -> left == NULL)
                    {
                        stack[stack_top - 1] -> left = stack[stack_top];
                    }
                    else
                    {
                        stack[stack_top - 1] -> right = stack[stack_top];
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

    return stack[0];
}

/***
    This function decodes a string (in bytes) that has been encoded by a coding tree. 

    It works by using a coding tree and traversing it as bits are read,
    with 0 meaning go left and 1 meaning go right, starting from the head. 
    When a leaf node is reached, the character is read  and added to a decoded string, 
    with the traversal starting from head over again. 
    This continues until all characters are read. The decoded string is then printed to a file.

    unsigned char bytes[] = byte array representing the encoded string of the original file
    long numOrigChars = number of characters in the original file
    TreeNode * head = head of the coding tree
    char * outfile = name of the file for the decoded string to be written to
***/
void Decode(unsigned char bytes[], long numOrigChars, TreeNode * head, char * outfile)
{
    char decoded[numOrigChars];
    long c = 0; // index to keep track of where we are in decoded[]

    int byte_in = 0; // index to keep track of current byte
    int bit_in = 0; // index to keep track of current bit in current byte
    while(numOrigChars != 0) // ends when all characters present in original string have been found, prevents padding 0s from being read
    {
        TreeNode * ptr = head; // reset ptr when a character has been found

        while ((ptr -> left) != NULL) // while not at a leaf node
        {
            // Read bit in reverse order
            if (bit_in > 7)
            {
                byte_in++;
                bit_in = 0;
            }
            unsigned char bit = (bytes[byte_in] >> bit_in) & 1;
            bit_in++;

            // traverse
            if (bit == 0)
            {
                ptr = ptr -> left;
            }
            else
            {
                ptr = ptr -> right;
            }
        }
        // Character has been found, add it to decoded string.
        decoded[c] = ptr -> label;
        c++;
        numOrigChars--;
    }

    // Output decoded string to file
    FILE * fp_out = fopen(outfile, "wb");
    Checkfp(fp_out);
    fwrite(decoded, sizeof(decoded[0]) * c, 1, fp_out);
    fclose(fp_out);
}

/***
    This function creates an array of counts corresponding to the 256 ascii characters present in the decoded/original file.
    It reads in the decoded file data as a btye array (as to work for both binary and char files). It loops through the decoded
    byte array and determins what ascii character it is, incrementing its count in the count array.

    long decoded_count = count of characters/bytes in the decoded file
    long asciiFreqCount[] = array that will store the ascii frequency counts. 
                            indicies correspond to 0-255 ascii chars, values stored correspond to that char's/index's count.
    char * infile = name of the decoded/original file
    char * outfile = name of file to output count array
***/
void CreateFreqArr(long decoded_count, long asciiFreqCount[],char * infile, char * outfile)
{
    // Read bytes from decoded file
    unsigned char decoded_bytes[decoded_count];
    FILE * fp_in= fopen(infile, "rb");
    Checkfp(fp_in);
    fread(decoded_bytes, 1, decoded_count, fp_in);
    fclose(fp_in);
    
    for (int i = 0; i < decoded_count; i++) // for each byte in the decoded_byte array
    {
        unsigned char c = decoded_bytes[i];
        asciiFreqCount[(int)c]++; // determine which ascii char it is and increment its count
    }

    // Output asciiFreqCount
    FILE * fp_out = fopen(outfile, "wb");
    Checkfp(fp_out);
    fwrite(asciiFreqCount, sizeof(long) * ASCII_SIZE, 1, fp_out);
    fclose(fp_out);
}

/***
    Creates the initial sorted list that is used for huffman tree creation. Taken from previous work in ECE 264.
***/
ListNode * createSortedList(long asciiCount[])
{
    unsigned char chrs[ASCII_SIZE];
    long count[ASCII_SIZE];
    int size = 0;
    for (int ch = 0; ch < ASCII_SIZE; ch++)
    {
        if (asciiCount[ch] != 0)
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

/***
    Counts the number of nodes in a list. Helper function for createHuffmanTree(). Taken from previous work in ECE 264.
***/
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

/***
    Logic helper function for createHuffmanTree(). Taken from previous work in ECE 264.
***/
bool compare(ListNode * insnode, ListNode * compnode)
{
    bool cond = (insnode -> ptr -> count < compnode -> ptr -> count);
    return cond;
}

/***
    This function creates a huffman tree from a sorted list. Taken from previous work in ECE 264.
***/
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

/***
    This preforms a pre-order traversal of a coding tree to output its topology. Taken from previous work in ECE 264.
***/
void CreateTopologyString(TreeNode * t, FILE * outfp)
{
    if (t != NULL)
    {
        if (t -> label == 9999)
        {
            unsigned char o = '0';
            fwrite(&o, sizeof(o), 1, outfp);
        }
        else
        {
            unsigned char i = '1';
            fwrite(&i, sizeof(i), 1, outfp);
            unsigned char l = t -> label;
            fwrite(&l, sizeof(l), 1, outfp);
        }

        CreateTopologyString(t -> left, outfp);
        CreateTopologyString(t -> right, outfp);
    }
}

/***
    This function calculates the total number of bits required by a tree to encode a string.

    Given the frequency/occurence of each character present in the string and the tree, it traverses the tree and counts how many
    steps it took to get to a given leaf node (this represents the number of bits to encode 1 instance of a given character). 
    It multiplies that by the count of the character to get the total number of bits to encode all instances of that character.
    It then repeats this proces for all characters in the string and sums them to get the total number of bits.

    TreeNode * t = head of the coding tree
    long step = the count of nodes traversed
    long asciiCount[] = array that stores the count of each ascii character in string. 
                        indicies correspond to 0-255 ascii chars, values stored correspond to that char's/index's count.
    long * numBits = total number of bits to encode string
***/
void CalcTreeEncBits(TreeNode * t, long step, long asciiCount[], long * numBits)
{
    if (t -> label != 9999)
    {
        *numBits += step * asciiCount[t -> label];
        return;
    }

    CalcTreeEncBits(t -> left, step + 1, asciiCount, numBits);
    CalcTreeEncBits(t -> right, step + 1, asciiCount, numBits);
}

/***
    This function takes in the coding tree present in the encoded file, and the constructed huffman tree, and outputs some metrics.

    First the number of bits to encode the original/decoded file is calculated for each tree. 
    Then the number of full bytes required is calculated for both trees. The leftover bits are also then calculated.
    These metrics are output to a file.

    TreeNode * input_tree = head of the tree from the encoded file
    TreeNode * huff_tree = head of the constructed huffman tree
    long asciiCount[] = array that stores the count of each ascii character in string. 
                        indicies correspond to 0-255 ascii chars, values stored correspond to that char's/index's count.
    char * outfile = name of output file
***/
void TreeEval(TreeNode * input_tree, TreeNode * huff_tree, long asciiCount[], char * outfile)
{
    // Calculate number of bits to encode deocded file using input tree
    long numInputTreeBits = 0;
    CalcTreeEncBits(input_tree, 0, asciiCount, &numInputTreeBits);

    // Calculate number of bits to encode deocded file using huffman tree
    long numHuffTreeBits = 0;
    CalcTreeEncBits(huff_tree, 0, asciiCount, &numHuffTreeBits);

    FILE * fp_out = fopen(outfile, "wb");
    Checkfp(fp_out);

    // Calculate and output the number of full bytes and leftover bits for input tree
    long numFullBytes = (int) (numInputTreeBits / 8);
    int numLeftoverBits = numInputTreeBits % 8;
    fwrite(&numFullBytes, sizeof(long), 1, fp_out);
    fwrite(&numLeftoverBits, sizeof(int), 1, fp_out);

    // Calculate and output the number of full bytes and leftover bits for huffman tree
    numFullBytes = (int) (numHuffTreeBits / 8);
    numLeftoverBits = numHuffTreeBits % 8;
    fwrite(&numFullBytes, sizeof(long), 1, fp_out);
    fwrite(&numLeftoverBits, sizeof(int), 1, fp_out);

    fclose(fp_out);
}

/***
    This function frees a list. Taken from previous work in ECE 264.
***/
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

/***
    This function frees a tree. Taken from previous work in ECE 264.
***/
void freeTree(TreeNode * t)
{   
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

void Checkfp(FILE * fp)
{
    if (fp == NULL)
    {
        exit(1);
    }
}