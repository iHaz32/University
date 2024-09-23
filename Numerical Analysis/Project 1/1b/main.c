#include <stdio.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.000005 // Defines a 5 decimal digits tolerance

double f(double x) { // Calculates the value of f(x)
  return 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12;
}

double derivative(double x) { // Calculates the derivative value of f(x)
  return 14 * x * exp(x - 2) + 2 * exp(x - 2) - 21* x * x + 40 * x - 26;
}

void newtonRaphsonMethod(double a) {
  clock_t start, end; // Calculates the start time of algorithm
  double cpu_time_used; // Calculates the start time of algorithm
  start = clock(); // Calculates the start time of algorithm

  int loopCount = 0;
  double r, previous;

  r=a;

  do {
    loopCount++;

    if (f(previous) == 0.0) {
      break;
    }
    
    previous = r; // Stores previous value

    //printf("%lf\n", previous); // For convergence check

    r = previous - f(previous)/derivative(previous); // Calculates next value

  } while (fabs(previous - r) >= TOLERANCE); // Checks if the approximation is enough

  end = clock(); // Calculates the end time of algorithm
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

  printf("Root is at: r = %lf\n", r);
  printf("f(r) = %lf\n", f(r));
  printf("Loops: %d\n", loopCount);
  printf("Execution time: %.20lf seconds\n", cpu_time_used);
  printf("---------------------\n");
}

int main() {
  newtonRaphsonMethod(0); // Newton-Raphson in for n0 = 0
  newtonRaphsonMethod(3); // Newton-Raphson in for n0 = 1.5

  return 0;
}