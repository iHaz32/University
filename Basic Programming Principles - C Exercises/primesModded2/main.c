#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#define N 200

bool isPrime(int x) {
  int i;
  double root = sqrt(x);
  if (x == 1) {
    return false;
  }
  for (i = 3; i <= root; i += 2) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

int main(void) {
  int i, n, mersenne = 0, k = 0, A[N], counter = 0;
  for (n = 0; mersenne < 2000; n++) {
    mersenne = (round)(pow(2, n)) + 1;
    if (isPrime(mersenne)) {
      A[k] = n;
      A[++k] = mersenne;
      k++;
    }
  }

  for (i = 0; i < k - 1; i += 2) {
    printf("%d, %d\n", A[i], A[i + 1]);
    if ((A[i] != 0) && (ceil(log2(A[i])) == floor(log2(A[i])))) {
      counter++;
    }
  }
  printf("\n\n");
  printf("%d\n\n", counter);
  for (i = 0; i < k; i += 2) {
    if ((A[i] != 0) && (ceil(log2(A[i])) == floor(log2(A[i])))) {
      printf("%d\n", A[i]);
    }
  }
}