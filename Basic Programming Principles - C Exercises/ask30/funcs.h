#include <stdio.h>
#include <string.h>

void read(char s[],int N) {
  fgets(s,N,stdin);
  s[strcspn(s,"\n")]='\0';
}

void mostInRow(char s[], int *t, char *k) {
  int i,counter=0,maxCounter=0;
  char newChar=s[0],maxChar;
  for (i=0;s[i]!='\0';i++) {
    if (s[i]==newChar) {
      counter++;
      if (counter>maxCounter) {
        maxCounter=counter;
        maxChar=s[i];
      }
    } else {
      newChar=s[i];
      counter=1;
    }
  }
  *t=maxCounter;
  *k=maxChar;
}