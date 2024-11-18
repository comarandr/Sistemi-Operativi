#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
//modifica con aggiunta di ulteriore comando
int main(int argc, char **argv)
{
  if(argc < 3) {
    fprintf(stderr,
            "Specificare il nome di un file e l'intervallo in secondi.\n");
    return 1;
  }

  char *endptr = NULL; //puntatore a carattere , devo aver bisogno dell'indirizzo del puntatore per modificare. Doppio puntatore serve per puntare null successo oppure altro errore.  OSSERVAZIONE
  long secondi = strtol(argv[2], &endptr, 10); //stringtolong, funzione particolare. vuole base per convertire intero e puntatore di puntatore a carattere, cioè indirizzo puntatore
  if(*endptr != '\0') { //controlliamo che il deriferimento sia diverso da nullo, deve essere da nullo (FARE UN MAN PER CAPIRE)
    fprintf(stderr,
            "Specificare il nome di un file e l'intervallo in secondi.\n"); //errore
    return 1;
  }

  char *filename = argv[1]; 

  struct stat sb; //nuova struttura
  if(stat(filename, &sb) == -1) //valore di ritorno -1, chiamata fallita
  {
    fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
            argv[0], filename, strerror(errno));
    return 1;
  }

  time_t start = time(NULL); //mi tengo numeri di secondi
  time_t mtime = sb.st_mtime; //tengo data modifica

  int n = 0; //inizio ciclo
  while(time(NULL) - start <= secondi) { //finche non 
    if(stat(filename, &sb) == -1) 
    {
      fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
              argv[0], filename, strerror(errno));
      return 1;
    }

    if(sb.st_mtime != mtime) { //chiamo stat
      ++n; //se cìè stata aggiorno n con n+1
      mtime = sb.st_mtime; //aggiorno mtine con ultima data di modifica
    }
  }
//stampo a fine ciclo
  printf("Il file %s è stato modificato %d volte negli ultimi %ld secondi\n",
         filename, n, secondi);
}

