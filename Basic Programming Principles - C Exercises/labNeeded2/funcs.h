#include <stdio.h>
#include <string.h>

void anonymize(char *s) {
  int i;
  for (i = 0; s[i] != '\0'; i++) {
    s[i] = '*';
  }
}

void createString(int k, char a, char b, char *s) {
  int i;
  for (i = 0; i < k; i++) {
    s[i] = (i % 2 == 0) ? a : b;
  }
  s[i] = '\0';
}