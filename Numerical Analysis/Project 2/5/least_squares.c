#include <stdio.h>
#include <math.h>

#define N 10
#define M 200
#define PI 3.14159265358979323846 // Defines mathematical pi

// Define a structure to hold the coefficients
typedef struct {
    long double m;
    long double b;
} Coefficients;

Coefficients leastSquares(long double *xValues, long double *yValues) {
    // Initialize sums and coefficients
    long double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, m, b;
    Coefficients coefficients;

    // Calculate sums
    for (int i = 0; i < N; i++) {
        sumX += xValues[i];
        sumY += yValues[i];
        sumXY += xValues[i] * yValues[i];
        sumX2 += xValues[i] * xValues[i];
    }

    // Calculate the coefficients m and b of y = mx + b line
    m = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    b = (sumY - m * sumX) / N;

    coefficients.m = m;
    coefficients.b = b;

    return coefficients;
}

long double calculateWithLeastSquares(long double x, Coefficients coefficients) {
    return coefficients.m * x + coefficients.b;
}

int main() {

    long double x_values[N] = {-PI/2, -PI/4, -PI/6, -PI/8, 0, PI/10, PI/7, PI/5, PI/3, PI}; // Initialize known x values disparately
    long double y_values[N]; // Initialize y real values
    Coefficients coefficients; // Initialize coefficients

    long double x_points[M]; // Initialize unknown x values
    long double y_approximations[M]; // Initialize y approximations
    long double errors[M]; // Initialize errors

    for (int i = 0; i < N; i++) { // Calculate y real values
        y_values[i] = sin(x_values[i]); // y = sin(x) - real values
    }

    for (int i = 0; i < M; i++) { // Calculate x points symmetrically
        x_points[i] = -PI + (2 * PI * i) / (M - 1);
    }

    coefficients = leastSquares(x_values, y_values); // Calculate coefficients


    for (int i = 0; i < M; i++) { // Calculate y approximations and errors
        y_approximations[i] = calculateWithLeastSquares(x_points[i], coefficients); // y = mx + b
        errors[i] = fabs(sin(x_points[i]) - y_approximations[i]); // Error
    }

    for (int i = 0; i < M; i++) { // Output
        printf("For x=%Lf: Real=%Lf Approx=%Lf Error:=%.20Lf\n", x_points[i], (long double)sin(x_points[i]), y_approximations[i], errors[i]);
    }

    // long double sum = 0;
    // for (int i = 0; i < M; i++) {
    //     sum += errors[i] * errors[i];
    // }
    // sum = sqrt(sum);
    // printf("Norm = %.20Lf\n", sum);

    double userValue; // Initialize user value
    printf("\nEnter number in [-3,14 , 3,14]: "); // Scan user value

    // Read the double value from the user
    if (scanf("%lf", &userValue) == 1 && userValue >= -PI && userValue <= PI) {
        // Input was successfully read
        long double approx = calculateWithLeastSquares(userValue, coefficients); // Approximation
        long double error = fabs(sin(userValue) - approx); // Error
        printf("For x=%Lf: Real=%Lf Approx=%Lf Error:=%.20Lf\n", (long double)userValue, (long double)sin(userValue), approx, error); // Output
    } else {
        // Input was not a valid double in [-pi , pi]
        printf("Invalid input. Please enter a valid double.\n"); // Error message
    }

    return 0;
}