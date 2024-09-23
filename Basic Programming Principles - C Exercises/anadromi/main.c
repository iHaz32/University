#include <stdio.h>

int a=0; //global
int pC(int k, int A, int Z) {
  if (A==0||Z==0) {
    a++;
  } else {
    pC(k*10,A,Z-1);
    pC(k*10+1,A-1,Z);
  }
  return a;
}

int main() {
  int A,Z;
  scanf("%d %d",&A,&Z);
  
  printf("%d", pC(0,A,Z));
  return 0;
}