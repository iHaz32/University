/* 
CHAT GPT INPUT:

Write me a bisection method C code for this function: f(x) = 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4
Tolerance of 5 decimal digits.
Make it so it runs 5 times, one for interval [-2,-1], one for interval [-1,0], one for interval [0,0.4], one for [0.4, 1] and one for [1,1.2]. Add loop counter for each of 5 times.
Make it so the root approximation each time is not the median, but a random variable between a and b, borders of interval.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define TOLERANCE 0.000005 // I added this

double f(double x) {
    return 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4;
}

double randomDouble(double a, double b) {
    return ((double)rand() / RAND_MAX) * (b - a) + a;
}

void bisection(double a, double b) {
    clock_t start, end; // I added this
    double cpu_time_used; // I added this
    start = clock(); // I added this

    double c, fa, fb, fc;
    int iteration = 0;

    do {
        c = randomDouble(a, b); // Use randomDouble to get a random value between a and b
        fa = f(a);
        fb = f(b);
        fc = f(c);

        if (fc == 0.0) {
            break;
        }

        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }

        iteration++;
    } while (b - a > TOLERANCE);

    end = clock(); // I added this
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // I added this

    printf("Root is at: m = %lf\n", c); // I added this
    printf("f(m) = %lf\n", fc); // I added this
    printf("Loops: %d\n", iteration); // I added this
    printf("Execution time: %.20lf seconds\n", cpu_time_used); // I added this
    printf("---------------------\n"); // I added this
}

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // First interval [-2, -1]
    bisection(-2, -1);
    // First interval [-1, 0]
    bisection(-1, 0);
    // Second interval [0, 0.4]
    bisection(0, 0.4);
    // Third interval [0.4, 1]
    bisection(0.4, 1);
    // Fourth interval [1, 1.2]
    bisection(1, 1.2);

    return 0;
}

/* 
COMMENTS ABOUT THE TWO CODES:

Chat GPT code is similar with mine. There are small differences, such as variable names, amount of code lines and amount of comments.
However, in line 41 there is logical error which makes second run never end.
*/