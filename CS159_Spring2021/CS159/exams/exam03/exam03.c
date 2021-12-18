/************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*
*  Lab #: exam 3
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any otherunauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Asynchronous Online
*
*  Program Description: User inputs a numbering system for odd integers, a second numbering system for even integers, and a data set consisting of up to 20 non-negative integers. Program displays the conversion of all odd numbers to the specified
numbering system followed by the even numbers to the second specified numbering system.
*
************************************************************************/
#include <stdio.h>
#include <math.h>

#define LIST_LENGTH 20

void Input(int *, int *, int []);
int CalcBaseVal(int, int);
void Print_Basename(int);
void Output(int, int, int []);

int main(void)
{
  //---Declarations---
  int odd_base = 0; // Base number system for odd values, 2-9
  int even_base = 0; // Base number system for even values, 2-9
  int integers[LIST_LENGTH] = {}; // List of integers > 0

  //---Executables---
  Input(&odd_base, &even_base, integers);
  Output(odd_base, even_base, integers);

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
*    1. int *odd_base // Pointer to odd_base variable in main()
*    2. int *even_base // Pointer to even_base variable in main()
*    3. int integers[] // Pointer to integers[] array in main()
*
*  Function Description: Collect input from user for odd_base, even_base, integers[] variables in main()
*
***************************************************************************/
void Input(int *odd_base, int *even_base, int integers[])
{
  //---Declarations---
  int i = 0; // counter

  //---Executables---
  do
  {
    printf("Enter base for odd numbers -> ");
    scanf("%d", odd_base);
    if(*odd_base < 2 || *odd_base > 9)
    {
      printf("\nError! Base must be in the range from 2 to 9.\n\n");
    }
  } while (*odd_base < 2 || *odd_base > 9);

  do
  {
    printf("Enter base for even numbers -> ");
    scanf("%d", even_base);
    if(*even_base < 2 || *even_base > 9)
    {
      printf("\nError! Base must be in the range from 2 to 9.\n\n");
    }
  } while (*even_base < 2 || *even_base > 9);

  printf("Enter up to 20 integer values -> ");
  for(i = 0; i < LIST_LENGTH; i++)
  {
    scanf("%d", &integers[i]);
    if(integers[i] == -1)
    {
      i = LIST_LENGTH;
    }
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcBaseVal
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int integer // A given non-negative integer
*    2. int base // A base system from 2-9
*
*  Function Description: Convert a given integer to a value in the base system
*
***************************************************************************/
int CalcBaseVal(int integer, int base)
{
  //---Declarations---
  int base_value = 0; // value of the integer in the base system
  int quotient; //the remaining value of parameter divided by the base
  int count = 0; //counts the number of the iterations
  
  //---Executables--- 
  
  while (integer != 0)
  {
    quotient = integer % base;
    integer = integer / base;
    base_value += quotient * (pow(10, count));
    count++;
  }

  //---Exit---
  return (base_value);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Print_Basename
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int base // The base of a numbering system, 2-9
*
*  Function Description: Print the name of the given base
*
***************************************************************************/
void Print_Basename(int base)
{
  //---Executables---
  switch(base)
  {
    case 2:
      printf("Binary");
      break;
    case 3:
      printf("Ternary");
      break;
    case 4:
      printf("Quaternary");
      break;
    case 5:
      printf("Quinary");
      break;
    case 6:
      printf("Senary");
      break;
    case 7:
      printf("Septenary");
      break;
    case 8:
      printf("Octal");
      break;
    case 9:
      printf("Nonary");
      break;
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
*    1. int *odd_base // Base number system for odd values, 2-9
*    2. int *even_base // Base number system for even values, 2-9
*    3. int integers[] // List of integers > 0
*
*  Function Description: Output the base name and converted integers, for the odd base and even base
*
***************************************************************************/
void Output(int odd_base, int even_base, int integers[])
{
  //---Declarations---
  int i; //loop control statement 
  int count = 0; //counts the number of odd/even values 

  //---Executables---
  printf("\n");
  Print_Basename(odd_base);
  printf(" values: ");
  for (i = 0; i < LIST_LENGTH; i++)
  {
    if(integers[i] == -1)
    {
      i = LIST_LENGTH;
    }
    else if (integers[i] % 2 == 1)
    {
      printf("%d ", CalcBaseVal(integers[i], odd_base));
      count += 1;
    }
  }
  if (count == 0)
  {
    printf("None");
  }
  
  printf("\n");
  Print_Basename(even_base);
  printf(" values: ");
  count = 0;
  for (i = 0; i < LIST_LENGTH; i++)
  {
    if(integers[i] == -1)
    {
      i = LIST_LENGTH;
    }
    else if (integers[i] % 2 == 0)
    {
      printf("%d ", CalcBaseVal(integers[i], even_base));
      count++;
    }
  }
  if (count == 0)
  {
    printf("None");
  }

  printf("\n");
}
