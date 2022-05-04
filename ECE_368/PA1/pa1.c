#include <stdio.h>
#include <stdlib.h>
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

        list = List_Shellsort(list, &n_comp);

        int x = List_Save_To_File(argv[3], list);

        freeList(list);
    }

    printf("%ld\n", n_comp);
    
    return EXIT_SUCCESS;
}