/************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. mcouso@purdue.edu
*  2. rmsundar@purdue.edu
*  3. jiang781@purdue.edu
*
*  Lab #: 07
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Asynchronous Online
*
*  Program Description: Given a non-negative decimal (base 10) integer value as input display the octal (base 8) equivalent. The program is also expectedto display the change in odd and even digits between the two numbers (base 10 and base 8 equivalent).
*
************************************************************************/
#include <stdio.h>
#include <math.h>

int getInput();
int getOctalValue(int);
int CountEvenDigits(int);
int CountOddDigits(int);
void Output(int, int);

int main(void)
{
  //---Declarations---
  int value; //The value input by the user
  int octal_Value; //The value of the decimal converted into octal
  
  //---Executables---
  value = getInput();
  octal_Value = getOctalValue(value);
  Output(value, octal_Value);
  
  //---Exit---
  return(0);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: getInput
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. N/A
*  
*
*  Function Description: The user inputs the value of the decimal user wants converted into octal form
*
***************************************************************************/
int getInput()
{
  //---Declarations---
  int value; // Stores the decimal int that user will input
  
  //---Executables---
  do
  {
    printf("Enter decimal value -> ");
    scanf("%d", &value);

    if (value < 0)
    {
      printf("\nError! The decimal value provided should be non-negative.\n\n");
    }
  }
  while (value < 0);
  
  //---Exit---
  return (value);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: getOctalValue
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int value The value of the decimal input by the user
*    
*  Function Description: Takes the decimal input by the user and converts it into an octal (base 8) form.
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
  
  while (value != 0)
  {
    quotient = value % 8;
    value = value / 8;
    octal_Value = quotient * (pow(10, count)) + octal_Value;
    count = count + 1;
  }
  //---Exit---
  return (octal_Value);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CountEvenDigits
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int value The value of the decimal input by the user
*    
*  Function Description: Counts the even digits of the decimal in decimal (base 10) and octal (base 8) form.
*
***************************************************************************/
int CountEvenDigits(int value)
{
  //---Declarations---
  int even_count = 0; // Stores the count of even numbers in value
  int rem = 0; // Stores the current digit/remainder in the value
  
  //---Executables---
  while(value > 0)
  {
    rem = value % 10;
    if(rem % 2 == 0)
    {
      even_count++;
    }
    value /= 10;
  }

  //---Exit---
  return(even_count);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CountOddDigits
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int value The value of the decimal input by the user
*
*  Function Description: Counts the odd digits of the decimal in decimal (base 10) and octal (base 8) form.
*
***************************************************************************/
int CountOddDigits(int value)
{
  //---Declarations---
  int odd_count = 0; //The number of odd digits in the number.
  int rem = 0; //The remainder after dividing the value by 10.
  
  //---Executables--- 
  while(value > 0)
  {
    rem = value % 10;
    if(rem % 2 == 1)
    {
      odd_count++;
    }
    value /= 10; 
  }

  //---Exit---
  return(odd_count);
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
*    1. int value The value of the decimal input by the user
*    2. int octal_Value The decimal input by the user, converted into octal form
*
*  Function Description: Displays the above parameters while calculating the change in even digits and odd digits between the value of the decimal and the octal form of the decimal, then displays those results.
*
***************************************************************************/
void Output(int value, int octal_Value)
{
  //---Declarations---
  int even_change = 0; //The change of even digits from the octal to the decimal.
  int odd_change = 0; //The change of odd digits from the octal to the decimal.

  //---Executables---
  printf("\nOctal equivalent: %d", octal_Value);
  
  even_change = CountEvenDigits(value) - CountEvenDigits(octal_Value);
  odd_change = CountOddDigits(value) - CountOddDigits(octal_Value);

  if(odd_change > 0)
  {
    printf("\nOdd digit change: +%d", odd_change);
  }
  else
  {
    printf("\nOdd digit change: %d", odd_change);
  }
  
  if(even_change > 0)
  {
    printf("\nEven digit change: +%d\n", even_change);
  }
  else
  {
    printf("\nEven digit change: %d\n", even_change);
  }
}
