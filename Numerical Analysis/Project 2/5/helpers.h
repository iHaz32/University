#ifndef HELPERS_H
#define HELPERS_H

#include <time.h>

void multiplyMV(long double **P, long double *b, long double *result, int rowFirst, int columnFirst, int rowSecond); // Function to multiply a matrix with a vector
void swap(long double *x, long double *y, int n); // Function to swap two vectors
void initializeIn(long double **X, int n); // Function to initialize In matrix
void copy(long double **X, long double **Y, int n); // Function to copy two matrices
void palu(long double **P, long double **A, long double **L, long double **U, int n); // Function to do the PA = LU factorization
void solveY(long double **L, long double *y, long double *b, int n); // Function to solve Ly = b with current b = Pb
void solveX(long double **U, long double *x, long double *y, int n); // Function to solve Ux = y
long double* solve(long double **P, long double **A, long double **L, long double **U, long double *b, long double *y, long double *x, int n); // Function to solve a linear system using the PA = LU factorization method

#endif