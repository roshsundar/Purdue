
/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*  2. jiang781@purdue.edu
*  3. mcouso@purdue.edu
*
*  Lab #: 4
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs three points that will always create a triangle with a positive area.
*  Program calculates the distance between the points and the coordinate of the incenter found within the triangle created.
*
***************************************************************************/
#include <stdio.h>
#include <math.h>

void Input(int*, int*, int*, int*, int*, int*);
double CalcDist(int, int, int, int);
double CalcInCen_X(double, double, double, int, int, int);
double CalcInCen_Y(double, double, double, int, int, int);
void Output(double, double, double, double, double);

int main(void)
{
  //---Declarations---
  int x_1 = 0; // x coord of point 1
  int y_1 = 0; // y coord of point 1
  int x_2 = 0; // x coord of point 2
  int y_2 = 0; // y coord of point 2
  int x_3 = 0; // x coord of point 3
  int y_3 = 0; // y coord of point 3
  
  double d_12 = 0; // Distance from point 1 to point 2
  double d_23 = 0; // Distance from point 2 to point 3
  double d_31 = 0; // Distance from point 3 to point 1
  
  double incen_x = 0; // Incenter x coord
  double incen_y = 0; // Incenter y coord

  //---Executables---
  Input(&x_1, &y_1, &x_2, &y_2, &x_3, &y_3);
  
  d_12 = CalcDist(x_1, y_1, x_2, y_2);
  d_23 = CalcDist(x_2, y_2, x_3, y_3);
  d_31 = CalcDist(x_3, y_3, x_1, y_1);

  incen_x = CalcInCen_X(d_12, d_23, d_31, x_1, x_2, x_3);
  incen_y = CalcInCen_Y(d_12, d_23, d_31, y_1, y_2, y_3);

  Output(d_12, d_23, d_31, incen_x, incen_y);

  //--Exit---
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
*    1. int *x_1 memory address of x_1 in main()
*    2. int *y_1 memory address of y_1 in main()
*    3. int *x_2 memory address of x_2 in main()
*    4. int *y_2 memory address of y_2 in main()
*    5. int *x_3 memory address of x_3 in main()
*    6. int *y_3 memory address of y_3 in main()
*
*  Function Description: Gets user input and fills above variables
*
***************************************************************************/
void Input(int *x_1, int *y_1, int *x_2, int *y_2, int *x_3, int *y_3)
{
  //---Executables---
  printf("Enter X coordinate #1 -> ");
  scanf("%d", x_1);
  
  printf("Enter Y coordinate #1 -> ");
  scanf("%d", y_1);

  printf("Enter X coordinate #2 -> ");
  scanf("%d", x_2);

  printf("Enter Y coordinate #2 -> ");
  scanf("%d", y_2);
  
  printf("Enter X coordinate #3 -> ");
  scanf("%d", x_3);

  printf("Enter Y coordinate #3 -> ");
  scanf("%d", y_3);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcDist
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. int x_i x coord of starting point
*    2. int y_i y coord of starting point
*    3. int x_f x coord of ending point
*    4. int y_f y coord of ending point
*
*  Function Description: Calculates distance between 2 points
*
***************************************************************************/
double CalcDist(int x_i, int y_i, int x_f, int y_f)
{
  //---Declarations---
  double dist = 0; // Distance between 2 points 

  //---Executables---
  // Calculations
  dist = sqrt(pow(x_f - x_i, 2) + pow(y_f - y_i, 2));
  
  //---End---
  return(dist);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcInCen_X
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double d_12 distance between point 1 and 2
*    2. double d_23 distance between point 2 and 3
*    3. double d_31 distance between point 3 and 1
*    4. int x_1 x coord of point 1
*    5. int x_2 x coord of point 2
*    6. int x_3 x coord of point 3
*
*  Function Description: Calculates x coord of incenter using variables above
*
***************************************************************************/
double CalcInCen_X(double d_12, double d_23, double d_31, int x_1, int x_2, int x_3)
{
  //---Declarations---
  double incen_x = 0; // x coord of incenter

  //---Executables---
  // Calculations
  incen_x = ((d_12 * x_3) + (d_23 * x_1) + (d_31 * x_2)) / (d_12 + d_23 + d_31);

  //---End---
  return(incen_x);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcInCen_Y
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double d_12 distance between point 1 and 2
*    2. double d_23 distance between point 2 and 3
*    3. double d_31 distance between point 3 and 1
*    4. int y_1 y coord of point 1
*    5. int y_2 y coord of point 2
*    6. int y_3 y coord of point 3
*
*  Function Description: Calculates y coord of incenter using variables above
*
***************************************************************************/
double CalcInCen_Y(double d_12, double d_23, double d_31, int y_1, int y_2, int y_3)
{
  //---Declarations---
  double incen_y = 0; // y coord of incenter

  //---Executables---
  // Calculations
  incen_y = ((d_12 * y_3) + (d_23 * y_1) + (d_31 * y_2)) / (d_12 + d_23 + d_31);

  //---End---
  return(incen_y);
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
*    1. double d_12 distance between point 1 and 2
*    2. double d_23 distance between point 2 and 3
*    3. double d_31 distance between point 3 and 1
*    4. double incen_x x coord of incenter
*    5. double incen_y y coord of incenter
*
*  Function Description: Output above variables
*
***************************************************************************/
void Output(double d_12, double d_23, double d_31, double incen_x, double incen_y)
{
  //---Executables---
  printf("\nDistance from point 1 to point 2: %0.2lf", d_12);
  printf("\nDistance from point 2 to point 3: %0.2lf", d_23);
  printf("\nDistance from point 3 to point 1: %0.2lf", d_31);
  printf("\nLocation of incenter: %0.2lf, %0.2lf\n", incen_x, incen_y);
}
