
/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*  2. mcouso@purdue.edu
*  3. jiang781@purdue.edu (delete line if no third partner)
*
*  Lab #: 3
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Distance
*
*  Program Description: The user will input whether (1) a regular polygon is inscribed inside of a circle or (2) the circle is*  inscribed inside of a regular polygon. The number of sides and the apothem will follow as additional input. This program 
*  will calculate and display both the radius and area of the circle, and the side length and area of the regular polygon.
*
***************************************************************************/
#include <stdio.h>
#include <math.h>

int main(void)
{
  //---Local Declarations---
  int option = 0; // The option user inputs (1) or (2) to represent case1 and case2
  int factor = 0; // Calculate: (0) option = 1, (1) option = 2 
  int poly_sides = 0; // Number of sides for the polygon - input by user
  double poly_apoth = 0; // Length of polygon apothem- input by user

  double circ_radius = 0; // Calculated radius of circle
  double circ_area = 0; // Calculated area of circle
  double poly_side_len = 0; // Calculated length of polygon side
  double poly_area = 0; // Calculated area of polygon

  //---Executable Statements---
  // Inputs
  printf("1. Polygon inside of circle");
  printf("\n2. Circle inside of polygon");
  printf("\nSelect your option -> ");
  scanf("%d", &option);

  printf("Enter number of polygon sides -> ");
  scanf("%d", &poly_sides);

  printf("Enter length of polygon apothem -> ");
  scanf("%lf", &poly_apoth);

  // Calculations
  factor = 3 % option;

  circ_radius = (poly_apoth / cos(M_PI / poly_sides)) * (1 - factor) + (poly_apoth) * (factor); // left operation - (1) right operation - (2)
  circ_area = M_PI * pow(circ_radius, 2);

  poly_side_len = (2 * poly_apoth * tan(M_PI / poly_sides)) * (1 - factor) + (2 * (poly_apoth / tan(((poly_sides - 2) * M_PI) / (2 *  poly_sides)))) * (factor); // left operation - (1) right operation - (2)
  
  poly_area = (0.5 * poly_sides * poly_side_len * poly_apoth);

  // Output
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  printf("\nCircle Radius: %16.2lf", circ_radius);
  printf("\nCircle Area: %18.2lf", circ_area);
  printf("\nPolygon Side Length: %10.2lf", poly_side_len);
  printf("\nPolygon Area: %17.2lf", poly_area);
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

  //---Exit---
  return(0);
}
