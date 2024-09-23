#include <stdio.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.000005 // Defines a 5 decimal digits tolerance

double f(double x) { // Calculates the value of f(x)
  return 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4;
}

void bisectionMethod(double a, double b) {
  clock_t start, end; // Calculates the start time of algorithm
  double cpu_time_used; // Calculates the start time of algorithm
  start = clock(); // Calculates the start time of algorithm

  int loopCount = 0;
  double m, fa, fb, fm;

  do {
    loopCount++;

    m = (a + b) / 2.0; // Calculates the median of interval as a root approximation
    fa = f(a); // Calculates f(a) one time to avoid multiple funtion calling
    fb = f(b); // Calculates f(b) one time to avoid multiple funtion calling
    fm = f(m); // Calculates f(c) one time to avoid multiple funtion calling

    if (fm != 0.0) { // Checks if root is already found to avoid useless operations
      if (fa * fm < 0) { // Defines new interval depends on signs
        b = m;
      } else {
        a = m;
      }
    } else {
      break;
    }

  } while (b - a >= TOLERANCE); // Checks if the approximation is enough

  end = clock(); // Calculates the end time of algorithm
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

  printf("Root is at: m = %lf\n", m);
  printf("f(m) = %lf\n", fm);
  printf("Loops: %d\n", loopCount);
  printf("Execution time: %.20lf seconds\n", cpu_time_used);
  printf("---------------------\n");
}

int main() {
  bisectionMethod(-2, -1);
  bisectionMethod(-1, 0);
  bisectionMethod(0, 0.4);
  bisectionMethod(0.4, 1);
  bisectionMethod(1, 1.2);

  return 0;
}