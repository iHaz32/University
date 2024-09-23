/*
CHAT GPT INPUT:

Write me a custom secant method C code for this function: f(x) = 54 * x * x * x * x * x * x + 45 * x * x * x * x * x - 102 * x * x * x * x - 69 * x * x * x + 35 * x * x + 16 * x - 4
Tolerance of 5 decimal digits.
Ηοwever, new approximation x3 = x2 - (r*(r-q)*(x2-x1) + (1-r)*s*(x2-x0))/((q-1)*(r-1)*(s-1)) with q=fx0/fx1; , r=fx2/fx1; and s=fx2/fx0;
Run the algorithm 5 times.
1st time: x0=-2, x1=-1.9, x2=-1.8
2nd time: x0=-1, x1=-0.9, x2=-0.8
3rd time: x0=0, x1=0.1, x2=0.2
4th time: x0=0,4, x1=0.5, x2=0.6
5th time: x0=2, x1=2.1, x2=2.2
Make it run without iterations limit.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

#define TOLERANCE 0.000005 // I added this

double f(double x) {
    return 54 * pow(x, 6) + 45 * pow(x, 5) - 102 * pow(x, 4) - 69 * pow(x, 3) + 35 * pow(x, 2) + 16 * x - 4;
}

double secantMethod(double x0, double x1, double x2) {
    clock_t start, end; // I added this
    double cpu_time_used; // I added this
    start = clock(); // I added this

    int iterations = 0;
    double x3, q, r, s;

    do {
        iterations++;

        q = f(x0) / f(x1);
        r = f(x2) / f(x1);
        s = f(x2) / f(x0);

        x3 = x2 - (r * (r - q) * (x2 - x1) + (1 - r) * s * (x2 - x0)) / ((q - 1) * (r - 1) * (s - 1));

        if (fabs(x3 - x2) < TOLERANCE) {
            break;
        }

        if (f(x0)==0.0) {
            x3=x0;
            break;
        }

        if (f(x1)==0.0) {
            x3=x1;
            break;
        }

        if (f(x2)==0.0) {
            x3=x2;
            break;
        }

        x0 = x1;
        x1 = x2;
        x2 = x3;

    } while (1);

    end = clock(); // I added this
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // I added this

    printf("Root is at: m = %lf\n", x3); // I added this
    printf("f(m) = %lf\n", f(x3)); // I added this
    printf("Loops: %d\n", iterations); // I added this
    printf("Execution time: %.20lf seconds\n", cpu_time_used); // I added this
    printf("---------------------\n"); // I added this
}

int main() {

    // 1st time
    secantMethod(-2, -1.9, -1.8);

    // 2nd time
    secantMethod(-1, -0.9, -0.8);

    // 3rd time
    secantMethod(0, 0.1, 0.2);

    // 4th time
    secantMethod(0.4, 0.5, 0.6);

    // 5th time
    secantMethod(2, 2.1, 2.2);

    return 0;
}
