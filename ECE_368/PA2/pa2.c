#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char** argv)
{
    // Check if command line is as expected
    if (argc != 7)
    {
        return EXIT_FAILURE;
    }

    // --- Get and categorize data from input file --- //
    FILE * fp_in = fopen(argv[1], "rb");
    Checkfp(fp_in);

    long numTotalBytes = 0;
    fread(&numTotalBytes, sizeof(long), 1, fp_in);

    long numTopologyBytes = 0;
    fread(&numTopologyBytes, sizeof(long), 1, fp_in);

    long numUnencodedBytes = 0;
    fread(&numUnencodedBytes, sizeof(long), 1, fp_in);

    long numEncodedBytes = numTotalBytes - 24 - numTopologyBytes;

    unsigned char Topologybytes[numTopologyBytes];
    fread(Topologybytes, 1, numTopologyBytes, fp_in);

    unsigned char Encodedbytes[numEncodedBytes];
    fread(Encodedbytes, 1, numEncodedBytes, fp_in);
    
    fclose(fp_in);

    // --- Begin operations --- //

    // first output
    long t_count = 0;
    char * topology = DecodeTreeTopology(argv[2], Topologybytes, numTopologyBytes, &t_count);

    // second output
    TreeNode * head = CreateCodingTree(topology, t_count);
    Decode(Encodedbytes, numUnencodedBytes, head, argv[3]);

    // third output
    long asciiFreqCount[ASCII_SIZE] = {0};
    CreateFreqArr(numUnencodedBytes, asciiFreqCount,argv[3], argv[4]);

    // fourth output
    ListNode * sortedList = createSortedList(asciiFreqCount);
    ListNode * l = createHuffmanTree(sortedList);
    FILE * fp = fopen(argv[5], "wb");
    Checkfp(fp);
    CreateTopologyString(l -> ptr, fp);
    fclose(fp);

    // fifth output
    TreeEval(head, l -> ptr, asciiFreqCount, argv[6]);

    // free & exit
    free(topology);
    freeList(l, true);
    freeList(sortedList, false);
    freeTree(head);
    return EXIT_SUCCESS;
}