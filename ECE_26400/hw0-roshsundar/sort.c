#include "sort.h"


void ssort(int * arr, int size) 
{
	/* For step 3, fill this in to perform a selection sort
	   For step 4, add conditional compilation flags to perform an ascending selection sort instead */
	int c;
    int pos;
    int d;
    int t;
    
    for (c = 0; c < (size - 1); c++)
  	{
    	pos = c;

		for (d = c + 1; d < size; d++)
		{
			#ifdef ASCENDING
			if (arr[pos] > arr[d])
			#else
			if (arr[pos] < arr[d])
			#endif
			{
				pos = d;
			}
		}
    
		if (pos != c)
		{
			t = arr[c];
			arr[c] = arr[pos];
			arr[pos] = t;
		}
	}
}