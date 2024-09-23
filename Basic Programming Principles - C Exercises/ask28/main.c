#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_N 200

void sort(char words[][MAX_N], int k) {
  int i, j, min_idx;
  char temp[MAX_N];

  for (i = 0; i < k - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < k; j++)
      if (strcmp(words[j], words[min_idx]) >= 0) {
        min_idx = j;
        printf("\n%s is bigger than %s", words[j], words[min_idx]);
      }

    if (min_idx != i) {
      strcpy(temp, words[j]);
      strcpy(words[j], words[min_idx]);
      strcpy(words[min_idx], temp);
    }
  }
}

/*
strcpy(temp, words[j]);
      strcpy(words[j], words[min_idx]);
      strcpy(words[min_idx], temp);

int main(void) {
  char s[MAX_N], words[MAX_N][MAX_N] = {0};
  int i, j = 0, k = -1;

  fgets(s, MAX_N, stdin);
  s[strcspn(s, "\n")] = '\0';

  for (i = 0; i < strlen(s); i++) { // hello world
    if (s[i] >= 'A' && s[i] <= 'z') {
      k = j == 0 ? k + 1 : k;
      words[k][j] += s[i];
      j++;
    } else {
      j = 0;
    }
  }

  sort(words, k);
  for (i = 0; i <= k; i++) {
    printf("Word %i:%s\n", i, words[i]);
  }
}