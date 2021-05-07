/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #: 7
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have I provided access to my code
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: The user will specify whether they wish the data set to be (1) sorted by the count of the number of applications of the steps necessary to reach 1 or (2) sorted by the first power of two encountered during the application of the steps. The positive integer data set will follow that includes at least one value with a maximum number of 35
values.
*
***************************************************************************/
#include <stdio.h>

#define SIZE 35

void Input (int [], int *, int *);
int IsPowerOf2(int);
void Sort (int [], int [], int);
void SortList_Count (int [], int [], int);
void SortList_Power2 (int [], int [], int);
void Output(int [], int , int);

int main(void)
{
  //---Declarations---
  int option = 0; // 1 or 2, representing count/power-by-2 sorting methods respectively 
  int inputList [SIZE] = {0}; // List of positive ints entered by user
  int sortList [SIZE] = {0}; // Sorted int list derived from count/power-by-2
  int lastIndex = SIZE; // Index of the last input element in inputList & sortList

  //---Executables---
  Input(inputList, &lastIndex, &option);
  
  Sort(inputList, sortList, lastIndex);

  option == 1 ? SortList_Count(inputList, sortList, lastIndex) : SortList_Power2(inputList, sortList, lastIndex);

  Sort(sortList, inputList, lastIndex);

  Output(inputList, lastIndex, option);

  //---Exit---
  return(0);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Input
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int inputList [] // pointer to inputList [] variable in main()
*    2. int *lastIndex // pointer to lastIndex variable in main()
*    3. int *option // pointer to option option variable in main()
*
*  Function Description: Accepts input from user and returns them to main() via above pointers
*
***************************************************************************/
void Input (int inputList [], int *lastIndex, int *option)
{
  //---Declarations---
  int i; // Loop control condition

  //---Executables---
  do
  {
    printf("Enter sorting option (1) count or (2) power of two -> ");
    scanf("%d", option);

    if (*option != 1 && *option != 2)
    {
      printf("\nError! Enter option 1 or 2 only!\n\n");
    }
  } while (*option != 1 && *option != 2);

  printf("Enter up to 35 integer values -> ");
  for (i = 0; i < SIZE; i++)
  {
    scanf("%d", &inputList[i]);
      
    if (inputList[i] == -1) 
    {
      *lastIndex = i;
      i = SIZE;
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: IsPowerOf2
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int n // Positive integer
*
*  Function Description: Determine if n is a power of 2. Return 1 if it is, 0 if not
*
***************************************************************************/
int IsPowerOf2(int n)
{
  //---Executables---
  while (((n % 2) == 0) && n > 1)
  {
    n /= 2;
  }
    
  if (n != 1)
  {
    n = 0;
  }

  //---Exit---
  return(n);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Sort
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int mainList [] // List that will be properly sorted
*    2. int secondaryList [] // List that will experience exchange with same indicies in mainList
*    3. int lastIndex // index of last element in mainList and secondaryList
*
*  Function Description: Loop over elements in mainList and sort from smallest->largest. When exchange occurs, secondaryList also exchanges with same indicies
*
***************************************************************************/
void Sort (int mainList [], int secondaryList [], int lastIndex)
{
  //---Declarations---
  int numPasses; //LCV THAT CONTROLS # OF PASSES
  int lcv; //LOOP CONTROL VARIABLE FOR SORTING
  int temp; //HOLDS VALUE DURING SWAP

  //---Executables---
  for(numPasses = 1; numPasses < lastIndex; numPasses++)
  {
    for(lcv = 0; lcv < lastIndex - numPasses; lcv++)
    {
      if(mainList[lcv] > mainList[lcv + 1])
      {
        temp = mainList[lcv];
        mainList[lcv] = mainList[lcv + 1];
        mainList[lcv + 1] = temp;

        temp = secondaryList[lcv];
        secondaryList[lcv] = secondaryList[lcv + 1];
        secondaryList[lcv + 1] = temp;
      }
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: SortList_Count
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int inputList [] // List of positive ints entered by user
*    2. int sortList [] // Sorted int list derived from count/power-by-2
*    3. int lastIndex // Index of the last input element in inputList & sortList
*
*  Function Description: Calculate values to be in sortList via the count method
*
***************************************************************************/
void SortList_Count (int inputList [], int sortList [], int lastIndex)
{
  //---Declarations---
  int i; // Loop control condition
  int currVal; // Current value in inputList
  int count; // Number of iterations to get currVal to 1

  //---Executables---
  for (i = 0; i < lastIndex; i++)
  {
    currVal = inputList[i];
    count = 0;

    while (currVal != 1)
    {
      currVal = currVal % 2 == 0 ? currVal / 2 : (3 * currVal) + 1;
      count++;
    }

    sortList[i] = count;
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: SortList_Power2
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int inputList [] // List of positive ints entered by user
*    2. int sortList [] // Sorted int list derived from count/power-by-2
*    3. int lastIndex // Index of the last input element in inputList & sortList
*
*  Function Description: Calculate values to be in sortList via the power-of-2 method
*
***************************************************************************/
void SortList_Power2 (int inputList [], int sortList [], int lastIndex)
{
  //---Declarations---
  int i; // Loop control condition
  int currVal; // Current value in inputList

  //---Executables---
  for (i = 0; i < lastIndex; i++)
  {
    currVal = inputList[i];

    while (IsPowerOf2(currVal) == 0)
    {
      currVal = currVal % 2 == 0 ? currVal / 2 : (3 * currVal) + 1;
    }

    sortList[i] = currVal;
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Output
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int inputList [] // List of positive ints entered by user
*    2. int lastIndex // Index of the last input element in inputList & sortList
*    3. int option // 1 or 2, representing count/power-by-2 sorting methods respectively
*
*  Function Description: Display the sorted inputList
*
***************************************************************************/
void Output(int inputList [], int lastIndex, int option)
{
  //---Declarations---
  int i; // Loop control condition

  //---Executables---
  printf("\nSorted data by ");
  option == 1 ? printf("count:") : printf("power of two:");

  for (i = 0; i < lastIndex; i++)
  {
    printf(" %d", inputList[i]);
  }
  printf("\n"); 
}
