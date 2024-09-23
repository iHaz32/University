#include <stdio.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.000005 // Defines a 5 decimal digits tolerance

double f(double x) { // Calculates the value of f(x)
  return 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4;
}

void secantMethod(double a, double b) {
  clock_t start, end; // Calculates the start time of algorithm
  double cpu_time_used; // Calculates the start time of algorithm
  start = clock(); // Calculates the start time of algorithm

  int loopCount = 0;
  double previous = a, current = b, next, fprevious, fcurrent, fnext;

  do {
    loopCount++;

    fprevious = f(previous);
    fcurrent = f(current);

    if (fprevious==0.0) {
      next=previous;
      break;
    }

    if (fcurrent==0.0) {
      next=current;
      break;
    }

    next = current - ((double) fcurrent * (current - previous) / (fcurrent - fprevious));
    fnext = f(next);

    if (fabs(current-previous) < TOLERANCE) { // Checks if the approximation is enough
      break;
    }

    previous = current;
    current = next;
  } while (1); // Continues the loop

  end = clock(); // Calculates the end time of algorithm
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

  printf("Root is at: n = %lf\n", next);
  printf("f(n) = %lf\n", fnext);
  printf("Loops: %d\n", loopCount);
  printf("Execution time: %.20lf seconds\n", cpu_time_used);
  printf("---------------------\n");
}

int main() {
  secantMethod(-1.9 , -1.8);
  secantMethod(-0.9 , -0.8);
  secantMethod(0.1 , 0.2);
  secantMethod(0.5 , 0.6);
  secantMethod(2.1 , 2.2);

  return 0;
}