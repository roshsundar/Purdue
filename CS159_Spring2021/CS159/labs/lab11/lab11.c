/************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. mcouso@purdue.edu
*  2. rmsundar@purdue.edu
*  3. jiang781@purdue.edu
*
*  Lab #: 11
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Asynchronous Online
*
*  Program Description: Given a positive integer representing the size of an integer data set, accept input of that data set, and display the data sorted by odd and even with one additional requirement, an index that stores an odd value at the time of input must store an odd value after the data is sorted with the same requirement holding for even values.
*
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int InputSize();
void InputArray (int [], int);
void EvenSort(int[], int);
void OddSort(int[], int);
void Output(int[], int);

int main(void)
{
  //---Declarations---
  int *intArray; //Store the user input value in an array
  int size; //The size of the user input array
  
  //---Executables---
  size = InputSize();
  intArray = (int*) malloc(sizeof(int) * size);
  InputArray(intArray, size);
  EvenSort(intArray, size - 1);
  OddSort(intArray, size - 1);
  Output(intArray, size - 1);
  
  //---Exit---
  return(0);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: InputSize
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*
*  Function Description: Get size of array from user
*
***************************************************************************/
int InputSize()
{
  //---Declarations---
  int size; //Size of the array user wants
  
  //---Executables---
  printf("Enter data set size -> ");
  scanf("%d", &size);

  //---Exit---
  return (size);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: InputArray
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int intArray[]: array contains the input decimals
*    2. int size: size of the array
*
*  Function Description: Get inputs for the array
*
***************************************************************************/
void InputArray (int intArray[], int size)
{
  //---Declarations---
  int i; //Loop control variable
  
  //---Executables---
  printf("Enter %d integer values -> ", size);
  for(i = 0; i < size; i++)
  {
    scanf("%d", &intArray[i]);
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: EvenSort
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int mainList []: array contains the input decimals
*    2. int lastIndex: Last index of the array mainList
*
*  Function Description: Sorts the even numbers in the array from least to greatest, keeping odd numbers in indexes given by the user.
*
***************************************************************************/
void EvenSort (int mainList [], int lastIndex)
{
  //---Declarations---
  int numPasses; //LCV THAT CONTROLS # OF PASSES
  int lcv; //LOOP CONTROL VARIABLE FOR SORTING
  int temp; //HOLDS VALUE DURING SWAP
  
  int evenValIndex; //Store the index that has a even value
  int i; //Loop control variable

  //---Executables---
  for(numPasses = 1; numPasses <= lastIndex; numPasses++)
  {
    for(lcv = 0; lcv <= lastIndex - numPasses; lcv++)
    {
      temp = mainList[lcv];
      if(temp % 2 == 0)
      {
        for(i = lcv; i <= lastIndex; i++)
        {
          if(mainList[i] % 2 == 0)
          {
            evenValIndex = i;
            if(temp > mainList[i])
            {
              mainList[lcv] = mainList[i];
              mainList[i] = temp;
              temp = mainList[lcv];
            }
          }
        }
      }
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: OddSort
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int mainList []: array contains the input decimals
*    2. int lastIndex: Last index of the array mainList
*
*  Function Description: Sorts the odd numbers in the array from least to greatest, keeping odd numbers in indexes given by the user.
*
***************************************************************************/
void OddSort (int mainList [], int lastIndex)
{
  //---Declarations---
  int numPasses; //LCV THAT CONTROLS # OF PASSES
  int lcv; //LOOP CONTROL VARIABLE FOR SORTING
  int temp; //HOLDS VALUE DURING SWAP
  
  int oddValIndex; //Store the index that has a odd value
  int i; //Loop control variable

  //---Executables---
  for(numPasses = 1; numPasses <= lastIndex; numPasses++)
  {
    for(lcv = 0; lcv <= lastIndex - numPasses; lcv++)
    {
      temp = mainList[lcv];
      if(temp % 2 == 1)
      {
        for(i = lcv; i <= lastIndex; i++)
        {
          if(mainList[i] % 2 == 1)
          {
            oddValIndex = i;
            if(temp > mainList[i])
            {
              mainList[lcv] = mainList[i];
              mainList[i] = temp;
              temp = mainList[lcv];
            }
          }
        }
      }
    }
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
*    1. int decimals[]: array contains the input decimals
*    2. int size: last index of the decimals array 
*
*  Function Description: Displays the final sorted decimals array using the size (last index of array)
*
***************************************************************************/
void Output(int decimals[], int size)
{
  //---Declarations---
  int i; //Loop contol variable

  //---Executables---
  printf("\nFinal data set order: ");
  for(i = 0; i <= size; i++)
  {
    printf("%d ", decimals[i]);
  }
}
