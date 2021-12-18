/************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. mcouso@purdue.edu
*  2. rmsundar@purdue.edu
*  3. jiang781@purdue.edu
*
*  Lab #: 08
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Asynchronous Online
*
*  Program Description: User inputs a range of non-negative decimal (base 10) integer value. Program displays the smallest value in the range that represent the largest change in odd and even digits when comparing the decimal value to its octal (base 8) equivalent
*
************************************************************************/

#include <stdio.h>
#include <math.h>

void getInput(int*, int*);
int getOctalValue(int);
int CountEvenDigits(int);
int CountOddDigits(int);
void GetLargestOdd(int, int, int*, int*, int*);
void GetLargestEven(int, int, int*, int*, int*);
void Output(int, int, int, int, int, int);

int main(void)
{
  //---Declarations---
  int starting_value = 0; //The beginning decimal 
  int ending_Value = 0; //The ending decimal

  int odd_decimal = 0; //The decimal in the range which has the largest odd digit changes
  int odd_octal = 0; //The octal value for the decimal in the range which has the largest odd digit changes
  int odd_digit_change = 0; //The odd digit change from decimal to octal

  int even_decimal = 0; //The decimal within the range which has the largest even digit changes
  int even_octal = 0; //The octal value for the decimal within the range which has the largest even digit changes
  int even_digit_change = 0; //The even digit change from decimal to octal

  //---Executables---
  getInput(&starting_value, &ending_Value);
  GetLargestOdd(starting_value, ending_Value, &odd_decimal, &odd_octal, &odd_digit_change);
  GetLargestEven(starting_value, ending_Value, &even_decimal, &even_octal, &even_digit_change);
  Output(odd_decimal, even_decimal, odd_digit_change, even_digit_change, odd_octal, even_octal);
  
  //---Exit---
  return(0);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: getInput
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int *starting_value: points to starting_value variable in main()
*    2. int *ending_value: points to ending_value variable in main()
*
*  Function Description: Gets starting and ending decimal values from the user, and returns them to main()
*
***************************************************************************/
void getInput(int *starting_value, int *ending_value)
{
  //---Executables---
  do
  {
    printf("Enter starting decimal value -> ");
    scanf("%d", starting_value);
    
    if (*starting_value < 0)
    {
      printf("\nError! The decimal value provided should be non-negative.\n\n");
    }
  } while (*starting_value < 0);

  do
  {
    printf("Enter ending decimal value -> ");
    scanf("%d", ending_value);
    
    if (*ending_value <= *starting_value)
    {
      printf("\nError! The ending value provided should be greater than %d.\n\n", *starting_value);
    }
  } while (*ending_value <= *starting_value);
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
*  Name of Function: GetLargestOdd
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int beginning: beginning decimal
*    2. int ending: the ending decimal
*    3. int *odd_decimal: mempry address of the odd_decimal in mai()
*    4. int *odd_octal: mempry address of the odd_octal in mai()
*.   5. int *odd_digit_change: mempry address of the        * * * odd_digit_change in main()
*
*  Function Description: Finds the smallest decimal and octal value that has the largest odd digit change when going from decimal to octal equivalent.Find the decimal that has the largest odd digit changes within a range
*
********************************************** *****************************/
void GetLargestOdd(int beginning, int ending, int *odd_decimal, int *odd_octal, int *odd_digit_change) 
{
  //---Declarations---
  int index = beginning; //The beginning decimal 
  int octal; //The octal value of index
  int oddChange; //The change in odd digits from decimal to octal
  
  int tempDecimal = 0; //Temporary store the the decimal that has the largest odd digit change
  int tempOcatal = 0; //Temporatily stores the octal equivalent of the decimal that has the largest odd digit change
  int tempOddChange = 0; //Temporary store the largest odd digit changes

  //---Executables--
  while (index <= ending)
  {
    octal = getOctalValue(index);
    oddChange = CountOddDigits(index) - CountOddDigits(octal);
    
    if(fabs((double)oddChange) > fabs((double)tempOddChange))
    {
      tempDecimal = index;
      tempOcatal = octal;
      tempOddChange = oddChange;

    }
    else if (fabs((double)oddChange) == fabs((double)tempOddChange) && index < tempDecimal)
    {
      tempDecimal = index;
      tempOcatal = octal;
      tempOddChange = oddChange;
    }

    index += 1;
  }

  *odd_decimal = tempDecimal;
  *odd_octal = tempOcatal;
  *odd_digit_change = tempOddChange;
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetLargestEven
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int beginning The starting decimal value 
*    2. int ending the ending decimal value
*    3. int *even_decimal points to even_decimal in main()
*    4. int *even_octal points to even octal in main()
*    5. int *even_digit_change points to even_digit_change in main()
*
*  Function Description: Finds the smallest decimal and octal value that has the largest even digit change when going from decimal to octal equivalent.
*
***************************************************************************/
void GetLargestEven(int beginning, int ending, int *even_decimal, int *even_octal, int *even_digit_change)
{
  //---Declarations---
  int index = beginning;  //The beginning decimal
  int octal; //The octal value of index
  int evenChange;  //The even digit changes between octal value and the original decimal 
  
  int tempDecimal = 0; //Temporary store the the decimal that has the largest even digit change
  int tempOctal = 0; //Temporatily stores the octal equivalent of the decimal that has the largest even digit change
  int tempEvenChange = 0; //Temporary store the largest even digit changes

  //---Executables--
  while (index <= ending)
  {
    octal = getOctalValue(index);
    evenChange = CountEvenDigits(index) - CountEvenDigits(octal);

    if(fabs((double)evenChange) > fabs((double)tempEvenChange))
    {
      tempDecimal = index;
      tempOctal = octal;
      tempEvenChange = evenChange;
    }
    else if (fabs((double)evenChange) == fabs((double)tempEvenChange) && index < tempDecimal)
    {
      tempDecimal = index;
      tempOctal = octal;
      tempEvenChange = evenChange;
    }

    index += 1;
  }
  *even_decimal = tempDecimal;
  *even_octal = tempOctal;
  *even_digit_change = tempEvenChange;
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
*    1. int oddDecimal: The decimal in the range which has the largest odd digit changes
*    2. int evenDecimal: The decimal within the range which has the largest even digit changes
*    3. int oddChanges: The odd digit change from decimal to octalThe odd digit changes
*    4. int evenChanges: The even digit change from decimal to octalThe even digit changes
*    5. int oddOctal: The octal value for the decimal in the range which has the largest odd digit changesThe octal value of the decimal that has the largest odd digit changes 
*    6. int evenOctal: The octal value for the decimal within the range which has the largest even digit changesThe octal value of the decimal that has the largest even digit changes 
*
*  Function Description: Displays the above parameters
*
***************************************************************************/
void Output(int oddDecimal, int evenDecimal, int oddChanges, int evenChanges, int oddOctal, int evenOctal)
{
  //---Executables--
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-Change-Decimal-=-Octal-");

  printf("\nLargest odd digit change: %7d %7d %7d", oddChanges, oddDecimal, oddOctal);
  printf("\nLargest even digit change: %6d %7d %7d\n", evenChanges, evenDecimal, evenOctal);
}
