#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//utilizzo delle chiamate POSIX, ragiorno in termini di puri byte e non a livello di interi
#define ITEMS 10 //costante simbolica

int main()
{
  int devrandom = open("/dev/urandom", O_RDONLY); //uso della open, path del file e costante per modalità lettore
  if(devrandom == -1) { //devrandom è un intero
    perror("Impossibile aprire il file /dev/urandom"); //se uguale a -1 open fallita
    return 1;
  }

  int data[ITEMS] = { 0 }; //inizializzo il vettore di 10 interi a 0
  int bytes = read(devrandom, data, sizeof(int) * ITEMS); //read (file aperto (intero); buffer; moltiplicazione ESPLICITA)
//memorizzo il NUMERO DI BYTES LETTI NON NUMERO INTERI
  // ATTENZIONE: tratto EOF come un errore perché /dev/urandom non dovrebbe
  //             avere una fine.
  if(bytes != sizeof(int) * ITEMS) { //confronto il numero di bytes con il totale per capire se ho letto tutto
    perror("Errore durante la lettura del file /dev/urandom"); //errore
    return 2;
  }

  for(int i = 0; i < ITEMS; ++i) { //ciclo di stampa
    printf("%d\n", data[i]);
  }

  close(devrandom); //chiudo

  return 0;
}
