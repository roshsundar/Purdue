#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_list.h"
#include "shell_array.h"
#include "sequence.h"

static void freeList(Node * list);
static void freeList(Node * list)
{
    Node * nextNode = list;
    Node * toFree;

    while (nextNode != NULL)
    {
        toFree = nextNode;
        nextNode = nextNode -> next;
        free(toFree);
    }
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-l") != 0 )
    {
        return EXIT_FAILURE;
    }

    long n_comp;
    if (argv[1][1] == 'a')
    {
        long * arr;
        int size;
        arr = Array_Load_From_File(argv[2], &size);
        if (arr == NULL)
        {
            return EXIT_FAILURE;
        }

        Array_Shellsort(arr, size, &n_comp);

        Array_Save_To_File(argv[3], arr, size);

        free(arr);
    }
    else
    {
        Node * list = List_Load_From_File(argv[2]);
        if (list == NULL)
        {
            printf("0\n", n_comp);
            FILE * fp = fopen(argv[3], "wb");
            fclose(fp);
            return EXIT_SUCCESS;
        }

        list = List_Shellsort(list, &n_comp);

        int x = List_Save_To_File(argv[3], list);

        freeList(list);
    }

    printf("%ld\n", n_comp);
    
    return EXIT_SUCCESS;
}