// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

#ifdef TEST_ELIMINATE
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
	
  // Note that from here on, you can access elements of the arr with
  // expressions like a[i]
	
  // initialize all elements
  for(int x=0; x<n; x++)
  {
    arr[x] = x;
  }
  
  // counting to k,
  // mark the eliminated element
  // print the index of the marked element
  // repeat until only one element is unmarked
  int e = n;
  int i = 0;
  int c = 1;

  while (e >= 1)
  {
    if (arr[i] != -1)
    {
      if (c < k)
      {
        c++;
      }
      else
      {
        printf("%d\n", arr[i]);
        c = 1;
        arr[i] = -1;
        e--;
      }
    }
        
    if (i + 1 == n)
    {
      i = 0;
    }
    else
    {
      i++;  
    }
  }

  // release the memory of the array
  free (arr);
}
#endif
