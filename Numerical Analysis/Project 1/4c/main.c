#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#define N 15 // Matrix size
#define Q 0.15 // Probability q
#define TOLERANCE 0.00000000005 // Defines a 10 decimal digits tolerance

void writeMatrix(double **A, int n) {
    printf("G Matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.3lf ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void writeVector(double *x, int n) {
    printf("b Approximation: \n|");
    for (int i = 0; i < n; i++) {
        printf(" b[%d] = %.7lf |", i, x[i]);
    }
    printf("\n\n");
}

void initializeA(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
        }
    }

    A[0][1] = 1, A[0][8] = 1, A[1][4] = 1, A[1][6] = 1, A[2][1] = 1, A[2][5] = 1, A[2][7] = 1, A[3][2] = 1, A[3][11] = 1, A[4][0] = 1, A[4][9] = 1, A[5][9] = 1, A[5][10] = 1, A[6][9] = 1, A[6][10] = 1, A[7][3] = 1, A[7][10] = 1, A[8][4] = 1, A[8][5] = 1, A[8][9] = 1, A[9][12] = 1, A[10][1] = 1, A[10][14] = 1, A[11][6] = 1, A[11][7] = 1, A[11][10] = 1, A[12][1] = 1; A[12][8] = 1, A[12][13] = 1, A[13][1] = 1, A[13][14] = 1, A[13][12] = 1, A[13][10] = 1, A[13][9] = 1, A[14][1] = 1, A[14][13] = 1, A[14][11] = 1;
    /*
    Removed: A[1][2] = 1;
    Added: A[10][1] = 1;
           A[12][1] = 1;
           A[13][1] = 1;
           A[14][1] = 1;
        
    */

}

double sumRow(double *row, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += row[i];
    }
    return sum;
}

void buildG(double **G, double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G[i][j] = Q/n + A[j][i]*(1-Q)/sumRow(A[j], n);
        }
    }
}

void* multiply(double **P, double *b, double *c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = 0;
        for (int j = 0; j < n; j++) {
            c[i] += P[i][j] * b[j];
        }
    }
}

double* multiply2(double l, double *b, double* c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = l * b[i];
    }
}

void copyVector(double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = x[i];
    }
}

double findFactor(double* x, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += x[i];
    }
    return sum;
}

void powerMethod(double **G, double *eigenVector, int n) {
    double *old, *new, *normalisedNew, factor, sub;
    new = (double *)malloc(n * sizeof(double));
    old = (double *)malloc(n * sizeof(double));
    normalisedNew = (double *)malloc(n * sizeof(double));
    copyVector(G[0], old, n); // Initalize the vector of the first column of G, as the beginning eigenvector approximation

    do {
        multiply(G, old, new, n);

        factor = findFactor(new, n);
        multiply2(1/factor, new, normalisedNew, n);

        sub = fabs(new[0] - old[0]);
        copyVector(new, old, n);

    } while (sub >= TOLERANCE);

    copyVector(normalisedNew, eigenVector, n);
    free(new);
    free(old);
    free(normalisedNew);
}

int main() {
    double **A, **G, *eigenVector;

    // Allocate memory for matrices
    A = (double **)malloc(N * sizeof(double *));
    G = (double **)malloc(N * sizeof(double *));
    eigenVector = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
        G[i] = (double *)malloc(N * sizeof(double));
    }

    initializeA(A, N);
    buildG(G, A, N);
    writeMatrix(G, N);
    powerMethod(G, eigenVector, N);

    writeVector(eigenVector, N);

    // Free memory of matrices
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(G[i]);
    }
    free(A);
    free(G);
    free(eigenVector);

  return 0;
}