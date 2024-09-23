#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#define N 5000

// finds prime numbers (1000-9999) that have reversed prime - simple static
// solution

bool alreadyExists(int x, int A[], int tempSize) {
  int i;
  for (i = 0; i <= tempSize; i++) {
    if (x == A[i]) {
      return true;
    }
  }
  return false;
}

bool isPrime(int x) {
  int i;
  double root = sqrt(x);
  if (x % 2 == 0) {
    return false;
  }
  for (i = 3; i <= root; i += 2) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

int findReverse(int n) {
  int f = n / 1000;
  int x = n % 1000;
  int s = x / 100;
  int y = x % 100;
  int t = y / 10;
  int l = y % 10;
  int rev = l * 1000 + t * 100 + s * 10 + f;
  return rev;
}

int main(void) {
  int A[N], i, reverseOfI, tempSize = 0;
  bool isPrimeNumber, exists;
  for (i = 1000; i < 10000; i++) {
    if (isPrime(i)) {
      if (!alreadyExists(i, A, tempSize)) {
        reverseOfI = findReverse(i);
        if (isPrime(reverseOfI)) {
          if (!alreadyExists(reverseOfI, A, tempSize)) {
            A[tempSize] = i;
            A[++tempSize] = reverseOfI;
            tempSize++;
          }
        }
      }
    }
  }

  for (i = 0; i < tempSize - 1; i += 2) {
    printf("%d, %d\n", A[i], A[i + 1]);
  }
}