#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.000005 // Defines a 5 decimal digits tolerance

double f(double x) { // Calculates the value of f(x)
  return 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4;
}

void bisectionMethod(double a, double b) {
  clock_t start, end; // Calculates the start time of bisection algorithm
  double cpu_time_used; // Calculates the start time of bisection algorithm
  start = clock(); // Calculates the start time of bisection algorithm

  int loopCount = 0;
  double r, fa, fb, fr;

  do {
    loopCount++;

    r = ((double)rand() / RAND_MAX) * (b - a) + a;  // Generates a random number of I=[a,b] as a root approximation

    fa = f(a);  // Calculates f(a) one time to avoid multiple funtion calling
    fb = f(b);  // Calculates f(b) one time to avoid multiple funtion calling
    fr = f(r);  // Calculates f(c) one time to avoid multiple funtion calling

    if (fabs(fr) >= TOLERANCE) { // Checks if the approximation is enough to avoid useless operations
      if (fa * fr < 0) { // Defines new interval depends on signs
        b = r;
      } else if (fb * fr < 0) {
        a = r;
      }
    } else {
      break;
    }

  } while (b - a >= TOLERANCE); // Checks if the approximation is enough

  end = clock(); // Calculates the end time of bisection algorithm
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of bisection algorithm

  printf("Root is at: r = %lf\n", r);
  printf("f(r) = %lf\n", fr);
  printf("Loops: %d\n", loopCount);
  printf("Execution time: %.20lf seconds\n", cpu_time_used);
  printf("---------------------\n");
}

int main() {
  srand((unsigned int)time(NULL)); // Seeds the random number generator with the current time

  bisectionMethod(-2, -1); // Bisection for I=[-2,-1]
  bisectionMethod(-1, 0); // Bisection for I=[-1,0]
  bisectionMethod(0, 0.4); // Bisection for I=[0,0.4]
  bisectionMethod(0.4, 1); // Bisection for I=[0.4,1]
  bisectionMethod(1, 1.2); // Bisection for I=[1,1.2]

  return 0;
}