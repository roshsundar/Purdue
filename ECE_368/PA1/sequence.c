#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "shell_array.h"
#include "sequence.h"


/*  This function generates the 2p3q sequence for a shell sort (or k-sorting). It takes in the number of elements of
    array to be sorted [int length] and returns the 2p3q sequence as well as its size [int * seq_size]
*/
long *Generate_2p3q_Seq(int length, int * seq_size)
{
    *seq_size = 0;
    long * seq = malloc(0);

    if (length <= 1)
    {
        // seq_size = 0 and seq malloc'd with 0 elements
        return seq;
    }

    // Generate raw seq (2p3q list)
    // Works by iterating over the 2p3q triangle. It iterates along the 1, 3, 9 ... axis and goes left-diagonally until
    // the number is greater than length. It stops when the number on the 1, 3, 9 ... axis is greater than length
    long q_3 = 1;
    long p_2 = 0;

    while (q_3 < length)
    {
        p_2 = q_3;
        while (p_2 < length)
        {
            seq = realloc(seq, (*seq_size + 1) * sizeof(long)); // Increase size of array dynamically to accomodate new element
            if (seq == NULL) // Check for realloc failure, return NULL and set [int * seq_size] to 0
            {
                *seq_size = 0;
                return NULL;
            }
            seq[*seq_size] = p_2;
            *seq_size += 1;
            p_2 *= 2;
        }
        q_3 *= 3;
    }

    // Sort the raw seq using insertion sort
    for(int i = 1; i <= *seq_size - 1; i++)
    {
        for(int j=i; j > 0 && seq[j - 1] > seq[j]; j--)
        {
            long t = seq[j];
            seq[j] = seq[j - 1];
            seq[j - 1] = t;
        }
   }

    return seq;
}