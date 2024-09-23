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

// For debugging
void writeMatrix(double **X, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", X[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void readVector(double *x, int n) {
    printf("Read A:\n");
    for (int i = 0; i < n; i++) {
        printf("b[%d]: ", i+1);
        scanf("%lf", &x[i]);
    }
}

void writeVector(double *x, int n) {
    printf("Solutions: \n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %lf |", i, x[i]);
    }
    printf("\n\n");
}

void swap(double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        double temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
}

void initializeIn(double **X, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            X[i][j] = i==j ? 1 : 0;
        }
    }
}

void copy(double **X, double **Y, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Y[i][j] = X[i][j];
        }
    }
}

void multiply(double **P, double *b, int n) {
    double *c;
    c = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        c[i] = 0;
        for (int j = 0; j < n; j++) {
            c[i] += P[i][j] * b[j];
        }
    }
     for (int i = 0; i < n; i++) {
        b[i] = c[i];
    }
    free(c);
}

void palu(double **P, double **A, double **L, double **U, int n) {
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
                double temp = U[j][i];
                U[j][i] = U[maxElementRow][i];
                U[maxElementRow][i] = temp;
            }

            swap(P[j], P[maxElementRow], n); // Also swap the rows in P matrix
        
            for (int i = 0; i < j; i++) { // Also swap all the essential elements the rows in L matrix
                double temp = L[j][i];
                L[j][i] = L[maxElementRow][i];
                L[maxElementRow][i] = temp;
            }
        }

        // Iterate through the remaining rows
        for (int i = j + 1; i < n; i++) {
            if (U[i][j] == 0) continue;
             
            if (U[j][j] != 0) { // If element is not zero, which will never be, but just in case it is getting checked
                double factor = U[i][j] / U[j][j];
                L[i][j] = factor;
                U[i][j] = 0;
                for (int k = j + 1; k < n; k++) { // Substract a value from the whole row
                    U[i][k] -= factor * U[j][k];
                }
            }
        }
    }
}

void solveY(double **L, double *y, double *b, int n) {
    y[0] = b[0]; // Find y[0] immidiately and use it to find the others
    for (int i = 1; i < n; i++) {
        double factor = 0;
        for (int j = 0; j < i; j++) {
            factor += L[i][j] * y[j];
        }
        y[i] = b[i] - factor;
    }
}

void solveX(double **U, double *x, double *y, int n) {
    x[n-1] = y[n-1] / U[n-1][n-1]; // Find x[n-1] immidiately and use it to find the others
    for (int i=n-2; i >= 0; i--) {
        double factor = 0;
        for (int j = n-1; j > i; j--) {
            factor += U[i][j] * x[j];
        }
        x[i] = (y[i] - factor) / U[i][i];
    }
}

double* solve(double **P, double **A, double **L, double **U, double *b, double *y, double *x, int n) {    
    clock_t start, end; // Calculates the start time of algorithm
    double cpu_time_used; // Calculates the start time of algorithm
    start = clock(); // Calculates the start time of algorithm

    palu(P, A, L, U, n); // Run PA=LU
    multiply(P, b, n); // b = Pb
    solveY(L, y, b, n); // Ly = b with current b = Pb
    solveX(U, x, y, n); // Ux = y

    end = clock(); // Calculates the end time of algorithm
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculates the end time of algorithm

    printf("Execution time: %.20lf seconds\n", cpu_time_used);

    return x;
}

int main() {
    int n; // Matrix size
    double **A, **P, **L, **U, *b, *y, *x;

    printf("Give A matrix size: ");
    scanf("%d", &n);

    // Allocate memory for matrices
    A = (double **)malloc(n * sizeof(double *));
    P = (double **)malloc(n * sizeof(double *));
    L = (double **)malloc(n * sizeof(double *));
    U = (double **)malloc(n * sizeof(double *));
    b = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        P[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
    }

    readMatrix(A, n);
    readVector(b, n);

    // For static declaration
    // A[0][0] = -9; A[0][1] = 7; A[0][2] = 1;
    // A[1][0] = 3; A[1][1] = -2; A[1][2] = 1;
    // A[2][0] = 6; A[2][1] = 1; A[2][2] = 27;
    // b[0] = 0;
    // b[1] = -3;
    // b[2] = -1;

    x = solve(P,A,L,U,b,y,x,n); // Solve linear system with PA = LU method
    writeVector(x, n); // Print solution x

    // Free memory of matrices
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(P[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(P);
    free(L);
    free(U);
    free(b);
    free(y);
    free(x);

  return 0;
}