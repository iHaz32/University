#include <stdio.h>
#include <string.h>
#include "funcs.h"
#define N 150
int main()
{
 char a,b,s[N];
 int k;
 fgets(s,N,stdin);
 s[strcspn(s,"\n")]='\0';
 anonymize(s);
 printf("%s\n",s);
 scanf ("%d %c %c",&k,&a,&b);
 createString (k,a,b,s);
 printf("%s\n",s);
 return 0;
}