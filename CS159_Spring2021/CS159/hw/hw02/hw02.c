
/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #: 2
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source, 
*  either modified or unmodified.  Neither have I provided access to my code 
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: Distance
*
*  Program Description: The user inputs the  mass of an airplane, the amount of forward force produced by its propellers, and *  the mass of the TWO gliders it is towing (airplane connected to first glider and the first glider is connected to the
*  second glider). The program calculates the resulting tension on each cable connecting the aircraft and the acceleration of *  the glider.
*
***************************************************************************/
#include <stdio.h>
#include <math.h>

int main(void)
{
  //---Local Declarations---
  double m_p = 0; // mass of plane
  double f_sys = 0; // force of the system/propellers
  double a_sys = 0; // acceleration of system

  double m_g1 = 0; // mass of glider1
  double m_g2 = 0; // mass of glider2

  double f_t1 = 0; // force of tension on cable1
  double f_t2 = 0; // force of tension on cable2
  
  int w = 0; // width modifier for output

  //---Executable Statements--
  // Input
  printf("Enter mass of airplane (kg) -> ");
  scanf("%lf", &m_p);

  printf("Enter mass of glider #1 (kg) -> ");
  scanf("%lf", &m_g1);

  printf("Enter mass of glider #2 (kg) -> ");
  scanf("%lf", &m_g2);
  
  printf("Enter force produced by propellers (N) -> ");
  scanf("%lf", &f_sys);

  // Calculations
  a_sys = f_sys / (m_p + m_g1 + m_g2);
  
  f_t1 = f_sys - (m_p * a_sys);

  f_t2 = f_t1 - (m_g1 * a_sys);
  
  w = log10(f_sys) + 6;

  // Output
  printf("\nAcceleration: %0.2lf m/s^2", a_sys);
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  printf("\nResulting tension on cable #1: %*.2lf Newtons", w, f_t1);
  printf("\nResulting tension on cable #2: %*.2lf Newtons", w, f_t2);
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  
  // End
  return(0);
}
