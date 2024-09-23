#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct route {
  char start[50];
  int length;
  int anabasi;
  int katabasi;
  int maxHeight;
  int minHeight;
  char end[50];
};

void swap(struct route *p1, struct route *p2) {
  struct route temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

void singlePrint(struct route a, int way) {
  // way = 0 for normal print - 1 for reverse print
  int time, timeReverse;
  if (way == 0) {
    time = (round)(a.length / 65.0 + a.anabasi / 10.0);
    printf("From %s to %s\n", a.start, a.end);
    printf("Uphill %d, Downhill %d\n", a.anabasi, a.katabasi);
    printf("Max altitude %d, Min altitude %d\n", a.maxHeight, a.minHeight);
    printf("Length %d, Estimated time %d min\n\n", a.length, time);
  } else {
    timeReverse = (round)(a.length / 65.0 + a.katabasi / 10.0);
    printf("From %s to %s\n", a.end, a.start);
    printf("Uphill %d, Downhill %d\n", a.katabasi, a.anabasi);
    printf("Max altitude %d, Min altitude %d\n", a.maxHeight, a.minHeight);
    printf("Length %d, Estimated time %d min\n\n", a.length, timeReverse);
  }
}

void sort(struct route *A, int N) {
  int i, j;
  for (i = 0; i < N - 1; i++) {
    for (j = 0; j < N - i - 1; j++) {
      if (A[j].length <= A[j + 1].length) {
        swap(&A[j], &A[j + 1]);
      }
    }
  }
}

void copy(struct route *a, struct route *b) { *b = *a; }

struct route *readFromInput(int *N) {
  int i;
  struct route *A;

  scanf("%d ", N);
  A = (struct route *)malloc(*N * sizeof(struct route));
  for (i = 0; i < *N; i++) {
    fgets(A[i].start, 50, stdin);
    A[i].start[strcspn(A[i].start, "\n")] = '\0';
    scanf("%d %d %d %d %d ", &A[i].length, &A[i].anabasi, &A[i].katabasi,
          &A[i].maxHeight, &A[i].minHeight);
    fgets(A[i].end, 50, stdin);
    A[i].end[strcspn(A[i].end, "\n")] = '\0';
  }
  sort(A, *N);
  return A;
}

void printData(struct route *A, int N) {
  int i, time, timeReverse;

  for (i = 0; i < N; i++) {
    time = (round)(A[i].length / 65.0 + A[i].anabasi / 10.0);
    printf("From %s to %s\n", A[i].start, A[i].end);
    printf("Uphill %d, Downhill %d\n", A[i].anabasi, A[i].katabasi);
    printf("Max altitude %d, Min altitude %d\n", A[i].maxHeight,
           A[i].minHeight);
    printf("Length %d, Estimated time %d min\n\n", A[i].length, time);
    if (strcmp(A[i].start, A[i].end) != 0) {
      timeReverse = (round)(A[i].length / 65.0 + A[i].katabasi / 10.0);
      printf("From %s to %s\n", A[i].end, A[i].start);
      printf("Uphill %d, Downhill %d\n", A[i].katabasi, A[i].anabasi);
      printf("Max altitude %d, Min altitude %d\n", A[i].maxHeight,
             A[i].minHeight);
      printf("Length %d, Estimated time %d min\n\n", A[i].length, timeReverse);
    }
  }
}

void findShort(struct route *A, int N) {
  int i, j = 0, L;
  struct route *B;
  B = (struct route *)malloc(N * sizeof(struct route));

  scanf("%d", &L);
  for (i = 0; i < N; i++) {
    if (A[i].length <= L) {
      copy(&A[i], &B[j]);
      j++;
    }
  }
  printData(B, j);
  free(B);
  B = NULL;
}

void findLocation(struct route *A, int N) {
  int i, time, timeReverse;
  char key[50];

  fgets(key, 50, stdin);
  key[strcspn(key, "\n")] = '\0';

  for (i = 0; i < N; i++) {
    if (strcmp(A[i].start, key) == 0) {
      singlePrint(A[i], 0);
    } else if (strcmp(A[i].end, key) == 0) {
      singlePrint(A[i], 1);
    }
  }
}

void findUpHill(struct route *A, int N) {
  int i;
  for (i = 0; i < N; i++) {
    if (abs(A[i].anabasi) > abs(A[i].katabasi)) {
      singlePrint(A[i], 0);
    } else if (abs(A[i].katabasi) > abs(A[i].anabasi)) {
      singlePrint(A[i], 1);
    }
  }
}

void findDownHill(struct route *A, int N) {
  int i;
  for (i = 0; i < N; i++) {
    if (abs(A[i].katabasi) > abs(A[i].anabasi)) {
      singlePrint(A[i], 0);
    } else if (abs(A[i].anabasi) > abs(A[i].katabasi)) {
      singlePrint(A[i], 1);
    }
  }
}

void findAltitude(struct route *A, int N) {
  int i, j = 0, min, max;
  struct route *B;
  B = (struct route *)malloc(N * sizeof(struct route));

  scanf("%d %d", &min, &max);
  for (i = 0; i < N; i++) {
    if (A[i].maxHeight - max <= 0 && A[i].minHeight - min >= 0) {
      copy(&A[i], &B[j]);
      j++;
    }
  }
  printData(B, j);
  free(B);
  B = NULL;
}

void findTimely(struct route *A, int N) {
  int T, i;
  double time, timeReverse;
  scanf("%d", &T);

  for (i = 0; i < N; i++) {
    time = A[i].length / 65.0 + A[i].anabasi / 10.0;
    if (time <= T) {
      singlePrint(A[i], 0);
    }
    timeReverse = A[i].length / 65.0 + A[i].katabasi / 10.0;
    if (timeReverse <= T && strcmp(A[i].start, A[i].end) != 0) {
      singlePrint(A[i], 1);
    }
  }
}

struct route *readFromFile(int *N) {
  int i = 0;
  struct route *A;
  char name[50];
  FILE *fp;
  scanf("%s", name);
  fp = fopen(name, "r");
  if (fp != NULL) {
    fscanf(fp, "%d ", N);
    A = (struct route *)malloc(*N * sizeof(struct route));
    while (!feof(fp) && i < *N) {
      fgets(A[i].start, 50, fp);
      A[i].start[strcspn(A[i].start, "\n")] = '\0';
      fscanf(fp, "%d %d %d %d %d ", &A[i].length, &A[i].anabasi, &A[i].katabasi,
             &A[i].maxHeight, &A[i].minHeight);
      fgets(A[i].end, 50, fp);
      A[i].end[strcspn(A[i].end, "\n")] = '\0';
      i++;
    }
  } else {
    A = NULL;
    printf("Can't open file!\n");
  }
  fclose(fp);
  sort(A, *N);
  return A;
}

void saveData(struct route *A, int N) {
  int time, timeReverse, i;
  char name[50];
  FILE *fp;
  scanf("%s", name);
  fp = fopen(name, "w");
  if (fp != NULL) {
    for (i = 0; i < N; i++) {
      time = (round)(A[i].length / 65.0 + A[i].anabasi / 10.0);
      fprintf(fp, "From %s to %s\n", A[i].start, A[i].end);
      fprintf(fp, "Uphill %d, Downhill %d\n", A[i].anabasi, A[i].katabasi);
      fprintf(fp, "Max altitude %d, Min altitude %d\n", A[i].maxHeight,
              A[i].minHeight);
      fprintf(fp, "Length %d, Estimated time %d min\n\n", A[i].length, time);
      if (strcmp(A[i].start, A[i].end) != 0) {
        timeReverse = (round)(A[i].length / 65.0 + A[i].katabasi / 10.0);
        fprintf(fp, "From %s to %s\n", A[i].end, A[i].start);
        fprintf(fp, "Uphill %d, Downhill %d\n", A[i].katabasi, A[i].anabasi);
        fprintf(fp, "Max altitude %d, Min altitude %d\n", A[i].maxHeight,
                A[i].minHeight);
        fprintf(fp, "Length %d, Estimated time %d min\n\n", A[i].length,
                timeReverse);
      }
    }
  } else {
    printf("Can't open file!\n");
  }
  fclose(fp);
}