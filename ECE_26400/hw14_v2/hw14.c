#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "huffman.h"

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* read and count the occurrences of characters */
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   // Your code should go here
   int valid = 0;
   for (int ch = 0; ch < ASCII_SIZE; ch++) {
      if (asciiCount[ch] != 0) valid++;
   }

   if(valid==0){
      free(asciiCount);
      return EXIT_FAILURE;
   }

   ListNode * sortedList = createSortedList(asciiCount);
   //printSortedList(sortedList);

   //printf("\n\n");

   ListNode * l = createHuffmanTree(sortedList);
   //printTree(l -> ptr);

   //printf("\n\n");

   //char path[ASCII_SIZE];
   //printHuffmanCodes(l -> ptr, path, 0);

   char enc_str[ENC_STR_MAX];
   for (int i = 0; i < ENC_STR_MAX; i++) {enc_str[i] = '\0';}
   createEncodedString(l -> ptr, enc_str);
   //printf("%s", enc_str);

   printHeader(enc_str, argv[4]);

   free(asciiCount);
   freeList(l, true);
   freeList(sortedList, false);
   return EXIT_SUCCESS;
}
