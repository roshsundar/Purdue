
/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #: 3
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source, 
*  either modified or unmodified.  Neither have I provided access to my code 
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: DIST
*
*  Program Description: User inputs the initial height, velocity, and angle (to the horizontal) of a projectile being launched
*  This program will calculate the time to reach maximum height, the maximum height reached, the time to hit the ground, and 
*  the total distance traveled; it will output those results.
*
***************************************************************************/
#include <stdio.h>
#include <math.h>

#define G 9.8
#define R2D M_PI / 180

void Input(double*, double*, double*);
double Calc_t_maxh(double, double);
double Calc_h_max(double, double, double, double);
double Calc_t_f(double, double, double);
double Calc_d_f(double, double, double);
void Output(double, double, double, double);

int main(void)
{
  //---Declaration---
  double h_i = 0; // Initial height
  double v_i = 0; // Inital velocity
  double angle = 0; // Angle of launch

  double t_maxh = 0; // Time when projectile reaches max height
  double h_max = 0; // Maxiumum height reached
  double t_f = 0; // Time to hit ground
  double d_f = 0; // Total distance travelled

  //---Executables---
  // Input
  Input(&h_i, &v_i, &angle);
  
  // Calculations
  t_maxh = Calc_t_maxh(v_i, angle);
  h_max = Calc_h_max(h_i, v_i, angle, t_maxh);
  t_f = Calc_t_f(v_i, angle, h_i);
  d_f = Calc_d_f(v_i, angle, t_f);

  // Output
  Output(t_maxh, h_max, t_f, d_f);

  //---End---
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
*    1. double *h_i // Fills h_i in main()
*    2. double *v_i // Fills v_i in main()
*    3. double angle // Fills angle in main()
*
*  Function Description: Gather user input for *h_i, *v_i, *angle and return
*  to appropriate vairables in main()
*
***************************************************************************/
void Input(double *h_i, double *v_i, double *angle)
{
  //---Executables---
  // Input
  printf("Enter height of launch [m] -> ");
  scanf("%lf", h_i);

  printf("Enter initial velocity [m/s] -> ");
  scanf("%lf", v_i);

  printf("Enter angle to the horizontal [degrees] -> ");
  scanf("%lf", angle);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_t_maxh
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double v_i // Initial velocity needed to calculate t_maxh
*    2. double angle // Angle needed to calculate t_maxh
*
*  Function Description: Calculate t_maxh, or time to reach max height
*
***************************************************************************/
double Calc_t_maxh(double v_i, double angle)
{
  //---Declarations---
  double t_maxh = 0; // Time to reach max height

  //---Executables---
  // Calculations
  t_maxh = (v_i * sin(angle * R2D)) / G;

  //---End---
  return(t_maxh);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_h_max
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double h_i // Initial height needed for calculation
*    2. double v_i // Initial velocity needed for calculation
*    3. double angle // Angle needed for calculation
*    4. double t_maxh // Time to reach max height needed for calcuation
*
*  Function Description: Calculate h_max, or max height
*
***************************************************************************/
double Calc_h_max(double h_i, double v_i, double angle, double t_maxh)
{
  //---Declarations---
  double h_max = 0; // Max height

  //---Executables---
  // Calculations
  h_max = h_i + (v_i * sin(angle * R2D) * t_maxh) - (0.5 * G * pow(t_maxh, 2));

  //---End---
  return(h_max);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_t_f
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double v_i // Initial velocity needed for calculation
*    2. double angle // Angle needed for calculation
*    3. double h_i // Initial height needed for calculation
*
*  Function Description: Calculate t_f, or time to hit ground
*
***************************************************************************/
double Calc_t_f(double v_i, double angle, double h_i)
{
  //---Declarations--
  double t_f = 0; // Time to hit ground

  //---Executables---
  // Calculations
  t_f += v_i * sin(angle * R2D);
  t_f += sqrt((pow(v_i, 2) * pow(sin(angle * R2D), 2)) + (2 * G * h_i));
  t_f /= G;

  //--End--
  return(t_f);
}

/***************************************************************************
*
*  Function Information
*
*  Name of Function: Calc_d_f
*
*  Function Return Type: double
*
*  Parameters (list data type, name, and comment one per line):
*    1. double v_i // Initial velocity needed for calculation
*    2. double angle // Angle needed for calculation
*    3. double t_f // Time to hit ground needed for calculation
*
*  Function Description: Calculate d_f, or total distance travelled
*
***************************************************************************/
double Calc_d_f(double v_i, double angle, double t_f)
{
  //---Declarations---
  double d_f = 0; // Total distance travelled

  //---Executables---
  // Calculations
  d_f = v_i * cos(angle * R2D) * t_f;

  //--End---
  return(d_f);
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
*    1. double t_maxh // Time to reach max height to be output
*    2. double h_max // Maxiumum height reached to be output
*    3. double t_f // Time to hit ground to be output
*    4. double d_f // Total distance travelled to be output
*
*  Function Description: Print all of the above values
*
***************************************************************************/
void Output(double t_maxh, double h_max, double t_f, double d_f)
{
  //---Executables---
  // Output
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  printf("\nTime to max height: %19.2lf s", t_maxh);
  printf("\nMaximum height reached: %15.2lf m", h_max);
  printf("\nTime to hit ground: %19.2lf s", t_f);
  printf("\nTotal distance traveled: %14.2lf m", d_f);
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}
