#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

void readMatrix(double **X, int n) {
    printf("Read A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i+1, j+1);
            scanf("%lf", &X[i][j]);
        }
    }
}

void writeMatrix(double **X, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", X[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void copy(double **X, double **Y, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Y[i][j] = X[i][j];
        }
    }
}

double** cholesky(double **A, double **L, int n) {
    double sum;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i <= k; i++) {
            sum = 0;
            if (k == i) { // For diagonal elements
                for (int j = 0; j < k; j++) {
                    sum += L[k][j] * L[k][j];
                }
                L[k][k] = sqrt(A[k][k] - sum);
            } else {
                for (int j = 0; j < i; j++) {
                    sum += L[i][j] * L[k][j];
                }

                if (L[i][i] != 0) {
                    L[k][i] = (A[k][i] - sum) / L[i][i];
                }
            }
        }
    }
    return L;
}

double** transpose(double **L, double **LTranspose, int n) {
    copy(L, LTranspose, n);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < i; j++) {
            LTranspose[i][j] = 0; // Extra
            L[j][i] = 0; // Extra
            LTranspose[j][i] = L[i][j];
        }
    }
    return LTranspose;
}

int main() {
    int n; // Matrix size
    double **A, **L, **LTranspose;

    printf("Give A matrix size: ");
    scanf("%d", &n);

    // Allocate memory for matrices
    A = (double **)malloc(n * sizeof(double *));
    L = (double **)malloc(n * sizeof(double *));
    LTranspose = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)malloc(n * sizeof(double));
        LTranspose[i] = (double *)malloc(n * sizeof(double));
    }

    readMatrix(A, n);

    // For static declaration
    // A[0][0] = 4; A[0][1] = 12; A[0][2] = -16;
    // A[1][0] = 12; A[1][1] = 37; A[1][2] = -43;
    // A[2][0] = -16; A[2][1] = -43; A[2][2] = 98;

    L = cholesky(A, L, n);
    LTranspose = transpose(L, LTranspose, n);
    printf("L:\n");
    writeMatrix(L, n);
    printf("L Transpose:\n");
    writeMatrix(LTranspose, n);

    // Free memory of matrices
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(L[i]);
        free(LTranspose[i]);
    }
    free(A);
    free(L);
    free(LTranspose);

  return 0;
}