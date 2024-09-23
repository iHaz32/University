#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ArrayAvg(int *A, int n, float *avg) {
  if (n <= 0) {
    return false;
  }

  int sum = 0, i;
  for (i = 0; i < n; i++) {
    sum += A[i];
  }
  *avg = (float)sum / i;
  return true;
}

float *Davg(int *A, int n) {
  float *B = malloc(n * sizeof(float)), average;
  int i = 0, sum = 0;
  for (i = 0; i < n; i++) {
    sum += A[i];
  }
  average = (float)sum / n;
  for (i = 0; i < n; i++) {
    B[i] = A[i] - average;
  }
  return B;
}