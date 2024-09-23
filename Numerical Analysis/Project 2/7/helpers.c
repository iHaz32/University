#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void multiplyMatrices(long double **firstMatrix, long double **secondMatrix, long double **result, int rowFirst, int columnFirst, int rowSecond, int columnSecond) {
    // Initializing elements of matrix mult to 0
    for (int i = 0; i < rowFirst; ++i) {
        for (int j = 0; j < columnSecond; ++j) {
            result[i][j] = 0;
        }
    }
    
    // Multiplying firstMatrix and secondMatrix and storing the result in result
    for (int i = 0; i < rowFirst; ++i) {
        for (int j = 0; j < columnSecond; ++j) {
            for (int k = 0; k < columnFirst; ++k) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

void multiplyMV(long double **P, long double *b, long double *result, int rowFirst, int columnFirst, int rowSecond) {
    long double *c;
    c = (long double *)malloc(rowFirst * sizeof(long double));

    for (int i = 0; i < rowFirst; i++) {
        c[i] = 0;
        for (int j = 0; j < columnFirst; j++) {
            c[i] += P[i][j] * b[j];
        }
    }

    for (int i = 0; i < rowFirst; i++) {
        result[i] = c[i];
    }

    free(c);
}


void displayMatrix(long double **matrix, int row, int column) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            printf("%Lf  ", matrix[i][j]);
            if (j == column - 1)
                printf("\n");
        }
    }
}

void displayVector(long double *vector, int row) {
    for (int i = 0; i < row; ++i) {
            printf("%Lf  ", vector[i]);
    }
}

void swap(long double *x, long double *y, int n) {
    for (int i = 0; i < n; i++) {
        long double temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
}

void initializeIn(long double **X, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            X[i][j] = i==j ? 1 : 0;
        }
    }
}

void copy(long double **X, long double **Y, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Y[i][j] = X[i][j];
        }
    }
}

void transposeMatrix(long double **matrix, long double **result, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
}

void palu(long double **P, long double **A, long double **L, long double **U, int n) {
    initializeIn(P, n); // Initialize P as In matrix
    initializeIn(L, n); // Initialize L as In matrix
    copy(A, U, n); // Copy A elements into U matrix

    // Now we have a PA = LU with P=L=In and A=U

    // Loop through U columns
    for (int j = 0; j < n; j++) {
        // Choose as a pivot the max element of the current j column and swap its row with current row
        int maxElementRow = j; // Starting row has same index with current column because we want to start from a diagonal element
        for (int i = j + 1; i < n; i++) { // Iterate through the rest of the column elements
            if (fabs(U[i][j]) > fabs(U[maxElementRow][j])) { // If an absolutely bigger element is found assign its row as the maxElementRow
                maxElementRow = i;
            }
        }

        if (U[maxElementRow][j] == 0) continue; // All elements of column are zero and we do not have to do anything

        if (maxElementRow != j) { // If a new maxElementRow is found
            for (int i = j; i < n; i++) { // Swap the rest of its row with the current j row
                long double temp = U[j][i];
                U[j][i] = U[maxElementRow][i];
                U[maxElementRow][i] = temp;
            }

            swap(P[j], P[maxElementRow], n); // Also swap the rows in P matrix
        
            for (int i = 0; i < j; i++) { // Also swap all the essential elements the rows in L matrix
                long double temp = L[j][i];
                L[j][i] = L[maxElementRow][i];
                L[maxElementRow][i] = temp;
            }
        }

        // Iterate through the remaining rows
        for (int i = j + 1; i < n; i++) {
            if (U[i][j] == 0) continue;
             
            if (U[j][j] != 0) { // If element is not zero, which will never be, but just in case it is getting checked
                long double factor = U[i][j] / U[j][j];
                L[i][j] = factor;
                U[i][j] = 0;
                for (int k = j + 1; k < n; k++) { // Substract a value from the whole row
                    U[i][k] -= factor * U[j][k];
                }
            }
        }
    }
}

void solveY(long double **L, long double *y, long double *b, int n) {
    y[0] = b[0]; // Find y[0] immidiately and use it to find the others
    for (int i = 1; i < n; i++) {
        long double factor = 0;
        for (int j = 0; j < i; j++) {
            factor += L[i][j] * y[j];
        }
        y[i] = b[i] - factor;
    }
}

void solveX(long double **U, long double *x, long double *y, int n) {
    x[n-1] = y[n-1] / U[n-1][n-1]; // Find x[n-1] immidiately and use it to find the others
    for (int i=n-2; i >= 0; i--) {
        long double factor = 0;
        for (int j = n-1; j > i; j--) {
            factor += U[i][j] * x[j];
        }
        x[i] = (y[i] - factor) / U[i][i];
    }
}

long double* solve(long double **P, long double **A, long double **L, long double **U, long double *b, long double *y, long double *x, int n) {

    palu(P, A, L, U, n); // Run PA=LU
    multiplyMV(P, b, b, n, n, n); // b = Pb
    solveY(L, y, b, n); // Ly = b with current b = Pb
    solveX(U, x, y, n); // Ux = y

    return x;
}