#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chars(char *s, char *most_seen, char *less_seen) {
  int i, max = -1, min = strlen(s) + 1, A[127], firstShows[strlen(s)];
  bool stop = false;

  for (i = 0; i < 127; i++) {
    A[i] = 0;
  }

  for (i = 0; i < strlen(s); i++) {
    A[s[i]]++;
  }
  for (i = 0; i < strlen(s); i++) {
    if (A[s[i]] > max) {
      max = A[s[i]];
    }
    if (A[s[i]] < min) {
      min = A[s[i]];
    }
  }
  for (i = 0; i < strlen(s) && !stop; i++) {
    if (A[s[i]] == max) {
      *most_seen = s[i];
      stop = true;
    }
  }
  stop = false;
  for (i = 0; i < strlen(s) && !stop; i++) {
    if (A[s[i]] == min) {
      *less_seen = s[i];
      stop = true;
    }
  }
}

char *reverse(char *s) {
  int i;
  char temp, *newWord = (char *)malloc((strlen(s) + 1) * sizeof(char));

  for (i = 0; i < strlen(s); i++) { // bala //lampa
    newWord[i] = s[strlen(s) - i - 1];
  }
  return newWord;
}