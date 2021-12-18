/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #: 4
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have I provided access to my code
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs year, day of the week number (0 [Sunday] through 6 [Saturday]), and occurrence numbe. Program determines the corresponding date.
*
***************************************************************************/

#include <stdio.h>

#define JAN_DAYS 31
#define MARCH_DAYS 31
#define APRIL_DAYS 30
#define MAY_DAYS 31
#define JUNE_DAYS 30
#define JULY_DAYS 31
#define AUG_DAYS 31
#define SEPT_DAYS 30
#define OCT_DAYS 31
#define NOV_DAYS 30
#define DEC_DAYS 31

void Input(int*, int*, int*);
int Calc_first_occ_date(int, int);
int Calc_feb_days(int);
int Calc_total_days(int, int);
void Output(int, int, int, int, int);

int main(void) 
{
  //---Declarations---
  int year = 0; // Year between 1800-2100
  int day_code = 0; // The code 0-6 repesenting Sunday-Saturday
  int occurance = 0; // The amount of times the day occurs

  int first_occ_date = 0; // The date of the first occurance of the day
  int feb_days = 0; // The amount of days in February depending on leap year
  int total_days = 0; // Total amount of days spanned by the occurance

  //---Executables---
  Input(&year, &day_code, &occurance);
  first_occ_date = Calc_first_occ_date(year, day_code);
  feb_days = Calc_feb_days(year);
  total_days = Calc_total_days(first_occ_date, occurance);
  Output(year, occurance, feb_days, total_days, day_code);
  
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
*    1. int *year // Is a pointer to year variable in main()
*    2. int *day_code // Is a pointer to day_code variable in main()
*    3. int *occurance // Is a pointer to occurance variable in main()
*
*  Function Description: Gathers user input for year, day_code, occurance in main()
*
***************************************************************************/
void Input(int *year, int *day_code, int *occurance)
{
  //---Executables---
  printf("Enter year number -> ");
  scanf("%d", year);

  printf("Enter day of week number -> ");
  scanf("%d", day_code);

  printf("Enter occurrence number -> ");
  scanf("%d", occurance);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_first_occ_date
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int year // Year input by user
*    2. int day_code // Code of the day input by user
*
*  Function Description: Calculate the date of the first occurence of user-input day
*
***************************************************************************/
int Calc_first_occ_date(int year, int day_code)
{
  //---Declarations---
  int first_occ_date = 0; // The date of the first occurance of the day
  int first_day_code = 0; // The code for the first day

  //---Executables---
  first_day_code = ((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400); // From pg 300 of textbook
  first_day_code = first_day_code % 7 + 1;
  first_occ_date = (7 - first_day_code + day_code) % 7 + 1;

  //---Exit---
  return(first_occ_date);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_feb_days
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int year // Year input by user
*
*  Function Description: Calculate number of days in Februrary depending on leap year
*
***************************************************************************/
int Calc_feb_days(int year)
{
  //---Declarations---
  int feb_days = 0; // The amount of days in February depending on leap year

  //---Executables---
  if((!(year % 4) && (year % 100)) || !(year % 400))
  {
    feb_days = 29;
  }
  else
  {
    feb_days = 28;
  }

  //---Exit---
  return(feb_days);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_total_days
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int first_occ_date // The date of the first occurance of the day
*    2. int occurance // The amount of times the day occurs
*
*  Function Description: Calcuate total amount of days spanned by the occurance
*
***************************************************************************/
int Calc_total_days(int first_occ_date, int occurance)
{
  //---Declarations---
  int total_days = 0; // Total amount of days spanned by the occurance

  //---Executables---
  total_days = first_occ_date + ((occurance - 1) * 7);

  //---Exit---
  return(total_days);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function:
*
*  Function Return Type:
*
*  Parameters (list data type, name, and comment one per line):
*    1. int year // Year input by user
*    2. int occurance // The amount of times the day occurs
*    3. int feb_days // The amount of days in February depending on leap year
*    4. int total_days // Total amount of days spanned by the occurance
*    5. int day_code // The code 0-6 repesenting Sunday-Saturday
*
*  Function Description: Output the occurance, year, and date
*
***************************************************************************/
void Output(int year, int occurance, int feb_days, int total_days, int day_code)
{
  //---Declarations---
  int flag = 1; // Used to prevent further unnecessary printing once date is reached

  //---Executables---
  switch(day_code)
  {
    case 0:
      printf("\nDesired occurrence #%d of Sunday ", occurance);
      break;
    case 1:
      printf("\nDesired occurrence #%d of Monday ", occurance);
      break;
    case 2:
      printf("\nDesired occurrence #%d of Tuesday ", occurance);
      break;
    case 3:
      printf("\nDesired occurrence #%d of Wednesday ", occurance);
      break;
    case 4:
      printf("\nDesired occurrence #%d of Thursday ", occurance);
      break;
    case 5:
      printf("\nDesired occurrence #%d of Friday ", occurance);
      break;
    case 6:
      printf("\nDesired occurrence #%d of Saturday ", occurance);
      break;
  }

  if(total_days <= JAN_DAYS && flag == 1)
  {
    // January
    printf("in %d: January %d\n", year, total_days);
    flag = 0;
  }

  total_days -= JAN_DAYS;
  if(total_days <= feb_days && flag == 1)
  {
    // February
    printf("in %d: February %d\n", year, total_days);
    flag = 0;
  }

  total_days -= feb_days;
  if(total_days <= MARCH_DAYS && flag == 1)
  {
    // March
    printf("in %d: March %d\n", year, total_days);
    flag = 0;
  }

  total_days -= MARCH_DAYS;
  if(total_days <= APRIL_DAYS && flag == 1)
  {
    // April
    printf("in %d: April %d\n", year, total_days);
    flag = 0;
  }

  total_days -= APRIL_DAYS;
  if(total_days <= MAY_DAYS && flag == 1)
  {
    // May
    printf("in %d: May %d\n", year, total_days);
    flag = 0;
  }

  total_days -= MAY_DAYS;
  if(total_days <= JUNE_DAYS && flag == 1)
  {
    // June
    printf("in %d: June %d\n", year, total_days);
    flag = 0;
  }
  
  total_days -= JUNE_DAYS;
  if(total_days <= JULY_DAYS && flag == 1)
  {
    // July
    printf("in %d: July %d\n", year, total_days);
    flag = 0;
  }

  total_days -= JULY_DAYS;
  if(total_days <= AUG_DAYS && flag == 1)
  {
    // August
    printf("in %d: August %d\n", year, total_days);
    flag = 0;
  }

  total_days -= AUG_DAYS;
  if(total_days <= SEPT_DAYS && flag == 1)
  {
    // September
    printf("in %d: September %d\n", year, total_days);
    flag = 0;
  }

  total_days -= SEPT_DAYS;
  if(total_days <= OCT_DAYS && flag == 1)
  {
    // October
    printf("in %d: October %d\n", year, total_days);
    flag = 0;
  }

  total_days -= OCT_DAYS;
  if(total_days <= NOV_DAYS && flag == 1)
  {
    // November
    printf("in %d: November %d\n", year, total_days);
    flag = 0;
  }

  total_days -= NOV_DAYS;
  if(total_days <= DEC_DAYS && flag == 1)
  {
    // December
    printf("in %d: December %d\n", year, total_days);
    flag = 0;
  }
}
