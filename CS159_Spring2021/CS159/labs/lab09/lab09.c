/************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. mcouso@purdue.edu
*  2. rmsundar@purdue.edu
*  3. jiang781@purdue.edu
*
*  Lab #: 09
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any otherunauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Asynchronous Online
*
*  Program Description: Given twenty non-negative decimal integer values as input convert all odd numbers into binary and even numbers into octal.
*
************************************************************************/
#include <stdio.h>
#include <math.h>

#define INT_LIST_COUNT 20

void Input (int []);
int getOctalValue(int);
int getBinaryValue(int);
void Output(int []);

int main(void) 
{
  //---Declarations---
  int integers[INT_LIST_COUNT] = {0}; //Store the user inputs into an array 
  
  //---Executables---
  Input (integers);
  Output (integers);

  //---Exit---
  return(0);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:Input
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimal[]: access the integer [] in main 
*
*  Function Description:
*
***************************************************************************/
void Input (int decimal[])
{
  //---Declarations--- 
  int i = 0; //loop control condition 
  
  //---Executables---
  printf("Enter 20 integer values -> ");

  for (i = 0; i < INT_LIST_COUNT; i++)
  {
    scanf("%d", &decimal[i]);
  }
}
/***************************************************************************
*
*  Function Information
*
*  Name of Function:getOctalValue
*
*  Function Return Type: int 
*
*  Parameters (list data type, name, and comment one per line):
*    1.int value: the input decimal 
*
*  Function Description: Convert the input decimal into equivalnet octal value
*
***************************************************************************/
int getOctalValue(int value)
{
  //---Declarations---
  int octal_Value = 0; //octal (base 8) equivalent to the parameter 
  int quotient; //the remaining value of parameter divided by 8
  int count = 0; //counts the number of the iterations
  
  //---Executables--- 
  if (value < 8)
  {
    octal_Value = value;
  }
  else
  {
    while (value != 0)
    {
      quotient = value % 8;
      value = value / 8;
      octal_Value = quotient * (pow(10, count)) + octal_Value;
      count = count + 1;
    }
  }

  //---Exit---
  return (octal_Value);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: getBinaryValue
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int value: integer value
*
*  Function Description: Convert the integer value into a binary equivalent
*
***************************************************************************/
int getBinaryValue(int value)
{
  //---Declarations---
  int binary_Value = 0; //binary (base 2) equivalent to the parameter 
  int quotient; //the remaining value of parameter divided by 8
  int count = 0; //counts the number of the iterations
  
  //---Executables--- 
  
  while (value != 0)
  {
    quotient = value % 2;
    value = value / 2;
    binary_Value = quotient * (pow(10, count)) + binary_Value;
    count = count + 1;
  }

  //---Exit---
  return (binary_Value);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Ouput
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int decimal [] The array for the values input by the user.
*
*  Function Description: Print the required ouput statement 
*
***************************************************************************/
void Output(int decimal[])
{
  //---Declarations---
  int i; //loop control statement 
  int count = 0; //counts the number of iterations 

  //---Executables---
  printf("\nBinary values: ");
  for (i = 0; i < INT_LIST_COUNT; i++)
  {
    if (decimal[i] % 2 == 1)
    {
      printf("%d ", getBinaryValue(decimal[i]));
      count += 1;
    }
  }

  if (count == 0)
  {
    printf("None");
  }
  
  printf("\nOctal values: ");
  count = 0;
  for (i = 0; i < INT_LIST_COUNT; i++)
  {
    if (decimal[i] % 2 == 0)
    {
      printf("%d ", getOctalValue(decimal[i]));
      count++;
    }
  }

  if (count == 0)
  {
    printf("None");
  }
  printf("\n");
}
