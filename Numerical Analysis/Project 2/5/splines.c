#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

#define N 10
#define M 200
#define PI 3.14159265358979323846 // Defines mathematical pi

// Define a structure to hold the coefficients
typedef struct {
    long double *a;
    long double *b;
    long double *c;
    long double *d;
} Coefficients;

Coefficients* splines(long double *x_values, long double *y_values) {
    long double **A, *b; // Initialize matrices
    long double *dx, *dy; // Initialize x and y distances
    long double **P, **L, **U, *x, *y; // Initialize matrices for linear system solving

    // Initialize coefficients matrices
    long double *a_coefficients, *b_coefficients, *c_coefficients, *d_coefficients;
    Coefficients *coefficients;

    a_coefficients = (long double *)malloc((N-1) * sizeof(long double));
    b_coefficients = (long double *)malloc((N-1) * sizeof(long double));
    c_coefficients = (long double *)malloc((N-1) * sizeof(long double));
    d_coefficients = (long double *)malloc((N-1) * sizeof(long double));
    coefficients = (Coefficients*)malloc((N-1) * sizeof(Coefficients));

    A = (long double **)malloc(N * sizeof(long double *));
    P = (long double **)malloc(N * sizeof(long double *));
    L = (long double **)malloc(N * sizeof(long double *));
    U = (long double **)malloc(N * sizeof(long double *));
    for (int i = 0; i < N; i++) {
        A[i] = (long double *)malloc(N * sizeof(long double));
        P[i] = (long double *)malloc(N * sizeof(long double));
        L[i] = (long double *)malloc(N * sizeof(long double));
        U[i] = (long double *)malloc(N * sizeof(long double));
    }
    b = (long double *)malloc(N * sizeof(long double));
    x = (long double *)malloc(N * sizeof(long double));
    y = (long double *)malloc(N * sizeof(long double));
    dx = (long double *)malloc((N-1) * sizeof(long double));
    dy = (long double *)malloc((N-1) * sizeof(long double));

    // Initalize A b items as zero
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 0;
        }
        b[i] = 0;
    }

    // First and last elements of A diagonial are equal to 1
    A[0][0] = 1;
    A[N-1][N-1] = 1;

    // First and last elements of b are equal to 0
    b[0] = 0;
    b[N-1] = 0;

    // Calculate x and y distances
    for (int i = 0; i < N-1; i++) {
        dx[i] = x_values[i + 1] - x_values[i];
        dy[i] = y_values[i + 1] - y_values[i];
    }

    // Calculate A and b
    for (int i = 1; i < N-1; i++) {
        // Calculate A matrix
        A[i][i-1] = dx[i-1];
        A[i][i] = 2 * (dx[i-1] + dx[i]);
        A[i][i+1] = dx[i];

        // Calculate b vector
        b[i] = 3 * (dy[i] / dx[i] - dy[i-1] / dx[i-1]);
    }

    // Calculate a coefficients
    for (int i = 0; i < N-1; i++) {
        a_coefficients[i] = y_values[i];
    }

    // Calculate c coefficients
    c_coefficients = solve(P, A, L, U, b, y, x, N); // Solve Ac = b with already known PA = LU factorization method

    // Calculate b and d coefficients
    for (int i = 0; i < N-1; i++) {
        d_coefficients[i] = (c_coefficients[i+1] - c_coefficients[i]) / (3 * dx[i]);
        b_coefficients[i] = dy[i]/dx[i] - dx[i]/3 * (2 * c_coefficients[i] + c_coefficients[i+1]);
    }

    // Set the pointers in the structure to the coefficient arrays
    coefficients->a = a_coefficients;
    coefficients->b = b_coefficients;
    coefficients->c = c_coefficients;
    coefficients->d = d_coefficients;

    // Free memory allocated
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(P[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(P);
    free(L);
    free(U);
    free(dx);
    free(dy);

    // Return all of the coefficients
    return coefficients;
}

long double calculateWithSplines(Coefficients* coefficients, long double x, long double *x_values) {
    // Extract coefficients from the structure
    long double *a = coefficients->a;
    long double *b = coefficients->b;
    long double *c = coefficients->c;
    long double *d = coefficients->d;

    // Find the interval in which x lies
    int interval = 0;
    while (x > x_values[interval + 1] && interval < N - 1) {
        interval++;
    }

    // Evaluate the cubic spline interpolation formula
    long double xi = x_values[interval];
    long double h = x - xi;
    return a[interval] + b[interval] * h + c[interval] * h * h + d[interval] * h * h * h;
}

int main() {
    long double x_values[N] = {-PI, -PI/4, -PI/6, -PI/8, 0, PI/10, PI/7, PI/5, PI/3, PI}; // Initialize known x values disparately
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

    Coefficients *coefficients = splines(x_values, y_values);

    for (int i = 0; i < M; i++) { // Calculate y approximations and errors
        y_approximations[i] = calculateWithSplines(coefficients, x_points[i], x_values); // y = s(x)
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
        long double approx = calculateWithSplines(coefficients, userValue, x_values);; // Approximation
        long double error = fabs(sin(userValue) - approx); // Error
        printf("For x=%Lf: Real=%Lf Approx=%Lf Error:=%.20Lf\n", (long double)userValue, (long double)sin(userValue), approx, error); // Output
    } else {
        // Input was not a valid double in [-pi , pi]
        printf("Invalid input. Please enter a valid double.\n"); // Error message
    }

    return 0;
}