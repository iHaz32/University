#include <stdio.h>
#include <stdlib.h>
#include "ymd_converter.h"
#include "helpers.h"

#define N 10

void approx(long double *a, long double x, const char* date, char* coinName) {
    long double approx = a[0] + a[1]*x + a[2]*x*x + a[3]*x*x*x + a[4]*x*x*x*x;
    printf("\nApproximation of %s for %s is: %Lf", coinName, date, approx);
}

int main() {
    const char *dateStrings[] = {"2023-11-17", "2023-11-18", "2023-11-19", "2023-11-20", "2023-11-21", "2023-11-22", "2023-11-23", "2023-11-24", "2023-11-25", "2023-11-26"};
    const long double yXPRValues[] = {0.613717, 0.611189, 0.627499, 0.612842, 0.580462, 0.611899, 0.620242, 0.621881, 0.623444, 0.616819};
    const long double yETHValues[] = {1961.28, 1963.29, 2013.20, 2022.24, 1937.07, 2064.43, 2062.21, 2081.15, 2084.41, 2063.29};

    long double xValues[N];
    for (int i = 0; i < N; i++) {
        xValues[i] = YMD_to_time(dateStrings[i]) / (double)100000000; // Convert dates to integers and store them as the x values
    }

    // for (int i = 0; i < N; i++) {
    //     printf("f(%Lf) = %Lf (%s)\n", xValues[i], yXPRValues[i], dateStrings[i]);
    // }
    // printf("\n\n");


    long double **A, **AT, **ATA, **P, **L, **U, *b, *b2, *ATb, *ATb2, *y, *y2, *x, *x2;

    // Allocate memory for matrices
    A = (long double **)malloc(N * sizeof(long double *));
    for (int i = 0; i < N; i++) {
        A[i] = (long double *)malloc(5 * sizeof(long double));
    }

    AT = (long double **)malloc(5 * sizeof(long double *));
    for (int i = 0; i < 5; i++) {
        AT[i] = (long double *)malloc(N * sizeof(long double));
    }

    b = (long double *)malloc(N * sizeof(long double));
    b2 = (long double *)malloc(N * sizeof(long double));
    ATb = (long double *)malloc(5 * sizeof(long double));
    ATb2 = (long double *)malloc(5 * sizeof(long double));

    ATA = (long double **)malloc(5 * sizeof(long double *));
    P = (long double **)malloc(5 * sizeof(long double *));
    L = (long double **)malloc(5 * sizeof(long double *));
    U = (long double **)malloc(5 * sizeof(long double *));
    for (int i = 0; i < 5; i++) {
        ATA[i] = (long double *)malloc(5 * sizeof(long double));
        P[i] = (long double *)malloc(5 * sizeof(long double));
        L[i] = (long double *)malloc(5 * sizeof(long double));
        U[i] = (long double *)malloc(5 * sizeof(long double));
    }

    y = (long double *)malloc(N * sizeof(long double));
    y2 = (long double *)malloc(N * sizeof(long double));
    x = (long double *)malloc(N * sizeof(long double));
    x2 = (long double *)malloc(N * sizeof(long double));

    for (int i = 0; i < N; i++) {
        A[i][0] = 1;
        A[i][1] = xValues[i];
        A[i][2] = xValues[i] * xValues[i];
        A[i][3] = xValues[i] * xValues[i] * xValues[i];
        A[i][4] = xValues[i] * xValues[i] * xValues[i] * xValues[i];
    }

    for (int i = 0; i < N; i++) {
        b[i] = yXPRValues[i];
        b2[i] = yETHValues[i];
    }

    //code
    transposeMatrix(A, AT, N, 5);
    multiplyMatrices(AT, A, ATA, 5, N, N, 5);

    multiplyMV(AT, b, ATb, 5, N, N);
    x = solve(P, ATA, L, U, ATb, y, x, 5);

    multiplyMV(AT, b2, ATb2, 5, N, N);
    x2 = solve(P, ATA, L, U, ATb2, y2, x2, 5);
    
    //outputs
    printf("XPR: p4(x) = %Lfx*x*x*x + %Lfx*x*x + %Lfx*x + %Lfx + %Lf\n", x[4], x[3], x[2], x[1], x[0]);
    printf("ETH: p4(x) = %Lfx*x*x*x + %Lfx*x*x + %Lfx*x + %Lfx + %Lf\n\n", x2[4], x2[3], x2[2], x2[1], x2[0]);

    printf("For known dates:\n");
    for (int i = 0; i < N; i++) {
        approx(x, xValues[i], dateStrings[i], "XPR");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        approx(x2, xValues[i], dateStrings[i], "ETH");
    }
    printf("\n\n\n");

    printf("For unknown dates:\n");
    const char* date1 = "2023-11-28";
    const char* date2 = "2023-12-02";
    long double dateNumber1 = YMD_to_time(date1) / (double)100000000;
    long double dateNumber2 = YMD_to_time(date2) / (double)100000000;
    approx(x, dateNumber1, date1, "XPR");
    approx(x, dateNumber2, date2, "XPR");
    printf("\n");
    approx(x2, dateNumber1, date1, "ETH");
    approx(x2, dateNumber2, date2, "ETH");

    // Free memory
    for (int i = 0; i < 10; i++) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < 5; i++) {
        free(AT[i]);
        free(ATA[i]);
        free(P[i]);
        free(L[i]);
        free(U[i]);
    }
    free(AT);
    free(ATA);
    free(P);
    free(L);
    free(U);

    free(b);
    free(b2);
    free(ATb);
    free(ATb2);
    free(y);
    free(y2);
    free(x);
    free(x2);
    
    return 0;
}
