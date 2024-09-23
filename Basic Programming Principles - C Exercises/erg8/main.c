#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcs.h"

// average of array
bool ArrayAvg(int *A, int n,float *avg);
//return a new array B where B[i] = A[i]-avg(A)
float *Davg(int *A, int n);

int main()
{
 int i,n, *A;
 float avg, *B;
 scanf("%d",&n);
 A = malloc (n*sizeof(int));
 for (i=0;i<n;i++)
 scanf ("%d",&A[i]);
 if (ArrayAvg(A,n,&avg))
 {
 printf ("%.1f\n",avg);
 B = Davg(A,n);
 for (i=0;i<n-1;i++)
 printf ("%.1f ",B[i]);
 printf ("%.1f\n",B[i]);
 }
 else
 {
 printf("NA\n");
 }
 return 0;
}