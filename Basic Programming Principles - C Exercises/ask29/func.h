#include <math.h>
#include <stdio.h>

struct vector {
  char description[21];
  double x;
  double y;
};

struct vector readVector() {
  struct vector vector;
  scanf("%s", vector.description);
  scanf("%lf %lf", &vector.x, &vector.y);
  return vector;
}

float getLength(struct vector vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}

struct vector findLongest(struct vector A[], int n) {
  int i, maxI;
  double max = -1, length;
  for (i = 0; i < n; i++) {
    length = getLength(A[i]);
    if (length > max) {
      max = length;
      maxI = i;
    }
  }
  return A[maxI];
}

void printVector(struct vector vector) {
  printf("%s (%.2lf,%.2lf)", vector.description, vector.x, vector.y);
}