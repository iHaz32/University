#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *primes(int *B, int n, int *m) {
  int N, i, j, *P, k;
  bool isPrime;

  P = (int *)malloc(n * sizeof(int));
  k = 0;

  for (i = 0; i < n; i++) {
    isPrime = true;
    N = B[i];
    if ((N % 2 == 0 || N < 2) && (N != 2)) {
      isPrime = false;
    }
    for (j = 2; j <= sqrt(N); j++) {
      if (N % j == 0) {
        isPrime = false;
      }
    }
    if (isPrime) {
      P[k] = N;
      k++;
    }
    *m = k;
  }

  return P;
}

void printArray(int *A, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
}