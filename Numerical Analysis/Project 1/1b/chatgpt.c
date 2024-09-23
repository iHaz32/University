/*
CHAT GPT INPUT:

Write me a Newton-Raphson method C code for this function: f(x) = 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12
Tolerance of 5 decimal digits.
Make it so it runs 2 times, one for x0=0 and one for x0=3. Add loop counter for each of 2 times.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#define TOLERANCE 0.000005 // I added this

// Function definition
double f(double x) {
    return 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12;
}

// Derivative of the function
double df(double x) {
    return 14 * x * exp(x - 2) + 2 * exp(x - 2) - 21* x * x + 40 * x - 26;  // I added this
}

// Newton-Raphson method
void newtonRaphson(double x0) {
    clock_t start, end; // I added this
    double cpu_time_used; // I added this
    start = clock(); // I added this

    double x = x0;
    int iteration = 0;

    do {
        x0 = x;

        if (f(x) == 0.0) {
            break;
        }

        x = x0 - f(x0) / df(x0);
        iteration++;
    } while (fabs(x - x0) > TOLERANCE);

    end = clock(); // I added this
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // I added this

    printf("Root is at: c = %lf\n", x); // I added this
    printf("f(c) = %lf\n", f(x)); // I added this
    printf("Loops: %d\n", iteration); // I added this
    printf("Execution time: %.20lf seconds\n", cpu_time_used); // I added this
    printf("---------------------\n"); // I added this
}

int main() {
    // Run for different initial values
    newtonRaphson(0);
    newtonRaphson(3);

    return 0;
}