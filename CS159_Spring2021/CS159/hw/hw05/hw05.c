/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #: 5
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have I provided access to my code
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs the year and occurrence number. Program determines when that week begins & ends, and displays the week which will begin on the same day of the week as January 1st of the specified year.
*
***************************************************************************/

#include <stdio.h>

void Input(int*, int*);
int Calc_first_day_code(int);
int Calc_last_day_code(int);
int Calc_total_days(int, int);
void Calc_month_date(int*, int, int*, int*);
int Get_Month_Len(int);
int Get_Month_Days(int, int);
void Output_Day(int);
void Output_Month(int);
void Calendar(int, int, int, int, int, int);
void Output(int, int, int, int, int, int, int, int);

int main(void)
{
  //---Declarations---
  int start_year = 0; // Year between 1800-2100, input by user
  int end_year = 0; // Year the week ends in
  int occurance = 0; // The week number, does not go over a year

  int first_day_code = 0; // first day of week, code 0-6 representing sun-sat
  int first_day_days = 0; // Number of days to the first day of the week
  int first_day_month = 0; // Month the first day starts in, code 1-12 for jan-dec
  int first_day_date = 0; // The date in the month the first day starts in

  int last_day_code = 0; // Last day of week, code 0-6 representing sun-sat
  int last_day_days = 0; // Number of days to the last day of the week
  int last_day_month = 0; // Month the last day starts in, code 1-12 for jan-dec
  int last_day_date = 0; // The date in the month the last day starts in

  //---Executables---
  Input(&start_year, &occurance);
  end_year = start_year;

  first_day_code = Calc_first_day_code(start_year);
  last_day_code = Calc_last_day_code(first_day_code);

  first_day_days = Calc_total_days(1, occurance);
  last_day_days = Calc_total_days(7, occurance);

  Calc_month_date(&end_year, first_day_days, &first_day_month, &first_day_date);
  Calc_month_date(&end_year, last_day_days, &last_day_month, &last_day_date);

  Output(first_day_code, last_day_code, first_day_date, last_day_date, first_day_month, last_day_month, start_year, end_year);

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
*    3. int *occurance // Is a pointer to occurance variable in main()
*
*  Function Description: Gathers user input for year, occurance in main()
*
***************************************************************************/
void Input(int *year, int *occurance)
{
  //---Executables---
  printf("Enter year number -> ");
  scanf("%d", year);

  printf("Enter occurrence number -> ");
  scanf("%d", occurance);
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
*  Name of Function: Calc_last_day_code
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int first_day_code // first day of week, code 0-6 representing sun-sat
*
*  Function Description: Calculate the code 0-6 for the last day of the week
*
***************************************************************************/
int Calc_last_day_code(int first_day_code)
{
  //---Declarations---
  int last_day_code = 0; // Last day of week, code 0-6 representing sun-sat

  //---Executables---
  last_day_code = first_day_code - 1;
  
  if(last_day_code < 0)
  {
    last_day_code = 0;
  }

  if(first_day_code == 0)
  {
    last_day_code = 6;
  }

  //---Exit---
  return(last_day_code);
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
*  Name of Function: Calc_month_date
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int *end_year // Pointer to end_year in main()
*    2. int total_days // Total amount of days to a date
*    3. int *month_code // Pointer to a month_code variable in main(), for the first day or last day
*    4. int *date // Pointer to a date variable in main(), for the first day or last day
*
*  Function Description: For a number of days, return the year, the month, and the date it exists in
*
***************************************************************************/
void Calc_month_date(int *end_year, int total_days, int *month_code, int *date)
{
  //---Declarations---
  int flag = 1; // Used to prevent further unnecessary printing once date is reached

  //---Executables---
  if(total_days <= Get_Month_Days(1, *end_year) && flag == 1)
  {
    // January
    *month_code = 1;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(1, *end_year);
  if(total_days <= Get_Month_Days(2, *end_year) && flag == 1)
  {
    // February
    *month_code = 2;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(2, *end_year);
  if(total_days <= Get_Month_Days(3, *end_year) && flag == 1)
  {
    // March
    *month_code = 3;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(3, *end_year);
  if(total_days <= Get_Month_Days(4, *end_year) && flag == 1)
  {
    // April
    *month_code = 4;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(4, *end_year);
  if(total_days <= Get_Month_Days(5, *end_year) && flag == 1)
  {
    // May
    *month_code = 5;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(5, *end_year);
  if(total_days <= Get_Month_Days(6, *end_year) && flag == 1)
  {
    // June
    *month_code = 6;
    *date = total_days;
    flag = 0;
  }
  
  total_days -= Get_Month_Days(6, *end_year);
  if(total_days <= Get_Month_Days(7, *end_year) && flag == 1)
  {
    // July
    *month_code = 7;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(7, *end_year);
  if(total_days <= Get_Month_Days(8, *end_year) && flag == 1)
  {
    // August
    *month_code = 8;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(8, *end_year);
  if(total_days <= Get_Month_Days(9, *end_year) && flag == 1)
  {
    // September
    *month_code = 9;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(9, *end_year);
  if(total_days <= Get_Month_Days(10, *end_year) && flag == 1)
  {
    // October
    *month_code = 10;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(10, *end_year);
  if(total_days <= Get_Month_Days(11, *end_year) && flag == 1)
  {
    // November
    *month_code = 11;
    *date = total_days;
    flag = 0;
  }

  total_days -= Get_Month_Days(11, *end_year);
  if(total_days <= Get_Month_Days(12, *end_year) && flag == 1)
  {
    // December
    *month_code = 12;
    *date = total_days;
    flag = 0;
  }
  else if (flag == 1)
  {
    // Jan of next year
    total_days -= 31;
    *end_year += 1;
    *month_code = 1;
    *date = total_days;
  }
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Get_Month_Len
*
*  Function Return Type: int
*
*  Parameters (list data type, name, and comment one per line):
*    1. int month_code // Code 1-12 for a given month
*
*  Function Description: Return the length of the text for a given month
*
***************************************************************************/
int Get_Month_Len(int month_code)
{
  //---Declarations---
  int len = 0; // Length of the text for a given month

  //---Executables---
  switch(month_code)
  {
    case 1: 
      // January
      len = 7;
      break;
    case 2: 
      // February
      len = 8;
      break;
    case 3: 
      // March
      len = 5;
      break;
    case 4: 
      // April
      len = 5;
      break;
    case 5: 
      // May
      len = 3;
      break;
    case 6: 
      // June
      len = 4;
      break;
    case 7: 
      // July
      len = 4;
      break;
    case 8: 
      // August
      len = 6;
      break;
    case 9: 
      // September
      len = 9;
      break;
    case 10: 
      // October
      len = 7;
      break;
    case 11: 
      // November
      len = 8;
      break;
    case 12: 
      // December
      len = 8;
      break;
  }

  //---Exit---
  return(len);
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
*  Name of Function: Output_Week
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int day_code // Code 0-6 for sun-sat
*    2. int month_code // Code 1-12 for a given month
*    3. int date // Given date in a month
*    4. int year // Year between 1800-2100
*
*  Function Description: Print the month for a given month code
*
***************************************************************************/
void Output_Week(int day_code, int month_code, int date, int year)
{
  //---Executables---
  Output_Day(day_code);
  printf(" ");
  Output_Month(month_code);
  printf(" %d, %d", date, year);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calendar
*
*  Function Return Type: void
*
*  Parameters (list data type, name, and comment one per line):
*    1. int first_day_code // first day of week, code 0-6 representing sun-sat
*    2. int last_day_code // Last day of week, code 0-6 representing sun-sat
*    3. int first_day_date // The date in the month the first day starts in
*    4. int last_day_date // The date in the month the last day starts in
*    5. int first_day_month // Month the first day starts in, code 1-12 for jan-dec
*    6. int start_year // Year between 1800-2100, input by user
*
*  Function Description: Create a calender for the full week - displaying month, first & last date
*
***************************************************************************/
void Calendar(int first_day_code, int last_day_code, int first_day_date, int last_day_date, int first_day_month, int start_year)
{
  //---Declarations---
  int prepad = 0; // Number of spaces before the month, to center it
  int pos = 0; // Current index in the caledar
  int max_pos = 0; // Maximum indexin the caledar
  int count = 0; // Current day of the month

  //---Executables---
  prepad = 14 - (1 + Get_Month_Len(first_day_month) / 2);
  printf("%*c", prepad, 32);
  Output_Month(first_day_month);
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  printf("\nSun Mon Tue Wed Thu Fri Sat\n");

  count = first_day_date;
  
  if(first_day_code == 0)
  {
    max_pos = last_day_code;
  }
  else
  {
    max_pos = last_day_code+7;
  }

  for(pos = 0; pos <= max_pos; pos++)
  {
    if(pos >= first_day_code)
    {
      if(count > Get_Month_Days(first_day_month, start_year))
      {
        count = 1;
      }
      printf(" %-2d", count);
      count++;
    }
    else
    {
      printf("   ");
    }

    if(pos == 6 && pos != max_pos)
    {
      printf("\n");
    }
    else
    {
      printf(" ");
    }
  }
  printf("\n");
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
*    1. int first_day_code // first day of week, code 0-6 representing sun-sat
*    2. int last_day_code // Last day of week, code 0-6 representing sun-sat
*    3. int first_day_date // The date in the month the first day starts in
*    4. int last_day_date // The date in the month the last day starts in
*    5. int first_day_month // Month the first day starts in, code 1-12 for jan-dec
*    6. int last_day_month // Month the last day starts in, code 1-12 for jan-dec
*    7. int start_year // Year between 1800-2100, input by user
*    8. int end_year = 0; // Year the week ends in
*
*  Function Description: Output the start and end week info, as well as calendar
*
***************************************************************************/
void Output(int first_day_code, int last_day_code, int first_day_date, int last_day_date, int first_day_month, int last_day_month, int start_year, int end_year)
{
  //---Executables---
  printf("\n");
  printf("Start of week: ");
  Output_Week(first_day_code, first_day_month, first_day_date, start_year);

  printf("\n");
  printf("End of week: ");
  Output_Week(last_day_code, last_day_month, last_day_date, end_year);

  printf("\n\n");
  Calendar(first_day_code, last_day_code, first_day_date, last_day_date, first_day_month, start_year);
}
