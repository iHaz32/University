#include <stdio.h>

char turn(char c,char direction,int n) {
  for (int i=0;i<n%4;i++) {
    switch (c) {
      case '^':
        c = (direction=='r')?'>':'<';
        break;
      case '>':
        c = (direction=='r')?'v':'^';
        break;
      case 'v':
        c = (direction=='r')?'<':'>';
        break;
      case '<':
        c = (direction=='r')?'^':'v';
        break;
    }
  }
  return c;
}

int main(void) {
  char a,b,rightA,leftA;
  int n;
  
  scanf("%c %c %d",&a,&b,&n);
  rightA=leftA=a;

  rightA=turn(rightA,'r',n);
  leftA=turn(leftA,'l',n);

  if (rightA==b && leftA==b) {
    printf("undefined");
  } else if (rightA==b) {
    printf("cw");
  } else if (leftA==b) {
    printf("ccw");
  }  
  return 0;
}