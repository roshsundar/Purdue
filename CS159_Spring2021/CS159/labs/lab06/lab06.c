/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*  2. jiang781@purdue.edu
*  3. mcouso@purdue.edu
*
*  Lab #: 6
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs three points (A, B, C) that will always create a triangle with a positive area. Program calculates and outputs the location of the orthocenter, circumcenter, and the location of the center of the nine point circle and whether that point is inside or outside of the triangle
*
***************************************************************************/

#include <stdio.h>
#include <math.h>

void Input (double*, double*, double*, double*, double*, double*);
double GetOrthoC_x (double, double, double, double, double, double);
double GetOrthoC_y (double, double, double, double, double, double);
double CalcDist (double, double, double, double);
double CalcAngle (double, double, double);
double GetCircumC_x(double, double, double, double, double, double);
double GetCircumC_y(double, double, double, double, double, double);
double GetNinePointC_x (double, double);
double GetNinePointC_y (double, double);
double GetTriArea (double, double, double);
void Output (double, double, double, double, double, double, double, double, double, double);

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

  double d_1cen9 = 0; //Distance from point 1 to nine point circle center
  double d_2cen9 = 0; //Distance from point 2 to nine point circle center
  double d_3cen9 = 0; //Distance from point 3 to nine point circle center

  double angle_1 = 0; // The degree of angle 1
  double angle_2 = 0; // The degree of angle 2
  double angle_3 = 0; // The degree of angle 3
  
  double orthc_x = 0; // The x coord of orthocenter
  double orthc_y = 0; // The y coord of orthocenter

  double circ_x = 0; // The x coord of circumcenter
  double circ_y = 0; // The y coord of circumcenter

  double cen9_x = 0; // The x coord of nine point circle center
  double cen9_y = 0; // The y coord of nine point circle center

  double triArea = 0; //The area of the triangle made up with point A, B and C
  double smallTri_A1 = 0; //The area of the triangle made up with points A, B and nine point circle center
  double smallTri_A2 = 0; //The area of the triangle made up with points B, C, and the nine point circle center
  double smallTri_A3 = 0; //The area of the triangle made up with points C, A, and the nine point circle center

  //---Executables---
  Input (&x_1, &y_1, &x_2, &y_2, &x_3, &y_3);
  
  d_12 = CalcDist(x_1, y_1, x_2, y_2);
  d_23 = CalcDist(x_2, y_2, x_3, y_3);
  d_31 = CalcDist(x_3, y_3, x_1, y_1);

  angle_1 = CalcAngle (d_31, d_12, d_23);
  angle_2 = CalcAngle (d_23, d_12, d_31);
  angle_3 = CalcAngle(d_31, d_23, d_12);

  orthc_x = GetOrthoC_x(x_1, x_2, x_3, angle_1, angle_2, angle_3);
  orthc_y = GetOrthoC_y(y_1, y_2, y_3, angle_1, angle_2, angle_3);
  
  circ_x = GetCircumC_x(x_1, x_2, x_3, angle_1, angle_2, angle_3);
  circ_y = GetCircumC_y(y_1, y_2, y_3, angle_1, angle_2, angle_3);
  
  cen9_x = GetNinePointC_x(orthc_x, circ_x);
  cen9_y = GetNinePointC_y(orthc_y, circ_y);

  d_1cen9 = CalcDist(cen9_x, cen9_y, x_1, y_1);
  d_2cen9 = CalcDist(cen9_x, cen9_y, x_2, y_2);
  d_3cen9 = CalcDist(cen9_x, cen9_y, x_3, y_3);

  triArea = GetTriArea(d_12, d_23, d_31);
  smallTri_A1 = GetTriArea(d_12, d_1cen9, d_2cen9); 
  smallTri_A2 = GetTriArea(d_23, d_2cen9, d_3cen9);
  smallTri_A3 = GetTriArea(d_31, d_1cen9, d_3cen9);

  Output(orthc_x, orthc_y, circ_x, circ_y, cen9_x, cen9_y, triArea, smallTri_A1, smallTri_A2, smallTri_A3);

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

  //---Exit---
  return(ortho_y);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetCircumC_x
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
*  Function Description: Calculates the x coord of the circumcenter of a triangle
*
***************************************************************************/
double GetCircumC_x (double x_1, double x_2, double x_3, double angle_1, double angle_2, double angle_3)
{
  //---Declarations---
  double circum_x; // x coord circumcenter of the triangle

  //---Executables---
  circum_x = (x_1 * sin((2 * M_PI * angle_1) / 180) + x_2 * sin((2 * M_PI * angle_2) / 180) + x_3 * sin((2 * M_PI * angle_3) / 180)) / (sin((2 * M_PI * angle_1) / 180) + sin((2 * M_PI * angle_2) / 180) + sin((2 * M_PI * angle_3) / 180));

  //---Exit---
  return(circum_x);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetCircumC_y
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
*  Function Description: Calculates the y coord of the circumcenter of a triangle
*
***************************************************************************/
double GetCircumC_y (double y_1, double y_2, double y_3, double angle_1, double angle_2, double angle_3)
{
  //---Declarations---
  double circum_y; // y coord of the circumcenter of a triangle

  //---Executables---
  circum_y = (y_1 * sin((2 * M_PI * angle_1) / 180) + y_2 * sin((2 * M_PI * angle_2) / 180) + y_3 * sin((2 * M_PI * angle_3) / 180)) / (sin((2 * M_PI * angle_1) / 180) + sin((2 * M_PI * angle_2) / 180) + sin((2 * M_PI * angle_3) / 180));

  //---Exit---
  return(circum_y);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetNinePointC_x
*
*  Function Return Type: double 
*
*  Parameters (list data type, name, and comment one per line):
*    1. double orthc_x: get x coord of the orthocenter of a triangle
*    2. double circ_x: get x coord of the circumcenter of a triangle
*
*  Function Description: Calculates the location of x coord of the center of the nine point circle
*
***************************************************************************/
double GetNinePointC_x (double orthc_x, double circ_x)
{
  //---Declarations---
  double center9_x; //x coord of nine point circle center

  //---Executables---
  center9_x = (orthc_x + circ_x) / 2;

  //---Exit---
  return(center9_x);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: GetNinePointC_y
*
*  Function Return Type: double 
*
*  Parameters (list data type, name, and comment one per line):
*    1. double orthc_y: get y coord of the orthocenter of a triangle
*    2. double circ_y: get y coord of the circumcenter of a triangle
*
*  Function Description: Calculates the location of y coord of the center of the nine point circle
*
***************************************************************************/
double GetNinePointC_y (double orthc_y, double circ_y)
{
  //---Declarations---
  double center9_y; //y coord of the nine point circle center

  //---Executables---
  center9_y = (orthc_y + circ_y) / 2;

  //---Exit---
  return(center9_y);
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
*  Function Description: Calculates a specific angle of a triangle using *  above value
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
*  Name of Function: GetTriArea
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. side1: length of one side of a triangle
*    2. side2: length of another side of a triangle
*    3. side3: length of last side of a triangle
*
*  Function Description: Calculate area of a triangle given the length of its sides
*
***************************************************************************/
double GetTriArea (double side1, double side2, double side3)
{
  //---Declarations--- 
  double semiP; //Semipermeter of the triangle
  double area; //Area of the triangle

  //---Executables---
  semiP = (side1 + side2 + side3) / 2;
  area = sqrt(((semiP - side1) * (semiP - side2) * (semiP - side3) * semiP));

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
*    1. double orthc_x x coordinate of the orthocenter
*    2. double orthc_y y coordinate of the orthocenter
*    3. double circ_x x coordinate of the circumcenter
*    4. double circ_y y coordinate of the circumcenter
*    5. double cen9_x x coordinate of the center of the nine point circle
*    6. double cen9_y y coordinate of the center of the nine point circle
*    7. double triArea Area of the triangle created by the points input by the user
*    8. double smallTri_A1 Area of one of the small triangles created by 2 points input by the user and the nine point circle center
*    9. double smallTri_A2 Area of one of the small triangles created by 2 points input by the user and the nine point circle center
*   10. double smallTri_A3 Area of one of the small triangles created by 2 points input by the user and the nine point circle center
*
*  Function Description: This function will recieving the parameters 1-6 and output them. Then the function will determine if parameter 7 is very close to the sum of parameters 8-10. If the sum is very close, it will output that the point is in the triangle, and if the sum is not that close, then it will output that the point is outside the triangle.
*
***************************************************************************/
void Output (double orthc_x, double orthc_y, double circ_x, double circ_y, double cen9_x, double cen9_y, double triArea, double smallTri_A1, double smallTri_A2, double smallTri_A3)
{
  //---Executables---
  printf("\nCoordinates of orthocenter: %0.2lf, %0.2lf", orthc_x, orthc_y);
  printf("\nCoordinates of circumcenter: %0.2lf, %0.2lf", circ_x, circ_y);

  if (fabs(triArea - (smallTri_A1 + smallTri_A2 + smallTri_A3)) < 0.001 )
  {
    printf("\nThe nine point circle center: %0.2lf, %0.2lf is inside of the triangle.\n", cen9_x, cen9_y);
  }
  else
  {
    printf("\nThe nine point circle center: %0.2lf, %0.2lf is outside of the triangle.\n", cen9_x, cen9_y);
  }
}
