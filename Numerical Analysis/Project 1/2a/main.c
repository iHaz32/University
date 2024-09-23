/*
From the graph of f(x) in MATLAB, it is has 1 root between each of the intervals [-2,-1], [-1,0], [0, 0.5], [0.5, 1], [1, 1.2].
So I decided to run the bisection algorithm for each interval.
*/

#include <stdio.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.000005 // Defines a 5 decimal digits tolerance

double f(double x) { // Calculates the value of f(x)
  return 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4;
}

double derivative(double x) { // Calculates the derivative value of f(x)
  return 324 * x * x * x * x * x + 225 * x * x * x * x - 408 * x * x * x - 207 * x * x + 70 * x + 16;
}

double secondDerivative(double x) { // Calculates the derivative value of f(x)
  return 1620 * x * x * x * x + 900 * x * x * x - 1224 * x * x - 414 * x + 70;
}

void newtonRaphsonMethod(double a) {
  clock_t start, end; // Calculates the start time of Newton-Raphson algorithm
  double cpu_time_used; // Calculates the start time of Newton-Raphson algorithm
  start = clock(); // Calculates the start time of Newton-Raphson algorithm

  int loopCount = 0;
  double r, previous, fprevious, derPrev, secondDerPrev;

  r = a;

  do {
    loopCount++;

    if (f(previous) == 0.0) {
      break;
    }

    previous = r; // Stores previous value
    fprevious = f(r);
    derPrev = derivative(previous);
    secondDerPrev = secondDerivative(previous);
    
    r = previous - (1.0 / ((derPrev / fprevious) - (0.5 * secondDerPrev / derPrev))); // Calculates next value

  } while (fabs(previous - r) >= TOLERANCE); // Checks if the approximation is enough

  end = clock(); // Calculates the end time of bisection algorithm
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of bisection algorithm

  printf("Root is at: r = %lf\n", r);
  printf("f(r) = %lf\n", f(r));
  printf("Loops: %d\n", loopCount);
  printf("Execution time: %.20lf seconds\n", cpu_time_used);
  printf("---------------------\n");
}

int main() {
  newtonRaphsonMethod(-2); // Newton-Raphson in for n0 = -2 because f(-2)*f''(-2) > 0
  newtonRaphsonMethod(-1); // Newton-Raphson in for n0 = -1 because f(-1)*f''(-1) > 0
  newtonRaphsonMethod(0); // Newton-Raphson in for n0 = 0 because f(0)*f''(0) > 0
  newtonRaphsonMethod(0.4); // Newton-Raphson in for n0 = 0.4 because f(0.4)*f''(0.4) > 0,  f`(x) = 0 near 0.3
  newtonRaphsonMethod(1); // Newton-Raphson in for n0 = 1 because f(1)*f''(1) > 0

  return 0;
}