#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pqueue.h" /* Ficheiro de interface do TDA */


int main(void){

  int array [] = {12,3,4,16,15,17,20,2,1};
  PtPQueue pque;
  int valor;
  int fds;
  pque = PQueueCreate((int)(sizeof(array)/sizeof(int)));

  for(int i=0;i<(int)(sizeof(array)/sizeof(int));i++){
      fds =  PQueueInsert(pque, array[i]);
  }

  for(int i=0;i<(int)(sizeof(array)/sizeof(int));i++){
    PQueueDeleteMax(pque,&valor);
    array[(int)(sizeof(array)/sizeof(int))-i-1]=valor;
  }

  for(int i=0;i<(int)(sizeof(array)/sizeof(int));i++){
    printf("%d - ",array[i]);
  }

  return 0;
}
