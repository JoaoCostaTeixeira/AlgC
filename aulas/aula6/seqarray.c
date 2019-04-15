/*******************************************************************************
 Ficheiro de implementação do Tipo de Dados Abstracto SEQ_ARRAY (seqarray.c).
 A estrutura de dados de suporte da sequência é um registo, constituída pelos
 campos de tipo inteiro Dim para indicar a capacidade de armazenamento da
 sequência e Size para indicar o número de elementos efectivamente armazenados na
 sequência e o campo de tipo ponteiro Seq, para representar a sequência (array)
 atribuída dinamicamente onde são armazenados os números inteiros.

 Autor : João Teixeira                                NMEC : 80192
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "seqarray.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Definição da Estrutura de Dados Interna da Sequência ************/

struct seqarray
{
  unsigned int Dim; /* capacidade de armazenamento - array's size */
  int Size; /* número de elementos - sequence's size */
  int *Seq; /* ponteiro para armazenar a sequencia - array to store the numbers */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "sequencia(s) inexistente(s) - Sequence(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "indice errado - Wrong index",
                                 "elemento inexistente - Element does not exist",
                                 "sequencia vazia - Empty sequence",
                                 "sequencia cheia - Full sequence",
                                 "dimensao da sequencia errada - Wrong size",
                                 "ficheiro inexistente - File does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/*************************** Definição das Funções ****************************/

void SeqArrayClearError (void)
{ Error = OK; }

int SeqArrayError (void)
{ return Error; }

char *SeqArrayErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqArray SeqArrayCreate (unsigned int pdim)
{
  if(pdim<=0){Error = BAD_SIZE; return NULL;}
  PtSeqArray Pseq;
  if ((Pseq = malloc (sizeof (struct seqarray))) == NULL){ Error = NO_MEM; return NULL; }
//  if ((SeqArray -> Seq = calloc (pdim, sizeof (int))) == NULL){ Error = NO_MEM; return NULL; }
  Error = OK;

  Pseq -> Dim = pdim;
  Pseq -> Size = 0;
  Pseq -> Seq = malloc(sizeof (sizeof (int) * pdim));

  if(Pseq -> Seq == NULL){Error = NO_MEM; free(Pseq); return NULL;}
  Error = OK;
  return Pseq;
}

void SeqArrayDestroy (PtSeqArray *pseq)
{
  PtSeqArray TmpSeqArray = *pseq;
	if(TmpSeqArray == NULL){Error = NO_SEQ; return ;}
	free(TmpSeqArray);
	Error = OK;
	*pseq = NULL;
}

PtSeqArray SeqArrayCopy (PtSeqArray pseq)
{
  PtSeqArray Copy; int I;

  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* criação da sequência copia vazia - creating an empty sequence */
  if ((Copy = SeqArrayCreate (pseq->Dim)) == NULL) return NULL;

  /* fazer a copia dos elementos da sequência - copying the components */
  for (I = 0; I < pseq->Size; I++) Copy->Seq[I] = pseq->Seq[I];
  Copy->Size = pseq->Size;

  return Copy;  /* devolve a sequência copia - returning the new sequence */
}

PtSeqArray SeqArrayFileCreate (char *pfname)
{
  PtSeqArray Seq; FILE *PtF; unsigned int Dim, Size, I;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão da sequência e do número de elementos armazenados */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u %u", &Dim, &Size);
  if (Dim < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* criação da sequência com a dimensão pretendida - creating the sequence */
  if ((Seq = SeqArrayCreate (Dim)) == NULL) { fclose (PtF); return NULL; }

  /* leitura da sequência do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++) fscanf (PtF, "%d", Seq->Seq+I);
  Seq->Size = Size;

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  Error = OK;
  return Seq;  /* devolve a sequência criada - returning the new sequence */
}

void SeqArrayStoreFile (PtSeqArray pseq, char *pfname)
{
  FILE *PtF; unsigned int I;

  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequência tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão da sequência e do número de elementos armazenados na sequência */
  /* writing the sequence's dimension and the number of elements */
  fprintf (PtF, "%u %u\n", pseq->Dim, pseq->Size);

  /* escrita da sequência - writing the sequence's components in the text file */
  for (I = 0; I < pseq->Size; I++) fprintf (PtF, "%d\n", pseq->Seq[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}


/* Capacidade Máxima              */
int  SeqArrayGetDimension (PtSeqArray pseq)
{

  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  Error = OK;
  return pseq -> Dim;

}

/* numero de elementos que estao no array               */
int SeqArrayGetSize (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  Error = OK;
  return pseq -> Size;
}

//Retorna um elemento do array
int SeqArrayGetElement (PtSeqArray pseq, int pindex)
{
    if((pindex >= pseq->Size) || (pindex<- pseq->Size)){ Error = BAD_INDEX; return 0; }
    Error = OK;
    if(pindex>=0){return pseq-> Seq[pindex]; } //Inicio para o fim do Array
    return pseq -> Seq[pseq->Size + pindex]; //Fim para o inicio do array
}

void SeqArraySetElement (PtSeqArray pseq, int pindex, int pvalue)
{
  if((pindex >= pseq->Size) || (pindex<- pseq->Size)){ Error = BAD_INDEX; return ; }
  Error = OK;
  if(pindex>=0){pseq -> Seq[pindex] = pvalue;} //Inicio para o fim do Array
  else{pseq -> Seq[pseq-> Size + pindex] = pvalue;}  //Fim para o inicio do array

}

int SeqArrayEquals (PtSeqArray pseq1, PtSeqArray pseq2)
{
  if ((pseq1 == NULL) || (pseq1 == NULL)) { Error = NO_SEQ; return 0; }
  Error = OK;
  if(pseq1 -> Size != pseq2 -> Size){return 0;} // Se o tamanho nao for o mesmo os arrays sao diferentes
  for(int i=0; i<pseq1 -> Size -1;i++)
  {
    if(pseq1 -> Seq[i] != pseq1 -> Seq[i]){return 0;} // Verificar se todos os valores sao iguais
  }
  return 1;
}

void SeqArrayInsert (PtSeqArray pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return ; }
  if (pseq->Size == pseq -> Dim) { Error = SEQ_FULL; return ; }
  Error = OK;

  pseq -> Seq[pseq->Size] = pvalue; // adicionar o elemento ao fim do Array
  pseq->Size = pseq->Size + 1; // Aumentar o numero de posuçoes ocupadas no array
}

void SeqArrayDelete (PtSeqArray pseq, int pvalue)
{
    if (pseq == NULL) { Error = NO_SEQ; return ; }
    if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

    int aux = 0;
    for(int i=0; i<pseq -> Size;i++)
    {
      if(pseq-> Seq[i] == pvalue){
        aux = 1;
        for(int k=i; k< pseq -> Size-1;k++){pseq-> Seq[k] = pseq-> Seq[k+1];}
        pseq -> Size = pseq -> Size -1;
        i--;
      }
    }
    if( aux == 1) {Error = NO_MEM; }
    Error = OK;
}

void SeqArrayDuplicate (PtSeqArray pseq)
{
  int *newSeq;
  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return; }

  /* verifica se a sequência não está vazia - verifies if sequence is not empty */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  if ((newSeq = calloc (2*pseq->Size, sizeof (int))) == NULL)
  { Error = NO_MEM; return; }

  pseq->Dim = 2*pseq->Size;  /* armazenamento da nova dimensão - storing the new dimension */

  /* copiar os elementos - copying the elements */
  for (int I = 0; I < pseq->Size; I++) newSeq[I] = pseq->Seq[I];
  /* guardar o novo array e libertar o antigo - storing the new arry and freeing the old */
  int * Tmp = pseq->Seq; pseq->Seq = newSeq; free (Tmp);

  Error = OK;
}

int SeqArrayIsOrdered (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return 0; }
  Error = OK;

  for(int i=1; i<pseq->Size;i++)
  {
    if(pseq-> Seq[i-1]> pseq-> Seq [i]){return 0;}
  }
  return 1;
}


int SeqArrayIsEvenOdd (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return 0; }
  Error = OK;

  for(int i=0; i<pseq->Size-1;i++)
  {
      if(((pseq-> Seq[i]%2==0) && (pseq-> Seq[i+1]%2==0))
       || ( (pseq-> Seq[i]%2!=0) && (pseq-> Seq[i+1]%2!=0))){return 0;}

  }
  return 1;
}

int SeqArrayNumberOfMultiples (PtSeqArray pseq, int pvalue)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return 0; }
  Error = OK;

  int sum=0;
  for(int i=0; i<pseq->Size;i++)
  {
      if((pseq -> Seq[i] % pvalue==0)){sum++;}
  }
  return sum;
}

void SeqArraySmallerBigger (PtSeqArray pseq, int * psmall, int * pbig)
{
  if (pseq == NULL) { Error = NO_SEQ; return ; }
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }
  Error = OK;

  int min = pseq-> Seq [0];
  int max = pseq-> Seq [0];

  for(int i=0; i<pseq->Size;i++)
  {
      if((pseq -> Seq[i]< min )){min = pseq -> Seq[i];}
      if((pseq -> Seq[i]> max )){max = pseq -> Seq[i];}
  }
  *psmall = min;
  *pbig = max;
}

int SeqArrayIsPalindromic (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return 0; }
  Error = OK;

  for(int i=0; i<pseq->Size/2+1;i++)
  {
      if(pseq -> Seq[i] != pseq -> Seq[pseq->Size-1-i]){return 0;}
  }
  return 1;
}

double SeqArrayAverage (PtSeqArray pseq)
{
  if (pseq == NULL) { Error = NO_SEQ; return 0; }
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return 0; }
  Error = OK;

  double sum=0;
  for(int i=0; i<pseq->Size;i++){sum = sum + pseq -> Seq[i];}
  return sum/pseq->Size;
}
