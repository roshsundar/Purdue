
/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*  2. mcouso@purdue.edu
*  3. jiang781@purdue.edu (delete line if no third partner)
*
*  Lab #:1
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: 1/27/2020 5:10pm Asynch
*
*  Program Description: The user inputs the radius of a circle and the program calculates - Circle area, Side length of inscri
*                       -bed pentagon, and Incribed pentagon area.
***************************************************************************/

#include <stdio.h>

#define PI 3.1416

int  main(void)
{
  // Variable Initialization
  float radius = 0; // Represents radius of a circle
  float circle_area = 0; // Represents area of a circle
  float pent_side = 0; // Represents length of side of a pentagon
  float pent_area  = 0; // Represents area of a pentagon

  // Input
  printf("Please enter the value of the radius -> ");
  scanf("%f", &radius);
  
  // Calculations
  circle_area = PI * radius * radius;
  pent_side = 2 * radius * 0.587786441; // 0.587.. represents sin(PI/5) [radians] given by instructions
  pent_area = (2.5) * pent_side * (pent_side / 2) * 1.376381920; // 1.37.. represents sin(54)/sin(36) [degrees] given by law                                                                      of sines 
  // Output
  printf("Circle Area: %.2f\n", circle_area);
  printf("Pentagon Side: %.2f\n", pent_side);
  printf("Pentagon Area: %.2f\n", pent_area);

  return(0);
}
