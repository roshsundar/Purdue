#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
   
        ListNode* head = NULL;
        Sorted_Frequencies_File(asciiCount, argv[2], &head); 
        free(asciiCount);

        Huffman_Codes_File(&head, argv[3]);  

     char ini_str[ENC_STR_MAX];
     char enc_str[ENC_STR_MAX];
     for(int i=0; i<ENC_STR_MAX; i++)
     {
                enc_str[i]='\0';
                ini_str[i]='\0';
     } 

        strcpy(enc_str,Encoded_Str_Temp(&head,ini_str));

        Huffman_Header_File(enc_str, argv[4]); 

        ListNode* temp = head;
        while(temp != NULL)
        {
                Destroy_Tree_Node(temp -> ptr);
                temp = temp -> next;
        }
        Destroy_Node(head);

        return EXIT_SUCCESS;
}
