#include <stdio.h>

#include <time.h>

#include <math.h>

#define PI 3.14159265358979323846 // Defines mathematical pi

double f(double x) { // Calculates the value of f(x)
    return sin(x);
}

void simpsonMethod(double a, double b, int N) {
    clock_t start, end; // Calculates the start time of algorithm
    double cpu_time_used; // Calculates the start time of algorithm
    start = clock(); // Calculates the start time of algorithm

    double x, sum1 = 0, sum2 = 0, sum = 0, h = (b - a) / N; // Initialize variables
    for (int k = 1; k < N; k++) { // Calculates the xk and the two needed sums
        x = a + k * h;
        if (k % 2 == 0) {
            sum1 += f(x);
        } else {
            sum2 += f(x);
        }
    }

    double approximation = (h / 3) * ( f(a)+f(b) + 2*sum1 + 4*sum2 ); // Calculates the approximation

    end = clock(); // Calculates the end time of algorithm
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

    printf("Final approximation: %lf\n", approximation);
    printf("Execution time: %.20lf seconds\n", cpu_time_used);
    printf("---------------------\n");
}

int main() {

    int N = 10;
    double a = 0, b = PI/2; // Starting and final points
    simpsonMethod(a, b, N);  // Simpson method for the starting and final points

  return 0;
}