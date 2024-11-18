#include <stdio.h>

#define ITEMS 10 //variabile simbolica, so che devo fermarmi un numero limitato di interi

int main()
{
  FILE *devrandom = fopen("/dev/urandom", "rb"); //modalità di apertura rb
  if(!devrandom) { //controllo di apertura del file
    perror("Impossibile aprire il file /dev/urandom"); //messaggio di errore
    return 1; //controllo shell
  }

  int data[ITEMS] = { 0 }; //alloco memoria
  int items = fread(data, sizeof(int), ITEMS, devrandom); //data puntatore, devrandom puntatore, fread legge e alloca dentro data 10 interi
//nota: fread ci permette di moltiplicare e allocare(?) mem
  // ATTENZIONE: tratto EOF come un errore perché /dev/urandom non dovrebbe
  //             avere una fine.
  if(items != ITEMS) { //se non leggo 10 interi
    perror("Errore durante la lettura del file /dev/urandom"); //errore di lettura, eof prematuro. stampo
    return 2; //errore e uscita
  }
//ciclo di stampa classico nel caso ci siano tutti e 10
  for(int i = 0; i < ITEMS; ++i) {
    printf("%d\n", data[i]); //stampo 
  }

  fclose(devrandom); //chiudo 

  return 0;
}
