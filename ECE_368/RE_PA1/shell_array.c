#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "shell_array.h"
#include "sequence.h"

/*  This function loads a long array from a binary file */
long *Array_Load_From_File(char *filename, int *size)
{
    long * arr;

    FILE * fp = fopen(filename, "rb");
    if (fp == NULL) // fopen failure check
    {
        *size = 0;
        return NULL;
    }

    // Get size of the array
    fseek(fp, 0L, SEEK_END);
    long fsize = ftell(fp);
    if (fsize == 0) // Empty file check
    {
        arr = malloc(0);
        *size = 0;
        fclose(fp);
        return arr;
    }
    fseek(fp, 0, SEEK_SET);
    *size = fsize/sizeof(long);

    // Allocate arr memory
    arr = malloc(fsize);
    if (arr == NULL) // malloc failure check
    {
        *size = 0;
        fclose(fp);
        return NULL;
    }

    // Read long numbers from file to arr
    fread(arr, sizeof(long), *size, fp);

    fclose(fp);
    return arr;
}

/* This function saves a long array to a binary file */
int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE * fp = fopen(filename, "wb");

    fwrite(array, sizeof(long), size, fp);

    fclose(fp);

    return size;
}

/* This function performs the shell sort algorithm on a given array */
void Array_Shellsort(long *array, int size, long *n_comp)
{
    long cmp = 0;
    // Get the 2p3q sequence
    int k_sorting_size;
    long * k_sorting = Generate_2p3q_Seq(size, &k_sorting_size);

    // Run shell sort. Works by dividing array into subarrays of k size, sorting them, and merging them,
    // repeating the process until array is fully sorted
    for (int k_ind = k_sorting_size - 1; k_ind >= 0; k_ind--)
    {
        long k = k_sorting[k_ind];
        for (int j = k; j < size; j++)
        {
            long temp_r = array[j];

            int i = j;

            while (i >= k && array[i - k] > temp_r)
            {
                array[i] = array[i - k];
                i = i - k;
                cmp++;
            }
            array[i] = temp_r;
        }
    }

    *n_comp = cmp;

    free(k_sorting);
}