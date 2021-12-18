/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*  2. mcouso@purdue.edu
*  3. jiang781@purdue.edu
*
*  Lab #: 5
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs three points (A, B, C) that will always create a triangle with a positive area. Program will calculate and output the measures of its three internal angles and the areas of the three quadrilaterals (Area A, Area B, Area C) created when a perpendicular lines are connected from the incenter to each side of the triangle
*
***************************************************************************/

#include <stdio.h>
#include <math.h>

void Input (double*, double*, double*, double*, double*, double*);
double CalcInCen_X (double, double, double, double, double, double);
double CalcInCen_Y (double d_12, double d_23, double d_31, double y_1, double y_2, double y_3);
double CalcDist (double, double, double, double);
double CalcAngle (double, double, double);
double CalcMin (double);
double CalcSec (double);
double CalcArea (double, double);
void Output (double, double, double, double, double, double, double, double, double, double, double, double);

int main (void)
{
  //---Declarations---
  double x_1 = 0; // x coord of point 1
  double y_1 = 0; // y coord of point 1
  double x_2 = 0; // x coord of point 2
  double y_2 = 0; // y coord of point 2
  double x_3 = 0; // x coord of point 3
  double y_3 = 0; // y coord of point 3

  double d_12 = 0; // Distance from point 1 to point 2
  double d_23 = 0; // Distance from point 2 to point 3
  double d_31 = 0; // Distance from point 3 to point 1

  double incen_x = 0; //x coorcinate of the incenter
  double incen_y = 0; //y coorcinate of the incenter

  double d_i1 = 0; //distance from the incenter to point 1
  double d_i2 = 0; //distance from the incenter to point 2
  double d_i3 = 0; //distance from the incenter to point 3

  double angle_1_degree = 0; //The degree of angle 1
  double angle_2_degree = 0; //The degree of angle 2
  double angle_3_degree = 0; //The degree of angle 3
  double angle_1_minute = 0; //The minute of angle 1
  double angle_2_minute = 0; //The minute of angle 2
  double angle_3_minute = 0; //The minute of angle 3
  double angle_1_second = 0; //The second of angle 1
  double angle_2_second = 0; //The second of angle 2
  double angle_3_second = 0; //The second of angle 3

  double area_1 = 0; //area of quadrilateral 1
  double area_2 = 0; //area of quadrilateral 2
  double area_3 = 0; //area of quadrilateral 3

  //---Executables---
  Input (&x_1, &y_1, &x_2, &y_2, &x_3, &y_3);
  d_12 = CalcDist(x_1, y_1, x_2, y_2);
  d_23 = CalcDist(x_2, y_2, x_3, y_3);
  d_31 = CalcDist(x_3, y_3, x_1, y_1);

  incen_x = CalcInCen_X (d_12, d_23, d_31, x_1, x_2, x_3);
  incen_y = CalcInCen_Y (d_12, d_23, d_31, y_1, y_2, y_3);
  d_i1 = CalcDist (x_1, y_1, incen_x, incen_y);
  d_i2 = CalcDist (x_2, y_2, incen_x, incen_y);
  d_i3 = CalcDist (x_3, y_3, incen_x, incen_y);

  angle_1_degree = CalcAngle (d_31, d_12, d_23);
  angle_2_degree = CalcAngle (d_23, d_12, d_31);
  angle_3_degree = CalcAngle(d_31, d_23, d_12);
  
  angle_1_minute = CalcMin(angle_1_degree);
  angle_2_minute = CalcMin(angle_2_degree);
  angle_3_minute = CalcMin(angle_3_degree);

  angle_1_second = CalcSec(angle_1_minute);
  angle_2_second = CalcSec(angle_2_minute);
  angle_3_second = CalcSec(angle_3_minute);
  
  area_1 = CalcArea (d_i1, angle_1_degree);
  area_2 = CalcArea (d_i2, angle_2_degree);
  area_3 = CalcArea (d_i3, angle_3_degree);

  Output((int)angle_1_degree,(int)angle_2_degree, (int)angle_3_degree, (int)angle_1_minute, (int)angle_2_minute, (int)angle_3_minute, angle_1_second, angle_2_second, angle_3_second, area_1, area_2, area_3);
  
  //---End---
  return (0);
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
*    1. double *x_1 memory address of x_1 in main() 
*    2. double *y_1 memory address of y_1 in main() 
*    3. double *x_2 memory address of x_2 in main() 
*.   4. double *y_2 memory address of y_2 in main() 
*    5. double *x_3 memory address of x_3 in main() 
*.   6. double *y_3 memory address of y_3 in main() 
*
*  Function Description: Gets user input and fills above variables
*
***************************************************************************/
void Input (double *x_1, double *y_1, double *x_2, double *y_2, double *x_3, double *y_3)
{
  //---Executables---
  printf("Enter X coordinate #1 -> ");
  scanf("%lf", x_1);

  printf("Enter Y coordinate #1 -> ");
  scanf("%lf", y_1);

  printf("Enter X coordinate #2 -> ");
  scanf("%lf", x_2);

  printf("Enter Y coordinate #2 -> ");
  scanf("%lf", y_2);

  printf("Enter X coordinate #3 -> ");
  scanf("%lf", x_3);

  printf("Enter Y coordinate #3 -> ");
  scanf("%lf", y_3);
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
*    1. double d_12: distance between point 1 and 2
*    2. double d_23: distance between point 2 and 3
*    3. double d_31: distance between point 3 and 1
*    4. double x_1: x coord of point 1
*    5. double x_2: x coord of point 2
*    6. double x_3: x coord of point 3
*
*  Function Description: Calculates x coord of incenter using variables above
*
***************************************************************************/
double CalcInCen_X (double d_12, double d_23, double d_31, double x_1, double x_2, double x_3)
{
  //---Declarations---
  double incen_x = 0; // x coord of incenter

  //---Executables---
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
double CalcInCen_Y (double d_12, double d_23, double d_31, double y_1, double y_2, double y_3)
{
  //---Declarations---
  double incen_y = 0; // y coord of incenter

  //---Executables---
  incen_y = ((d_12 * y_3) + (d_23 * y_1) + (d_31 * y_2)) / (d_12 + d_23 + d_31);

  //---End---
  return(incen_y);
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
double CalcDist (double x_i, double y_i, double x_f, double y_f)
{
  //---Declarations---
  double dist = 0; // Distance between 2 points

  //---Executables---
  dist = sqrt(pow(x_f - x_i, 2) + pow(y_f - y_i, 2));

  //---End---
  return(dist);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcAngle
*
*  Function Return Type: double 
*
*  Parameters (list data type, name, and comment one per line):
*    1. double side1: side lenght 1 of a triangle
*    2. double side2: side lenght 2 of a triangle
*    3. double side3: side lenght 3 of a triangle
*
*  Function Description: Calculates a specific angle of a triangle using *  above value
*
***************************************************************************/
double CalcAngle (double side1, double side2, double side3)
{
  //---Declarations--- 
  double angle = 0; //a specific angle of the triangle

  //---Executables---
  angle = (acos(((pow(side1, 2) + pow(side2, 2) - pow(side3, 2)) / (2 * side1 * side2))) * 180) / M_PI;
  
  //---End---
  return(angle);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcMin
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double degree The degree component of the angle
*
*  Function Description: Using the conversion, this function computes 
*  the minute component of the angle
*
***************************************************************************/
double CalcMin (double degree)
{
  //---Declarations--- 
  int conversion_F = 60; //conversion factor from degree ot minute
  double min = 0; //the minute of a specific angle

  //---Executables---
  min = (degree - (int) degree) * conversion_F; 

  //---End---
  return(min);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcSec
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double min The minute component of the angle
*
*  Function Description: Using the conversion, this function computes the second component of the angle
*
***************************************************************************/
double CalcSec (double min)
{
  //---Declarations--- 
  int conversion_F = 60; //conversion factor from minute to degree
  double sec = 0; //the seconds of a specific angle
  
  //---Executables---
  sec = (min - (int) min) * conversion_F; 

  //---End---
  return(sec);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc Area
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double dist The distance between the incenter and the specified point
*    2. double angle The angle measure before it was converted
*  
*  Function Description: This function finds the area of the specified quadrilateral.
*
***************************************************************************/
double CalcArea (double dist, double angle)
{
  //---Declarations--- 
  double area = 0; // Area of internal quadrilaterals
  
  //---Executables---
  area = pow(dist, 2) * sin((angle / 2) * (M_PI / 180)) * cos(((angle / 2) * M_PI) / 180);
  
  //---End---
  return(area);
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
*    1. double angle_1_degree The degree component of the angle 1
*    2. double angle_2_degree The degree component of the angle 2
*    3. double angle_3_degree The degree component of the angle 3
*    4. double angle_1_minute The minute component of the angle 1
*    5. double angle_2_minute The minute component of the angle 2
*    6. double angle_3_minute The minute component of the angle 3
*    7. double angle_1_second The second component of the angle 1
*    8. double angle_2_second The second component of the angle 2
*    9. double angle_3_second The second component of the angle 3
*    10. double area_1 The area of quadrilateral 1
*    11. double area_2 The area of quadrilateral 2
*    12. double area_3 The area of quadrilateral 3
*
*  Function Description: Outputs the above variables.
*
***************************************************************************/
void Output (double angle_1_degree, double angle_2_degree, double angle_3_degree, double angle_1_minute, double angle_2_minute, double angle_3_minute, double angle_1_second, double angle_2_second, double angle_3_second, double area_1, double area_2, double area_3)
{
  //---Executables---
  printf("\n\nInternal triangle angles: %0.0lf%c%c %0.0lf\' %0.2lf\", %0.0lf%c%c %0.0lf\' %0.2lf\", %0.0lf%c%c %0.0lf\' %0.2lf\"", angle_1_degree, 0xC2, 0xB0, angle_1_minute, angle_1_second, angle_2_degree, 0xC2, 0xB0, angle_2_minute, angle_2_second,angle_3_degree, 0xC2, 0xB0, angle_3_minute, angle_3_second);

  printf("\nArea of quadrilaterals: %0.2lf, %0.2lf, %0.2lf\n", area_1, area_2, area_3);
}
