#include <stdio.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.000005 // Defines a 5 decimal digits tolerance

double f(double x) { // Calculates the value of f(x)
  return 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4;
}

void secantMethod(double a, double b, double c) {
  clock_t start, end; // Calculates the start time of algorithm
  double cpu_time_used; // Calculates the start time of algorithm
  start = clock(); // Calculates the start time of algorithm

  int loopCount = 0;
  double x0=a, x1=b, x2=c, x3, fx0, fx1, fx2, fx3, q, r, s;

  do {
    loopCount++;

    fx0 = f(x0);
    fx1 = f(x1);
    fx2 = f(x2);

    if (fx0==0.0) {
      x3=x0;
      break;
    }

    if (fx1==0.0) {
      x3=x1;
      break;
    }

    if (fx2==0.0) {
      x3=x2;
      break;
    }

    q=fx0/fx1;
    r=fx2/fx1;
    s=fx2/fx0;

    x3 = x2 - (r*(r-q)*(x2-x1) + (1-r)*s*(x2-x0))/((q-1)*(r-1)*(s-1));

    if (fabs(x3-x2) < TOLERANCE) { // Checks if the approximation is enough
      break;
    }

    x0 = x1;
    x1 = x2;
    x2 = x3;
  } while (1); // Continues the loop

  end = clock(); // Calculates the end time of algorithm
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

  printf("Root is at: n = %lf\n", x3);
  printf("f(n) = %lf\n", f(x3));
  printf("Loops: %d\n", loopCount);
  printf("Execution time: %.20lf seconds\n", cpu_time_used);
  printf("---------------------\n");
}

int main() {
  secantMethod(-2, -1.9 , -1.8); // Secant for x0=-2, x1=-1.9, x2=-1.8
  secantMethod(-1, -0.9 , -0.8); // Secant for x0=-1, x1=-0.9, x2=-0.8
  secantMethod(0, 0.1 , 0.2); // Secant for x0=0, x1=0.1, x2=0.2
  secantMethod(0.4, 0.5 , 0.6); // Secant for x0=0.4, x1=0.5, x2=0.6
  secantMethod(2, 2.1 , 2.2); // Secant for x0=2, x1=2.1, x2=2.2

  return 0;
}