#include <stdio.h>
#include <string.h>

int main(void) {
  int i,j,k,r1,c1,r2,c2,A[100][100],B[100][100],C[100][100],sum;
  
  scanf("%d %d",&r1,&c1);
  if (r1<0||r1>100||c1<0||c1>100) {
    printf("Wrong Input");
  } else {
    for (i=0;i<r1;i++) {
      for (j=0;j<c1;j++) {
        scanf("%d",&A[i][j]);
      }
    }
    scanf("%d %d",&r2,&c2);
    if (r2<0||r2>100||c2<0||c2>100||c1!=r2) {
      printf("Wrong Input");
    } else {
      for (i=0;i<r2;i++) {
        for (j=0;j<c2;j++) {
          scanf("%d",&B[i][j]);
        }
      }

      for (i=0;i<r1;i++) {
        for (j=0;j<c2;j++) {
          sum=0;
          for (k=0;k<r2;k++) {
            sum+=A[i][k]*B[k][j];
          }
          C[i][j]=sum;
        }
      }

      for (i=0;i<r1;i++) {
        for (j=0;j<c2;j++) {
          printf("%d",C[i][j]);
          if (j<c2-1) {
            printf(" ");
          }
        }
        printf("\n");
      }
      
    }
  }
}