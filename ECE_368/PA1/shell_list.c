#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "shell_array.h"
#include "sequence.h"

Node *List_Load_From_File(char *filename)
{
    FILE * fp = fopen(filename, "rb");

    // Get size of the array
    fseek(fp, 0L, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    int size = fsize/sizeof(long);

    // Create list
    Node * head;
    Node * prev;
    for (int i = 0; i < size; i++)
    {
        Node * n = malloc(sizeof(Node));
        long val;
        fread(&val, sizeof(long), 1, fp);
        n -> value = val;
        n -> next = NULL;

        if (i == 0)
        {
            head = n;
            prev = n;
            continue;
        }

        prev -> next = n;
        prev = n;
    }

    fclose(fp);
    return head;
}

int List_Save_To_File(char *filename, Node *list)
{
    FILE * fp = fopen(filename, "wb");

    Node * pointer = list;
    int s = 0;
    while (pointer != NULL)
    {
        long val = pointer -> value;
        fwrite(&val, sizeof(long), 1, fp);
        s++;
        pointer = pointer -> next;
    }

    fclose(fp);
    return s;
}

/* TODO: ADD N_COMP & FREE*/
Node *List_Shellsort(Node *list, long *n_comp)
{
    // Get size of list
    int s = 0;
    Node * pointer = list;
    while (pointer != NULL)
    {
        s++;
        pointer = pointer -> next;
    }

    // Get the 2p3q sequence
    int k_sorting_size;
    long * k_sorting = Generate_2p3q_Seq(s, &k_sorting_size);

    // Shell sort
    Node * head = list;
    long cmp = 0;
    for (int k_ind = k_sorting_size - 1; k_ind >= 1; k_ind--)
    {
        long k = k_sorting[k_ind];

        // bubble sort for k 'sublist'. The bubble sort will end when swapped = 0, as no elements will be swapped because the 'sublist' is sorted
        int swapped = 1;
        long swaps = ((s - 1)/k) - 1; // calculate the number of remaining swaps after the first exchange
            
        while (swapped == 1)
        {
            swapped = 0;
            Node * n1_prev = NULL;
            Node * n1 = head;
            Node * n1_next = n1 -> next;
            Node * n2_prev = n1;
            Node * n2 = n1_next;
            Node * n2_next = n2 -> next;

            // --- Handle the first swap, from head to the node k apart --- //
            for (int i = 1; i < k; i++) // Move n2 related pointers to correct positions
            {
                n2_prev = n2;
                n2 = n2_next;
                n2_next = n2 -> next;
            }

            cmp++;
            if (n1 -> value > n2 -> value) // Swap if necessary
            {
                n2 -> next = n1_next;
                n2_prev -> next = n1;
                n1 -> next = n2_next;
                head = n2;
                n2 = n1;
                n1 = head;
                swapped = 1;
            }

            // --- Handle remaining swaps --- //
            for (int sw = 0; sw < swaps; sw++) // repeat swapping process for number of swaps
            {
                for (int i = 0; i < k; i++) // Move n2 related pointers to correct positions
                {
                    n1_prev = n1;
                    n1 = n1_next;
                    n1_next = n1 -> next;

                    n2_prev = n2;
                    n2 = n2_next;
                    n2_next = n2 -> next;
                }

                cmp++;
                if (n1 -> value > n2 -> value) // Swap if necessary
                {
                    n2 -> next = n1_next;
                    n2_prev -> next = n1;
                    n1 -> next = n2_next;
                    n1_prev -> next = n2;
                    Node * temp = n2;
                    n2 = n1;
                    n1 = temp;
                    swapped = 1;
                }
            }
        }

        printf("k: %ld, %ld\n", k, cmp);
    }

    // Bubble sort for k = 1
    int swapped = 1;
    while (swapped == 1)
    {
        swapped = 0;
        Node * n1_prev = NULL;
        Node * n1 = head;
        Node * n2 = n1 -> next;
        Node * n2_next = n2 -> next;

        // --- Handle the first swap, from head to the next node --- //
        cmp++;
        if (n1 -> value > n2 -> value) // Swap if necessary
        {
            n2 -> next = n1;
            n1 -> next = n2_next;
            head = n2;
            n2 = n1;
            n1 = head;
            swapped = 1;
        }

        // --- Handle remaining swaps --- //
        for (int sw = 1; sw < s - 1; sw++)
        {
            n1_prev = n1;
            n1 = n1 -> next;

            n2 = n2_next;
            n2_next = n2_next -> next;

            cmp++;
            if (n1 -> value > n2 -> value) // Swap if necessary
            {
                n1_prev -> next = n2;
                n2 -> next = n1;
                n1 -> next = n2_next;
                Node * temp = n2;
                n2 = n1;
                n1 = temp;
                swapped = 1;
            }
        }
    }
    
    free(k_sorting);
    *n_comp = cmp;
    return head;
}