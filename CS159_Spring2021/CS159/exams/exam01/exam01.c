
/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*
*  Lab #: exam 1
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Dist
*
*  Program Description: The user will provide a positive int value as the first input representing the following options:
*  (1) - A circle with an equilateral [T]riangle inscribed.
*  (2) - A circle with a [S]quare inscribed.
*  (3) or larger -  A regular polygon with a [C]ircle inscribed. The number of sides of the polygon is equal to the int input.
*
*  The second input is the area of the figure (circle for options 1 and 2, polygon for 3 or larger).
*  The program will calculate the radius or apothem and area of the inscribed figure.
***************************************************************************/
#include <stdio.h>
#include <math.h>

int main(void)
{
  //-----Local Declarations-----
  int n = 0; // Option choice and # of polygon sides if n >= 3
  int factor1 = 0; // Weight for (1)
  int factor2 = 0; // Weight for (2)
  int factor3 = 0; // Weight for (3)
  
  double fig_area = 0; // Area of whole figure
  double r_a = 0; // Radius of circle (1),(2) or Apothem (3)
  double in_area = 0; // Area of inscribed figure
  
  int c = 0; // Integer representing inscribed shape letter

  //-----Executable Statements-----
  // Input
  printf("Enter desired option -> ");
  scanf("%d", &n);

  printf("Enter area of figure -> ");
  scanf("%lf", &fig_area);
  
  // Calculations
  // Calculate weights
  factor1 = 1 / n;
  factor2 = ((2 / n) * (2 % (n + 1))) / 2;
  factor3 = 1 - factor1 - factor2;
  
  // Caclulate (1) values
  r_a += factor1 * sqrt(fig_area / M_PI);
  in_area += factor1 * (3 * sqrt(3) * pow(r_a, 2) / 4);

  // Calculate (2) values
  r_a += factor2 * sqrt(fig_area / M_PI);
  in_area += factor2 * (pow(2 * r_a, 2) / 2);

  // Caclulate (3) values
  r_a += factor3 * (sqrt(4 * fig_area * fabs(tan(M_PI / n))) / (2 * sqrt(n) * fabs(tan(M_PI / n))));
  in_area += factor3 * M_PI * pow(r_a, 2);
  
  // Calculate output character
  c = (factor1 * 84) + (factor2 * 83) + (factor3 * 67);
  // Output
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  printf("\nRadius/Apothem of figure with area given: %9.1lf", r_a);
  printf("\nArea of inscribed figure [%c]: %0.1lf\n", c, in_area);
  
  //-----End-----
  return(0);
}
