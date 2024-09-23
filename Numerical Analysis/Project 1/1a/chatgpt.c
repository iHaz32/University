/* 
CHAT GPT INPUT:

Write me a bisection method C code for this function: f(x) = 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12
Tolerance of 5 decimal digits.
Make it so it runs 2 times, one for interval [0,1.5] and one for interval [1.5,3]. Add loop counter for each of 2 times.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#define TOLERANCE 0.000005 // I added this

double f(double x) {
    return 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x * x * x + 20 * x * x - 26 * x + 12;
}

void bisection(double a, double b) {
    clock_t start, end; // I added this
    double cpu_time_used; // I added this
    start = clock(); // I added this

    double c, fa, fb, fc;
    int iteration = 0;

    do {
        iteration++;

        c = (a + b) / 2.0;
        fa = f(a);
        fb = f(b);
        fc = f(c);

        // Check if root is found
        if (fc == 0.0)
            break;

        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }
    } while (b - a > TOLERANCE);

    end = clock(); // I added this
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // I added this

    printf("Root is at: m = %lf\n", c); // I added this
    printf("f(m) = %lf\n", fc); // I added this
    printf("Loops: %d\n", iteration); // I added this
    printf("Execution time: %.20lf seconds\n", cpu_time_used); // I added this
    printf("---------------------\n"); // I added this
}

int main() {
    // First interval [0, 1.5]
    bisection(0, 1.5);

    // Second interval [1.5, 3]
    bisection(1.5, 3);

    return 0;
}