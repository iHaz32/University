#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000

int main(void) {
  int count=0,i,j,k;
  char **A, *s;
  FILE *fp;

  scanf("%d",&k);
  
  A=NULL;
  fp=fopen("a.txt","r");
  if (fp!=NULL) {
    while (!feof(fp)) {
      s=(char *)malloc(N*sizeof(char));
      fgets(s,N,fp);
      s[strcspn(s,"\n")]='\0';
      s=(char *)realloc(s,(strlen(s)+1)*sizeof(char));
      A=realloc(A,++count*sizeof(char *));
      A[count-1]=s;
    }
  }
  fclose(fp);

  fp=fopen("o.txt","w");
  for (i=0;i<count;i++) {
    for (j=0;j<strlen(A[i]);j++) {
      A[i][j]+=k;
    }
    printf("%s\n",A[i]);
    fprintf(fp,"%s\n",A[i]);
  }
  fclose(fp);
}