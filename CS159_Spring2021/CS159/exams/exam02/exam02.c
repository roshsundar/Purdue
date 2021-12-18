/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*
*  Lab #: exam 2
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs three points that will always create a triangle with a positive area. Program calculates the location of the orthocenter. It creates a triangle that connects the orthocenter to the end points of the largest side in the triangle ABC, for which it calculates the internal angles and type [isosceles, scalene, equilateral] [acute, obtuse, right]
*
***************************************************************************/
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void Input(double*, double*, double*, double*, double*, double*);
double CalcDist(double, double, double, double);
double CalcAngle(double, double, double);
double GetOrthoC_x(double, double, double, double, double, double);
double GetOrthoC_y(double, double, double, double, double, double);
double CalcIntAngleA(double, double, double, double, double, double);
double CalcIntAngleB(double, double, double, double, double, double);
double CalcIntAngleC(double, double, double, double, double, double);
void Output(double, double, double, double, double);

int main(void)
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

  double angle_1 = 0; // The degree of angle 1
  double angle_2 = 0; // The degree of angle 2
  double angle_3 = 0; // The degree of angle 3
  
  double orthc_x = 0; // The x coord of orthocenter
  double orthc_y = 0; // The y coord of orthocenter

  double d_1O = 0; // Distance from point 1 to orthocenter
  double d_2O = 0; // Distance from point 2 to orthocenter
  double d_3O = 0; // Distance from point 3 to orthocenter

  double angle_A = 0; // An angle of the internal triangle
  double angle_B = 0; // Another angle of the internal triangle
  double angle_C = 0; // Final angle of the internal triangle

  //---Executables---
  Input (&x_1, &y_1, &x_2, &y_2, &x_3, &y_3);

  d_12 = CalcDist(x_1, y_1, x_2, y_2);
  d_23 = CalcDist(x_2, y_2, x_3, y_3);
  d_31 = CalcDist(x_3, y_3, x_1, y_1);

  angle_1 = CalcAngle(d_31, d_12, d_23);
  angle_2 = CalcAngle(d_23, d_12, d_31);
  angle_3 = CalcAngle(d_31, d_23, d_12);

  orthc_x = GetOrthoC_x(x_1, x_2, x_3, angle_1, angle_2, angle_3);
  orthc_y = GetOrthoC_y(y_1, y_2, y_3, angle_1, angle_2, angle_3);

  d_1O = CalcDist(x_1, y_1, orthc_x, orthc_y);
  d_2O = CalcDist(x_2, y_2, orthc_x, orthc_y);
  d_3O = CalcDist(x_3, y_3, orthc_x, orthc_y);

  angle_A = CalcIntAngleA(d_12, d_23, d_31, d_1O, d_2O, d_3O);
  angle_B = CalcIntAngleB(d_12, d_23, d_31, d_1O, d_2O, d_3O);
  angle_C = CalcIntAngleC(d_12, d_23, d_31, d_1O, d_2O, d_3O);

  Output(orthc_x, orthc_y, angle_A, angle_B, angle_C);

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
  printf("Enter point #1 -> ");
  scanf("%lf%lf", x_1, y_1);

  printf("Enter point #2 -> ");
  scanf("%lf%lf", x_2, y_2);

  printf("Enter point #3 -> ");
  scanf("%lf%lf", x_3, y_3);
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
  double dist = 0; //Distance between 2 points

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
*    1. double side1: side length 1 of a triangle
*    2. double side2: side length 2 of a triangle
*    3. double side3: side length 3 of a triangle
*
*  Function Description: Calculates a specific angle of a triangle using above value
*
***************************************************************************/
double CalcAngle (double side1, double side2, double side3)
{
  //---Declarations--- 
  double angle = 0; //A specific angle of the triangle

  //---Executables---
  angle = (acos(((pow(side1, 2) + pow(side2, 2) - pow(side3, 2)) / (2 * side1 * side2))) * 180) / M_PI;
  
  //---End---
  return(angle);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetOrthoC_x
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double x_1: get x coordinate of point 1
*    2. double x_2: get x coordinate of point 2
*    3. double x_3: get x coordinate of point 3
*    4. double angle_1: get degree of angle 1
*    5. double angle_2: get degree of angle 2
*    6. double angle_3: get degree of angle 3
*
*  Function Description: Calculates the x coord of the orthocenter of a triangle
*
***************************************************************************/
double GetOrthoC_x (double x_1, double x_2, double x_3, double angle_1, double angle_2, double angle_3)
{
  //---Declarations---
  double ortho_x; // The x coord of orthocenter of a triangle
  
  //---Executables---
  ortho_x = (x_1 * tan((M_PI *angle_1) / 180) + x_2 * tan((M_PI *angle_2) / 180) + x_3 * tan((M_PI *angle_3) / 180)) / (tan((M_PI *angle_1) / 180) + tan((M_PI *angle_2) / 180) + tan((M_PI *angle_3) / 180));

  ortho_x = fabs(ortho_x) == 0 ? 0 : ortho_x; 
  
  //---Exit---
  return(ortho_x);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetOrthoC_y
*
*  Function Return Type: double 
*
*  Parameters (list data type, name, and comment one per line):
*    1. double x_1: get y coordinate of point 1
*    2. double x_2: get y coordinate of point 2
*    3. double x_3: get y coordinate of point 3
*    4. double angle_1: get degree of angle 1
*    5. double angle_2: get degree of angle 2
*    6. double angle_3: get degree of angle 3
*
*  Function Description: Calculates the y coord of the orthocenter of a triangle
*
***************************************************************************/
double GetOrthoC_y (double y_1, double y_2, double y_3, double angle_1, double angle_2, double angle_3)
{
  //---Declarations---
  double ortho_y; // The y coord of orthocenter of a triangle

  //---Executables---
  ortho_y = (y_1 * tan((M_PI *angle_1) / 180) + y_2 * tan((M_PI *angle_2) / 180) + y_3 * tan((M_PI *angle_3) / 180)) / (tan((M_PI *angle_1) / 180) + tan((M_PI *angle_2) / 180) + tan((M_PI *angle_3) / 180));

  ortho_y = fabs(ortho_y) == 0 ? 0 : ortho_y; 

  //---Exit---
  return(ortho_y);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcIntAngleA
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double d_12 // Distance from point 1 to point 2
*    2. double d_23 // Distance from point 2 to point 3
*    3. double d_31 // Distance from point 3 to point 1
*    4. double d_1O // Distance from point 1 to orthocenter
*    5. double d_2O // Distance from point 2 to orthocenter
*    6. double d_3O // Distance from point 3 to orthocenter
*
*  Function Description: Calculates an angle A of the interior triangle
*
***************************************************************************/
double CalcIntAngleA(double d_12, double d_23, double d_31, double d_1O, double d_2O, double d_3O)
{
  //---Declarations---
  double angle_A = 0; // An angle of the internal triangle

  //---Executables---
  if(d_12 >= d_23 && d_12 >= d_31)
  {
    angle_A = CalcAngle(d_12, d_1O, d_2O);
  }
  else if(d_23 >= d_12 && d_23 >= d_31)
  {
    angle_A = CalcAngle(d_23, d_2O, d_3O);
  }
  else if(d_31 >= d_12 && d_31 >= d_23)
  {
    angle_A = CalcAngle(d_31, d_1O, d_3O);
  }

  //---Exit---
  return(angle_A);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcIntAngleB
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double d_12 // Distance from point 1 to point 2
*    2. double d_23 // Distance from point 2 to point 3
*    3. double d_31 // Distance from point 3 to point 1
*    4. double d_1O // Distance from point 1 to orthocenter
*    5. double d_2O // Distance from point 2 to orthocenter
*    6. double d_3O // Distance from point 3 to orthocenter
*
*  Function Description: Calculates an angle B of the interior triangle
*
***************************************************************************/
double CalcIntAngleB(double d_12, double d_23, double d_31, double d_1O, double d_2O, double d_3O)
{
  //---Declarations---
  double angle_B = 0; // An angle of the internal triangle

  //---Executables---
  if(d_12 >= d_23 && d_12 >= d_31)
  {
    angle_B = CalcAngle(d_2O, d_12, d_1O);
  }
  else if(d_23 >= d_12 && d_23 >= d_31)
  {
    angle_B = CalcAngle(d_3O, d_23, d_2O);
  }
  else if(d_31 >= d_12 && d_31 >= d_23)
  {
    angle_B = CalcAngle(d_3O, d_31, d_1O);
  }

  //---Exit---
  return(angle_B);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: CalcIntAngleC
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double d_12 // Distance from point 1 to point 2
*    2. double d_23 // Distance from point 2 to point 3
*    3. double d_31 // Distance from point 3 to point 1
*    4. double d_1O // Distance from point 1 to orthocenter
*    5. double d_2O // Distance from point 2 to orthocenter
*    6. double d_3O // Distance from point 3 to orthocenter
*
*  Function Description: Calculates an angle C of the interior triangle
*
***************************************************************************/
double CalcIntAngleC(double d_12, double d_23, double d_31, double d_1O, double d_2O, double d_3O)
{
  //---Declarations---
  double angle_C = 0; // An angle of the internal triangle

  //---Executables---
  if(d_12 >= d_23 && d_12 >= d_31)
  {
    angle_C = CalcAngle(d_1O, d_2O, d_12);
  }
  else if(d_23 >= d_12 && d_23 >= d_31)
  {
    angle_C = CalcAngle(d_2O, d_3O, d_23);
  }
  else if(d_31 >= d_12 && d_31 >= d_23)
  {
    angle_C = CalcAngle(d_1O, d_3O, d_31);
  }

  //---Exit---
  return(angle_C);
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
*    1. double orthc_x // The x coord of orthocenter
*    2. double orthc_y // The y coord of orthocenter
*    3. double angle_A // An angle of the internal triangle
*    4. double angle_B // Another angle of the internal triangle
*    5. double angle_C // Final angle of the internal triangle
*
*  Function Description: Print the orthocenter, the sorted internal angles, and triangle type
*
***************************************************************************/
void Output(double orthc_x, double orthc_y, double angle_A, double angle_B, double angle_C)
{
  //---Declarations---
  double min = 0; // Minimum angle, used in sorting
  double med = 0; // Medium angle, used in sorting
  double max = 0; // Maximum angle, used in sorting
  double temp = 0; // Placeholder variable, used in sorting

  //---Executables---
  // Output orthocenter coordinates
  printf("\nCordinates of orthocenter: %0.2lf, %0.2lf", orthc_x, orthc_y);

  // Output angles in order
  min = angle_A;
  med = angle_B;
  max = angle_C;
  if(min > med)
  {
    temp = min;
    min = med;
    med = temp;
  }
  if(min > max)
  {
    temp = min;
    min = max;
    max = temp;
  }
  if(med > max)
  {
    temp = med;
    med = max;
    max = temp;
  }
  printf("\nInternal triangle angles: %0.1lf, %0.1lf, %0.1lf", min, med, max);

  // Output triangle type
  printf("\nTriangle Type: ");
  if(fabs(angle_A - 60) < 0.001 && fabs(angle_B - 60) < 0.001 && fabs(angle_C - 60) < 0.001)
  {
    printf("Equilateral ");
  }
  else if(fabs(angle_A - angle_B) > 0.001 && fabs(angle_A - angle_C) > 0.001 && fabs(angle_B - angle_C) > 0.001)
  {
    printf("Scalene ");
  }
  else
  {
    printf("Isosceles ");
  }

  if(fabs(angle_A - 90) < 0.001 || fabs(angle_B - 90) < 0.001 || fabs(angle_C - 90) < 0.001)
  {
    printf("right\n");
  }
  else if(angle_A < 90 && angle_B < 90 && angle_C < 90)
  {
    printf("acute\n");
  }
  else
  {
    printf("obtuse\n");
  }
}
