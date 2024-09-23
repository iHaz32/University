#include <stdlib.h>

int *dividedBy(int a, int b, int d, int *n) {
  int i, *A, counter = 0;
  A = (int *)malloc((b - a + 1) * sizeof(int));

  for (i = a; i <= b; i++) {
    if (i % d == 0) {
      A[counter] = i;
      counter++;
    }
  }
  *n = counter;
  return A;
}