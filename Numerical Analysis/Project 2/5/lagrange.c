#include <stdio.h>
#include <math.h>

#define N 10
#define M 200
#define PI 3.14159265358979323846 // Defines mathematical pi

long double lagrange(long double x, long double *xValues, long double *yValues) {
    long double value, result = 0;

    for (int i = 0; i < N; i++) { // Calculate p(x) = y * L
        value = yValues[i]; // Set each term starting value with y
        for (int j = 0; j < N; j++) {
            if (i != j) {
                value *= (x - xValues[j]) / (xValues[i] - xValues[j]); // Calculate each fraction value and multiply it with y, except the fraction where i = j
            }
        }
        result += value; // Add each term value to result
    }

    return result;
}

int main() {

    long double x_values[N] = {-PI/2, -PI/4, -PI/6, -PI/8, 0, PI/10, PI/7, PI/5, PI/3, PI}; // Initialize known x values disparately
    long double y_values[N]; // Initialize y real values

    long double x_points[M]; // Initialize unknown x values
    long double y_approximations[M]; // Initialize y approximations
    long double errors[M]; // Initialize errors

    for (int i = 0; i < N; i++) { // Calculate y real values
        y_values[i] = sin(x_values[i]); // y = sin(x) - real values
    }

    for (int i = 0; i < M; i++) { // Calculate x points symmetrically
        x_points[i] = -PI + (2 * PI * i) / (M - 1);
    }

    for (int i = 0; i < M; i++) { // Calculate y approximations and errors
        y_approximations[i] = lagrange(x_points[i], x_values, y_values); // y = p(x)
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
        long double approx = lagrange(userValue, x_values, y_values); // Approximation
        long double error = fabs(sin(userValue) - approx); // Error
        printf("For x=%Lf: Real=%Lf Approx=%Lf Error:=%.20Lf\n", (long double)userValue, (long double)sin(userValue), approx, error); // Output
    } else {
        // Input was not a valid double in [-pi , pi]
        printf("Invalid input. Please enter a valid double.\n"); // Error message
    }

    return 0;
}