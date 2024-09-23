/*
CHAT GPT INPUT:

Write me a secant method C code for this function: f(x) = 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12
Tolerance of 5 decimal digits.
Make it so it runs 2 times, one for x0=0 and x1=1 and one for x0=1.5 and x1=1.7. Add loop counter for each of 2 times.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#define TOLERANCE 0.000005 // I added this

double f(double x) {
    return 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12;
}

void secant(double x0, double x1) {
    clock_t start, end; // I added this
    double cpu_time_used; // I added this
    start = clock(); // I added this

    double x2, f0, f1, f2;
    int iteration = 0;

    do {
        f0 = f(x0);
        f1 = f(x1);

        if (fabs(f1 - f0) < TOLERANCE) {
            break;
        }

        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        f2 = f(x2);

        if (f2==0.0) {
            break;
        }

        x0 = x1;
        x1 = x2;

        iteration++;
    } while (fabs(f1 - f0) >= TOLERANCE);

    end = clock(); // I added this
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // I added this

    printf("Root is at: n = %lf\n", x2); // I added this
    printf("f(n) = %lf\n", f2); // I added this
    printf("Loops: %d\n", iteration); // I added this
    printf("Execution time: %.20lf seconds\n", cpu_time_used); // I added this
    printf("---------------------\n"); // I added this
}

int main() {
    // Run for different initial values
    secant(0, 1);
    secant(1.5, 1.7);

    return 0;
}