#include <stdio.h>
#include <stdlib.h>
int schroder(int);
int schroder_arr(int);
int Count;
int main(void) {
  int Result ;
  int res;
  int NLines, Test, Line;

  do
  	{
  		printf ("N de elementos da tabela? "); Test = scanf ("%d", &NLines);
  		scanf ("%*[^\n]"); scanf ("%*c");
  	} while (Test == 0)  ;

  printf ("Método 1\n");
  for (Line = 0; Line <= NLines; Line++)
	{
		Count = 0;

		/* invocação do algoritmo pretendido */
		Result = schroder(Line);

		/* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
		/* presenting the result and the number of arithmetic operations executed by the algorithm */
		fprintf (stdout, "Fi(%2d) = %10d   e executou %10d multiplicações\n", Line, Result, Count);
	}

  printf ("Método 2\n");
  for (Line = 0; Line <= NLines; Line++)
  {
    Count = 0;

    /* invocação do algoritmo pretendido */
    Result = schroder_arr(Line);

    /* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
    /* presenting the result and the number of arithmetic operations executed by the algorithm */
    fprintf (stdout, "Fi(%2d) = %10d   e executou %10d multiplicações\n", Line, Result, Count);
  }

}



int schroder (int n){
    if(n==0){return 1;}
    int sum=0;
    for(int i=0;i<=n-1;i++)
    {
      Count++;
      sum += (schroder(i) * schroder(n-i-1));
    }
    return schroder(n-1) + sum;
}



int schroder_arr (int n){
    int array[n+1];
    if(n==0){return 1;}
    int sum=0;
    array[0]=1;
    for(int i=1;i<=n;i++)
    {
      sum=0;
      for(int j=0; j<=i-1;j++)
      {
        Count++;
        sum+=(array[j] * array[i-j-1]);
      }
      array[i]=array[i-1]+sum;
    }
    return array[n];
}
