#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define ITEMS 10

int main()
{
  int devrandom = open("/dev/urandom", O_RDONLY);
  if(devrandom == -1) {
    perror("Impossibile aprire il file /dev/urandom");
    return 1;
  }

  int data[ITEMS] = { 0 };
  int bytes = read(devrandom, data, sizeof(int) * ITEMS);

  // ATTENZIONE: tratto EOF come un errore perché /dev/urandom non dovrebbe
  //             avere una fine.
  if(bytes != sizeof(int) * ITEMS) {
    perror("Errore durante la lettura del file /dev/urandom");
    return 2;
  }

  for(int i = 0; i < ITEMS; ++i) {
    printf("%d\n", data[i]);
  }

  close(devrandom);

  return 0;
}
