#include <stdio.h>

int main(void) {
  int x,i,counter=0;
  scanf("%d",&x);
  if (x<0) {
    printf("Wrong Input");
  } else {
    for (i=1;i<=x;i++) {
      if (x%i==0) {
        counter++;
      }
    }
    printf("%d",counter);
  }
  return 0;
}