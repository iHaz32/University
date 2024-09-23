#include <stdio.h>
#include "funcs.h"

void printArray (int A[], int n)
{
 int i;
 for (i=0;i<n;i++)
 printf("%d\n",A[i]);
}

int main()
{
 int a,b,d,n, *R;
 scanf("%d %d %d",&a, &b ,&d);
 R = dividedBy(a,b,d,&n);
 printArray(R,n);
 return 0;
}