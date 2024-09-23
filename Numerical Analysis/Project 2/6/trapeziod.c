#include <stdio.h>

#include <time.h>

#include <math.h>

#define PI 3.14159265358979323846 // Defines mathematical pi

double f(double x) { // Calculates the value of f(x)
    return sin(x);
}

void trapezoidalMethod(double a, double b, int N) {
    clock_t start, end; // Calculates the start time of algorithm
    double cpu_time_used; // Calculates the start time of algorithm
    start = clock(); // Calculates the start time of algorithm

    double x, sum = 0, h = (b - a) / N; // Initialize variables
    for (int k = 1; k < N; k++) { // Calculates the xk and the sum from k = 1 to k = n - 1 of f(xk)
        x = a + k * h;
        sum += f(x);
    }

    double approximation = (h / 2) * ( f(a)+f(b) + 2*sum ); // Calculates the approximation

    end = clock(); // Calculates the end time of algorithm
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

    printf("Final approximation: %lf\n", approximation);
    printf("Execution time: %.20lf seconds\n", cpu_time_used);
    printf("---------------------\n");
}

int main() {

    int N = 10; // Subtrapeziods size, 10 subtrapeziods for 11 points
    double a = 0, b = PI/2; // Starting and final points
    trapezoidalMethod(a, b, N);  // Trapezoidal method for the starting and final points

  return 0;
}