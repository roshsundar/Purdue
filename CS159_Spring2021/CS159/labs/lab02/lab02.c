
/***************************************************************************
*
*  Programmers and Purdue Email Addresses:
*  1. rmsundar@purdue.edu
*  2. jiang781@purdue.edu
*  3. mcouso@purdue.edu
*
*  Lab #: 2
*
*  Academic Integrity Statement:
*
*  We have not used source code obtained from any other unauthorized source,
*  either modified or unmodified.  Neither have we provided access to our code
*  to another. The effort we are submitting is our own original work.
*
*  Day, Time, Location of Lab: Distance
*
*  Program Description:In the image given in the lab document, there is a smaller circle inscribed inside of a regular hexagon*  . The hexagon is inscribed inside of a larger circle. And finally the larger circle is inscribed inside of a regular pentag*  -on. Given the radius of the smaller circle, this program will calculate the following: 1.Area of the small circle. 2.Area *  and side length of the hexagon. 3.Area of the large circle. 4.Area and side length of the pentagon
*
***************************************************************************/
#include <stdio.h>
#include <math.h>

int main(void)
{
  //---Local Declarations---
  double sc_radius = 0; // Radius of the small circle
  double sc_area = 0; // Area of the small circle
  
  double hex_side = 0; // Side length of hexagon & radius of large circle
  double hex_area = 0; // Area of hexagon
  
  double lc_area = 0; // Area of large circle

  double pent_side = 0; // Side length of pentagon
  double pent_area = 0; // Area of pentagon

  //---Executables---
  // Input
  printf("Enter the radius of the small circle -> ");
  scanf("%lf", &sc_radius);

  // Calculations
  sc_area = M_PI * pow(sc_radius, 2);

  hex_side = 2 * sqrt(3) * sc_radius / 3;
  hex_area = 3 * pow(hex_side, 2) * sqrt(3) / 2;

  lc_area = M_PI * pow(hex_side, 2);

  pent_side = hex_side * 2 * tan(M_PI / 5);
  pent_area = 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * pow(pent_side, 2);

  // Output
  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  printf("Area of small circle: %13.2lf\n", sc_area);
  printf("Hexagon side length: %14.2lf\n", hex_side);
  printf("Area of hexagon: %18.2lf\n", hex_area);
  printf("Area of large circle: %13.2lf\n", lc_area);
  printf("Pentagon side length: %13.2lf\n", pent_side);
  printf("Area of pentagon: %17.2lf\n", pent_area);
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
 
  // End
  return(0);
}
