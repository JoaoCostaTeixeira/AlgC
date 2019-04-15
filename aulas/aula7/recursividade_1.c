#include <stdio.h>
#include <stdlib.h>

double met1(double,int);
double met2(double,int);
int fibo_rec(int);
int fibo_dim(int);

int Count;
int main(void) {
  double Result ;
  int res;
  int NLines, Test, Line;


  do
  	{
  		printf ("N de elementos da tabela? "); Test = scanf ("%d", &NLines);
  		scanf ("%*[^\n]"); scanf ("%*c");
  	} while (Test == 0)  ;

  printf ("Método 1\n");
  for (Line = 1; Line <= NLines; Line++)
	{
		Count = 0;

		/* invocação do algoritmo pretendido */
		Result = met1(0.5, Line); ;

		/* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
		/* presenting the result and the number of arithmetic operations executed by the algorithm */
		fprintf (stdout, "Fi(%2d) = %10f   e executou %10d multiplicações\n", Line, Result, Count);
	}
  printf ("\n\n\n");
  printf ("Método 2\n");
  for (Line = 1; Line <= NLines; Line++)
  {
        /* inicialização da variável global contadora das operações aritméticas */
        /* initialization of the global variable for counting the arithmetic operations */
    Count = 0;

    /* invocação do algoritmo pretendido */
    /* invocation of the pretended algorithm */
    Result = met2(0.5, Line); ;

    /* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
    /* presenting the result and the number of arithmetic operations executed by the algorithm */
    fprintf (stdout, "Fi(%2d) = %10f   e executou %10d multiplicações\n", Line, Result, Count);
  }

  printf ("\n\n\n");
  printf ("fib Rec \n");
  for (Line = 0; Line <= NLines; Line++)
  {
        /* inicialização da variável global contadora das operações aritméticas */
        /* initialization of the global variable for counting the arithmetic operations */
    Count = 0;

    /* invocação do algoritmo pretendido */
    /* invocation of the pretended algorithm */
    res = fibo_rec(Line);

    /* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
    /* presenting the result and the number of arithmetic operations executed by the algorithm */
    fprintf (stdout, "Fi(%2d) = %10d  e executou %10d multiplicações\n", Line, res, Count);
  }

  printf ("\n\n\n");
  printf ("fib Dim \n");

  for (Line = 0; Line <= NLines; Line++)
	{
        /* inicialização da variável global contadora das operações aritméticas */
        /* initialization of the global variable for counting the arithmetic operations */
    Count = 0;

    /* invocação do algoritmo pretendido */
    /* invocation of the pretended algorithm */
    res = fibo_dim(Line);

    /* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
    /* presenting the result and the number of arithmetic operations executed by the algorithm */
    fprintf (stdout, "Fi(%2d) = %10d  e executou %10d multiplicações\n", Line, res, Count);
  }
  exit (EXIT_SUCCESS);
}

int fibo_rec(int n)
{
  if(n==0){return 0;}
  if(n==1){return 1;}
  Count+=2;
  return 3*fibo_rec(n-1) + 2 * fibo_rec(n-2);

}

int fibo_dim(int n)
{
  int array[n+1];
  if(n==0){return 0;}
  else if(n==1){return 1;}
  array[0]=0;
  array[1]=1;
  for(int i=2;i<=n;i++){array[i]=3*array[i-1] + 2 * array[i-2];Count+=2;}
  return array[n];
}



double met1 (double x,int n)
{
  if(n==1){return x;}
  Count++;
  return x*(met1(x,n-1));
}


double met2 (double x, int n)
{
  double aux;
  if(n==0){return 1;}
  if(n==1){return x;}
  aux=met2(x,n/2);
  Count++;
  if(n%2==0){Count++;return aux * aux;}
  else{Count+=2;return x* aux * aux;}
}
