#include "hw2.h"
double integrate1(Range rng)
{
    double deltax = (rng.upperlimit - rng.lowerlimit) / rng.intervals;

    double integral = 0;

    for (int n = 1; n <= rng.intervals; n++)
    {
        integral += func(rng.lowerlimit + (n - 1) * deltax); 
    }

    integral *= deltax;

    return integral;
}

void integrate2(RangeAnswer * rngans)
{
    rngans -> answer = integrate1(rngans -> rng);
}
