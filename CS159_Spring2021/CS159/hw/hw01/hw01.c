
/***************************************************************************
*
*  Programmer and Purdue Email Address:
*  1. rmsundar@purdue.edu
*
*  Homework #:1
*
*  Academic Integrity Statement:
*
*  I have not used source code obtained from any other unauthorized source, 
*  either modified or unmodified.  Neither have I provided access to my code 
*  to another. The effort I am submitting is my own original work.
*
*  Day, Time, Location of Lab: Distance
*
*  Program Description: For a plane fying with a glider attached by cable - this program takes in the mass of an airplane, mass of a glider, and the force of an airplane; this is in order to calculate tension of the rope and acceleration of the glider
***************************************************************************/
#include <stdio.h>

int main(void)
{
  //---Local Declarations---
  double m_p = 0; // mass of plane
  double f_p = 0; // force of the plane

  double m_g = 0; // mass of glider
  double a_g = 0; // acceleration of glider

  double f_t = 0; // force of tension on cable
  
  //---Executable statements---
  // Input
  printf("Enter mass of airplane (kg) -> ");
  scanf("%lf", &m_p);

  printf("Enter mass of glider (kg) -> ");
  scanf("%lf", &m_g);

  printf("Enter force produced by propellers (N) -> ");
  scanf("%lf", &f_p);

  // Calculation
  a_g = f_p / (m_p + m_g);
  f_t = m_g * a_g;

  // Output
  printf("\nResulting tension: %0.2lf Newtons", f_t);
  printf("\nAcceleration of glider: %0.2lf m/s^2\n", a_g);

  return(0);
}
