#include <stdio.h>
#include <stdlib.h>



int pot(int,int);

int main(void) {
  int a,b,Test;


  		printf ("a= ");scanf ("%d", &a);
      scanf ("%*[^\n]"); scanf ("%*c");
      printf ("b= ");scanf ("%d", &b);
      scanf ("%*[^\n]"); scanf ("%*c");

      fprintf(stdout,"%2d\n",pot(a,b));


        exit (EXIT_SUCCESS);
}

int pot (int a, int b)
{
  if((a==1) || (b==a)){return 1;}
  if((a%b==0) && (pot((int) a/b,b))){ return 1;}
  return 0;
}
