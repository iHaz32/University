#include <stdio.h>
#include <string.h>

struct member {
  char name[30];
  char ranking;
  int number;
};

void sortAndPrint(struct member A[], int N) {
  int i, BS[100000];
  for (i = 0; i < 100000; i++) {
    BS[i] = -1;
  }

  for (i = 0; i < N; i++) {
    BS[A[i].number] = i; // BS[3]=0 kai BS[10]=1
  }
  for (i = 0; i < 100000; i++) {
    if (BS[i] != -1) {
      printf("%s, %c, %d\n", A[BS[i]].name, A[BS[i]].ranking, A[BS[i]].number);
    }
  }
}

int main(void) {
  int N, i;
  struct member A[50];
  scanf("%d ", &N);
  for (i = 0; i < N; i++) {
    fgets(A[i].name, 30, stdin);
    A[i].name[strcspn(A[i].name, "\n")] = '\0';
    if (i < N - 1) {
      scanf("%c %d ", &A[i].ranking, &A[i].number);
    } else {
      scanf("%c %d", &A[i].ranking, &A[i].number);
    }
  }
  sortAndPrint(A, N);

  return 0;
}