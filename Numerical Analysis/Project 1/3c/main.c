#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#define TOLERANCE 0.00005 // Defines a 4 decimal digits tolerance

void writeVector(double *x, int n) {
    printf("Solutions: \n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %lf |", i, x[i]);
    }
    printf("\n\n");
}

void copyVector(double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = x[i];
    }
}

void initializeA(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                A[i][i] = 5;
                if (i + 1 < n) {
                    A[i + 1][i] = -2;
                    A[i][i + 1] = -2;
                }
            } else {
                if (i!=j+1 && i!=j-1) {
                    A[i][j] = 0;
                }

            }
        }
    }
}

void initializeX(double *x, int n) {
    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }
}

void initializeB(double *b, int n) {
    b[0] = 3;
    for (int i = 1; i < n-1; i++) {
        b[i] = 1;
    }
    b[n-1] = 3;
}

double* substract(double *x, double *y, double *z, int n) {
    for (int i = 0; i < n; i++) {
        z[i] = x[i] - y[i];
    }
    return z;
}

double calculateInfinityNorm(double *x, int n) {
    double max = fabs(x[0]);
    for (int i = 1; i < n; i++) {
        if (fabs(x[i]) > max) {
            max = fabs(x[i]);
        }
    }
    return max;
}

double* gaussSeidel(double **A, double *x, double *b, double *prevX, int n) {
    double sum1, sum2;

    for (int i = 0; i < n; i++) {
        copyVector(x, prevX, n);
        sum1 = 0;
        for (int j = 0; j < i; j++) {
            sum1 += A[i][j] * x[j];
        }

        sum2 = 0;
        for (int j = i + 1; j < n; j++) {
            sum2 += A[i][j] * prevX[j];
        }

        x[i] = 1/A[i][i] * (b[i] - sum1 - sum2);
    }

    return x;
}

int main() {
    int n; // Matrix size
    double **A, *x, *b, *prevX, *y, infinityNorm;

    printf("Give A matrix size: ");
    scanf("%d", &n);

    // Allocate memory for matrices
    A = (double **)malloc(n * sizeof(double *));
    x = (double *)malloc(n * sizeof(double));
    b = (double *)malloc(n * sizeof(double));
    prevX = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    initializeA(A, n);
    initializeX(x, n);
    initializeB(b, n);

    do {
        x = gaussSeidel(A, x, b, prevX, n);

        y = substract(x, prevX, y, n);
        infinityNorm = calculateInfinityNorm(y, n);
    } while (infinityNorm >= TOLERANCE);

    writeVector(x, n);

    // Free memory of matrices
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(b);
    free(prevX);
    free(y);

  return 0;
}