#include <stdio.h>
#include <string.h>
#include "funcs.h"
#define N 100
int main()
{
 char s[N],k;
 int t;
 read(s,N);
 mostInRow(s,&t,&k);
 printf ("%d %c\n",t,k);
 return 0;
}