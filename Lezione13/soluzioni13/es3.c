#include <stdio.h>

#define ITEMS 10

int main()
{
  FILE *devrandom = fopen("/dev/urandom", "rb");
  if(!devrandom) {
    perror("Impossibile aprire il file /dev/urandom");
    return 1;
  }

  int data[ITEMS] = { 0 };
  int items = fread(data, sizeof(int), ITEMS, devrandom);

  // ATTENZIONE: tratto EOF come un errore perché /dev/urandom non dovrebbe
  //             avere una fine.
  if(items != ITEMS) {
    perror("Errore durante la lettura del file /dev/urandom");
    return 2;
  }

  for(int i = 0; i < ITEMS; ++i) {
    printf("%d\n", data[i]);
  }

  fclose(devrandom);

  return 0;
}
