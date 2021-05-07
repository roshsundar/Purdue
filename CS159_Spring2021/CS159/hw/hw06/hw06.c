/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #: 6
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have I provided access to my code
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description:  User inputs the value of ten years and a desired day of the week. Program displays the months within the first year that begin on the desired day of the week. For the second through the tenth year the
desired day of the week will continually be incremented.
*
***************************************************************************/
#include <stdio.h>

#define YEARS_LENGTH 10

void Input(int [], int*);
int Get_Month_Days(int, int);
int Calc_first_day_code(int);
void Output_Day(int);
void Output_Month(int);
void Determine_Months(int, int);
void Output(int, int[]);

int main(void)
{
  //---Declarations---
  int years[YEARS_LENGTH] = {}; // Years between 1700-2100
  int day_code = 0; // Code 0-6 representing Sun-Sat

  //---Executables---
  Input(years, &day_code);
  Output(day_code, years);

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
*    1. int years[] // Years between 1700-2100
*    2. int *day_code // Pointer to day_code variable in main()
*
*  Function Description: Get user input for the 10 years and the day
*
***************************************************************************/
void Input(int years[], int *day_code)
{
  //---Declarations
  int i = 0; // Counter

  //---Executables---
  printf("Enter 10 years [1700 - 2100] -> ");
  for(i = 0; i < YEARS_LENGTH; i++)
  {
    scanf("%d", &years[i]);
  }
  
  do
  {
    printf("Enter day of week number -> ");
    scanf("%d", day_code);
    printf("\n");

    if(*day_code < 0 || *day_code > 6)
    {
      printf("Error! Day of the week must be 0 to 6.\n\n");
    }

  } while(*day_code < 0 || *day_code > 6);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Get_Month_Days
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int month_code // Code 1-12 for a given month
*    2. int year // Year between 1800-2100
*
*  Function Description: Return the number of days for a given month in a given year
*
***************************************************************************/
int Get_Month_Days(int month_code, int year)
{
  //---Declarations---
  int days = 0; // Number of days in a given month

  //---Executables---
  switch(month_code)
  {
    case 1: 
      // January
      days = 31;
      break;
    
    case 2: 
      // February
      if((!(year % 4) && (year % 100)) || !(year % 400))
      {
        days = 29;
      }
      else
      {
        days = 28;
      }
      break;
    
    case 3: 
      // March
      days = 31;
      break;
    
    case 4: 
      // April
      days = 30;
      break;
    
    case 5: 
      // May
      days = 31;
      break;
    
    case 6: 
      // June
      days = 30;
      break;
    
    case 7: 
      // July
      days = 31;
      break;
    
    case 8: 
      // August
      days = 31;
      break;
    
    case 9: 
      // September
      days = 30;
      break;
    
    case 10: 
      // October
      days = 31;
      break;
    
    case 11: 
      // November
      days = 30;
      break;
    
    case 12: 
      // December
      days = 31;
      break;
  }

  //---Exit---
  return(days);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_first_day_code
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int year // Year input by user
*
*  Function Description: Calculate the code 0-6 for the first day of the week
*
***************************************************************************/
int Calc_first_day_code(int year)
{
  //---Declarations---
  int first_day_code = 0; // The code for the first day

  //---Executables---
  first_day_code = ((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400); // From pg 300 of textbook
  first_day_code = first_day_code % 7 + 1;

  if(first_day_code == 7)
  {
    first_day_code = 0;
  }
  
  //---Exit---
  return(first_day_code);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Output_Day
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int day_code // Code 0-6 for sun-sat
*
*  Function Description: Print sun-sat given a day code
*
***************************************************************************/
void Output_Day(int day_code)
{
  //---Executables---
  switch(day_code)
  {
    case 0: 
      printf("Sunday");
      break;
    
    case 1: 
      printf("Monday");
      break;
    
    case 2: 
      printf("Tuesday");
      break;
    
    case 3: 
      printf("Wednesday");
      break;
    
    case 4: 
      printf("Thursday");
      break;
    
    case 5: 
      printf("Friday");
      break;
    
    case 6: 
      printf("Saturday");
      break;
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Output_Month
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int month_code // Code 1-12 for a given month
*
*  Function Description: Print the month for a given month code
*
***************************************************************************/
void Output_Month(int month_code)
{
  //---Executables---
  switch(month_code)
  {
    case 1: 
      printf("January");
      break;

    case 2: 
      printf("February");
      break;

    case 3: 
      printf("March");
      break;

    case 4: 
      printf("April");
      break;

    case 5: 
      printf("May");
      break;

    case 6: 
      printf("June");
      break;

    case 7: 
      printf("July");
      break;

    case 8: 
      printf("August");
      break;

    case 9: 
      printf("September");
      break;

    case 10: 
      printf("October");
      break;

    case 11: 
      printf("November");
      break;

    case 12: 
      printf("December");
      break;
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Determine_Months
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int day_code // Code 0-6 representing Sun-Sat
*    2. int year // Year between 1700-2100
*
*  Function Description: Determine the months that start with the given day in the given year
*
***************************************************************************/
void Determine_Months(int day_code, int year)
{
  //---Declarations---
  int month_code = 0; // Code 1-12 representing Jan-Dec
  int day = 0; // Counter representing day in the month
  int day_code_ticker = -1; // Counter code 0-6 representing Sun-Sat for given day

  //---Executables---
  day_code_ticker = Calc_first_day_code(year);
  
  for(month_code = 1; month_code <= 12; month_code++)
  {
    if(day_code_ticker == day_code)
    {
      printf(" ");
      Output_Month(month_code);
    }

    for(day = 1; day <= Get_Month_Days(month_code, year); day++)
    {
      day_code_ticker++;
      if(day_code_ticker > 6)
      {
        day_code_ticker = 0;
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
*    1. int day_code // Code 0-6 representing Sun-Sat
*    2. int years[] // Years between 1700-2100
*
*  Function Description: Output the relevant day and months for each year
*
***************************************************************************/
void Output(int day_code, int years[])
{
  //---Declarations---
  int i = 0; // Counter

  //---Executables---
  printf("Desired day of the week: ");
  Output_Day(day_code);

  for(i = 0; i < YEARS_LENGTH; i++)
  {
    if(day_code > 6)
    {
      day_code = 0;
    }

    printf("\nMonths in %d starting on ", years[i]);
    Output_Day(day_code);
    printf(":");

    Determine_Months(day_code, years[i]);
    
    day_code++;
  }
  printf("\n");
}
