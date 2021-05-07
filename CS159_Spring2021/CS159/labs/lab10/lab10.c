/************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. mcouso@purdue.edu
*  2. rmsundar@purdue.edu
*  3. jiang781@purdue.edu
*
*  Lab #: 10
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Asynchronous Online
*
*  Program Description: Given up to twenty non-negative decimal integer values as input; separate the data into even and odd numbers then sorting from smallest to largest within each classification.  Once the data is sorted as described take each value of the array modulus the data set size and use this number to represent an index and display the total of these elements. 
************************************************************************/
#include <stdio.h>

void GetInput (int [], int*);
void ArraySplit (int [], int);
int GetEvenIndex(int [], int);
void ArraySort (int [], int, int);
void BubbleSort(int [], int, int, int, int);
int CalcSum(int[], int);
void Output(int[], int, int);

#define INT_LIST_COUNT 20

int main(void)
{
  //---Declarations---
  int decimals[INT_LIST_COUNT] = {0}; // List of numbers input by user
  int size = INT_LIST_COUNT - 1; // index of the last element of decimals[] that isnt -1
  int evenIndex = 0; // index of the last even element
  int sum = 0; // Calculated sum
  
  //---Executables---
  GetInput(decimals, &size);
  ArraySplit (decimals, size);
  evenIndex = GetEvenIndex(decimals, size);
  ArraySort (decimals, evenIndex, size);
  sum = CalcSum(decimals, size);
  Output(decimals, sum, size);

  //---Exit---
  return(0);
}
/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetInput
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimals[]: array contains the input decimals
*    2. int *size: last index of the decimals array 
*
*  Function Description: Get inputs from users
*
***************************************************************************/
void GetInput (int decimals[], int *size)
{
  //---Declarations---
  int i = 0; //loop control condition
 
  //---Executables--
  printf("Enter up to 20 integer values -> ");

  for (i = 0; i < INT_LIST_COUNT; i++)
  {
    scanf("%d", &decimals[i]);
      
    if (decimals[i] == -1) 
    {
      *size = i - 1;
      i = INT_LIST_COUNT;
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: ArraySplit
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimals[]: array contains the input decimals
*    2. int *size: last index of the decimals array 
*
*  Function Description: Spilt the array into even and odd
*
***************************************************************************/
void ArraySplit (int decimals[], int size)
{
  int numPasses; //LCV THAT CONTROLS # OF PASSES
  int i; //LOOP CONTROL VARIABLE FOR SORTING
  int temp; //HOLDS VALUE DURING SWAP

  for(numPasses = 1; numPasses < size; numPasses++)
  {
    for(i = 0; i < size; i++)
    {
      if(decimals[i] % 2 == 1)
      {
        temp = decimals[i];
        decimals[i] = decimals[i + 1];
        decimals[i + 1] = temp;
      }
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetEvenIndex
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimals[]: array contains the input decimals
*    2. int size: last index of the decimals array 
*
*  Function Description: Return the last index containing even value
*
***************************************************************************/
int GetEvenIndex(int decimals[], int size)
{
  //---Declarations---
  int even_index = 0; // Stores the count of even numbers in value
  int i = 0; //loop control condition

  //---Executables---
  for(i = 0; i < size + 1; i++)
  {
    decimals[i] % 2 == 1 ? i = size : even_index++;
  }

  if (even_index != 0)
  {
    even_index -= 1;
  }

  //---Exit---
  return(even_index);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: ArraySort
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimals[]: array contains the input decimals
*    2. int size: last index of the decimals array 
*.   3. int midpoint: the last index containning even 
*
*  Function Description: Sort array from small to large, even to odd. 
*
***************************************************************************/
void ArraySort (int decimals[], int midpoint, int size)
{
  //---Executables---
  if (midpoint == size)
  {
    BubbleSort(decimals, 1, midpoint, 1, midpoint);
  }

  if (midpoint == 0)
  {
    BubbleSort(decimals, midpoint + 1, size, midpoint + 1, size);
  }
 
  if (midpoint != 0 && midpoint != size)
  {
    BubbleSort(decimals, 1, midpoint, 1, midpoint);
    BubbleSort(decimals, midpoint + 2, size, midpoint + 2, size);
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: BubbleSort
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimals[] The array input by the user
*    2. int numPass_init The initial numbers passed throught the function
*    3. int numPass_max The maximum numbers passed through the function
*    4. int  i_init The initial count for the loop
*    5. int i_max The max count for the loop
*
*  Function Description: Takes in the array input by the user, then uses the bubble sorting method to sort the array from least to greatest.
*
***************************************************************************/
void BubbleSort(int decimals [], int numPass_init, int numPass_max, int i_init, int i_max)
{
  int numPasses; //LCV THAT CONTROLS # OF PASSES
  int i; //LOOP CONTROL VARIABLE FOR SORTING
  int temp; //HOLDS VALUE DURING SWAP

  for(numPasses = numPass_init; numPasses <= numPass_max; numPasses++)
  {
    for (i = i_init; i <= i_max; i++)
    {     
      if (decimals[i - 1] > decimals[i])
      {
        temp = decimals[i - 1];
        decimals[i - 1] = decimals[i];
        decimals[i] = temp;
      }
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcSum
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimals[] The array input by the user.
*    2. int size The size of the array input by the user.
*
*  Function Description: Takes the array modulus the data set size and use that number to represent an index and then sum these.
*
***************************************************************************/
int CalcSum (int decimals[], int size)
{
  //---Declarations---
  int i; //Loop control variable
  int sum = 0; //The calculated sum

  //---Executables---
  for(i = 0; i < (size + 1); i++)
  {
    sum += decimals[decimals[i] % (size + 1)];
  }
  
  //---Exit---
  return(sum);
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
*    1. int decimals[] The array input by the user.
*    2. int sum The calculated sum.
*    3. int size The size of the array input by the user.
*
*  Function Description: Displays the above parameters
*
***************************************************************************/
void Output(int decimals[], int sum, int size)
{
  //---Declarations---
  int a; //Loop control variable

  //---Executables---
  printf("\nSorted array: ");

  for (a = 0; a <= size; a++)
  {
    printf("%d ", decimals[a]);
  }
  
  printf("\nCalculated sum: %d\n", sum);
}
