#include <stdio.h>
#include <math.h>
#include "func.h"
#define N 50

int main()
{
    struct vector max,A[N];
    int i,n;

    scanf("%d",&n);

    for (i=0;i<n;i++)
        A[i]=readVector();
    max = findLongest(A, n);

    printf("%.2f\n",getLength(max));
    printVector(max);

    return 0;
}