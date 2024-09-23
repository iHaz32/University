/* 
CHAT GPT INPUT:

Write me a Newton-Raphson method C code for this function: f(x) = 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4
Tolerance of 5 decimal digits.
Make it so it runs 5 times, one for n0=-2, n0=-1, n0=0, n0=0.4, n0=1.
New approximation point = x - (1 / ( f`(x)/f(x) - 0.5*f``(x)/f`(x) ) )
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#define TOLERANCE 0.000005 // I added this

// Function definition
double f(double x) {
    return 54 * pow(x, 6) + 45 * pow(x, 5) - 102 * pow(x, 4) - 69 * pow(x, 3) + 35 * pow(x, 2) + 16 * x - 4;
}

// First derivative of the function
double df(double x) {
    return 324 * pow(x, 5) + 225 * pow(x, 4) - 408 * pow(x, 3) - 207 * pow(x, 2) + 70 * x + 16;
}

// Second derivative of the function
double d2f(double x) {
    return 1620 * pow(x, 4) + 900 * pow(x, 3) - 1224 * pow(x, 2) - 414 * x + 70;
}

// Newton-Raphson method with modified formula
void newtonRaphson(double x0) {
    clock_t start, end; // I added this
    double cpu_time_used; // I added this
    start = clock(); // I added this

    int iteration = 0;
    double x = x0;

    do {
        x0 = x;

        if (f(x) == 0.0) {
            break;
        }

        x = x0 - (1 / ((df(x0) / f(x0)) - 0.5 * (d2f(x0) / df(x0))));
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
    newtonRaphson(-2);
    newtonRaphson(-1);
    newtonRaphson(0);
    newtonRaphson(0.4);
    newtonRaphson(1);

    return 0;
}

/* 
COMMENTS ABOUT THE TWO CODES:

Chat GPT code has some differences. It has different variable names, amount of code lines and amount of comments.
Had to provide him more details about derivatives and tolerance because it was wrong at first. 
*/