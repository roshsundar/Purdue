// ***
// *** You MUST modify this file.
// ***
#include <stdio.h>
#include <stdbool.h>
#include "hw3.h"

// must enclose the function by #ifdef TEST_INTEGRATE 
// and #endif to enable particial credits
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  // integrate the function stored in intrg's func
  // store the result in intrg's answer

  double deltax = ((intrg -> upperlimit) - (intrg -> lowerlimit)) / (intrg -> intervals);

  double integral = 0;

  for (int n = 1; n <= (intrg -> intervals); n++)
  {
    integral += intrg -> func((intrg -> lowerlimit) + (n - 1) * deltax); 
  }

  integral *= deltax;
  
  intrg -> answer = integral;
}
 #endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE
// and #endif to enable particial credits

#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
  // Declare intrg
  Integration intrg;

  // open the input file name for reading
  FILE * fpin = fopen(infilename, "r");


  // if fopen fails, return false
  if (fpin == NULL)
  {
    return false;
  }


  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  if (fscanf(fpin, "%lf\n", &intrg.lowerlimit) != 1)
  {
    fclose(fpin);
    return false;
  }




  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  if (fscanf(fpin, "%lf\n", &intrg.upperlimit) != 1)
  {
    fclose(fpin);
    return false;
  }




  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  if (fscanf(fpin, "%d\n", &intrg.intervals) != 1)
  {
    fclose(fpin);
    return false;
  }




  // close the input file
  fclose(fpin);






  // open the output file for writing
  // if fopen fails, return false
  FILE * fpout = fopen(outfilename, "w");

  if (fpout == NULL)
  {
    return false;
  }




  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5
  funcptr funcs[] = {func1, func2, func3, func4, func5};



  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf
  for (int i = 0; i < 5; i++)
  {
    intrg.func = funcs[i];
    integrate(&intrg);

    // check the return value of fprintf. 
    // If it is less one one, close the output
    // file and return false
    if (fprintf(fpout, "%lf\n", intrg.answer) < 1)
    {
      fclose(fpout);
      return false;
    }
  }




  // after going through all functions in funcs
  // close the output file
  fclose(fpout);






  // if the function reaches here, return true
  return true;
}
#endif // RUN_INTEGRATE
