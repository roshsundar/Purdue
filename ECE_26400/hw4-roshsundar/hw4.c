// ***
// *** You MUST modify this file.
// ***

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef TEST_COUNTINT
int countInt(char * filename)
{
  // count the number of integers in the file
  // Please notice that if a file contains
  // 124 378 -56
  // There are three integers: 124, 378, -56
  // DO NOT count individual character '1', '2', '4' ...
  //
  // If fopen fails, return -1

  // remember to fclose if fopen succeeds

  int count = 0;
  int dump;

  FILE * fp = fopen(filename, "r");
  if (fp == NULL)
  {
    return -1;
  }

  while(fscanf(fp, "%d\n", &dump) == 1)
  {
    count++;
  }

  fclose(fp);
  return count;
}
#endif

#ifdef TEST_READINT
bool readInt(char* filename, int * intArr, int size)
{
  // if fopen fails, return false
  // read integers from the file.
  // 
  //
  // if the number of integers is different from size (too
  // few or too many) return false
  // 
  // if everything is fine, fclose and return true

  int count = 0;

  FILE * fp = fopen(filename, "r");
  if (fp == NULL)
  {
    return false;
  }

  while(fscanf(fp, "%d\n", &intArr[count]) == 1)
  {
    count++;
  }

  if (count != size)
  {
    return false;
  }

  fclose(fp);
  return true;
}
#endif

#ifdef TEST_COMPAREINT
int compareInt(const void *p1, const void *p2)
{
  // needed by qsort
  //
  // return an integer less than, equal to, or greater than zero if
  // the first argument is considered to be respectively less than,
  // equal to, or greater than the second.

  return (*(int*)p1  - *(int*)p2);
}
#endif

#ifdef TEST_WRITEINT
bool writeInt(char* filename, int * intArr, int size)
{
  // if fopen fails, return false
  // write integers to the file.
  // one integer per line
  // 
  // fclose and return true

  FILE * fp = fopen(filename, "w");
  if (fp == NULL)
  {
    return false;
  }

  for (int i = 0; i < size; i++)
  {
    fprintf(fp, "%d\n", intArr[i]);
  }

  fclose(fp);
  return true;
}
#endif

