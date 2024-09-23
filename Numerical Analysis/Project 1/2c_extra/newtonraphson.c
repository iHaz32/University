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
  newtonRaphsonMethod(-2);
  newtonRaphsonMethod(-1);
  newtonRaphsonMethod(0);
  newtonRaphsonMethod(0.4);
  newtonRaphsonMethod(1);

  return 0;
}