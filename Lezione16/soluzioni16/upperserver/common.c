
/*
 * freadline.c
 *
 * File contenente funzioni varie utili per l'implementazione di file_exec.c
 */

#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

char *freadline(FILE *file, char *line)
{
  int size = 0;
  int read = 0;

  // Se siamo già alla fine del file, restituiamo NULL e liberiamo la memoria
  if(feof(file))
    goto exit;

  // Se ci hanno passato già una stringa in input riutilizzeremo la memoria,
  // quindi ci informiamo su quanto lunga è la stringa (la memoria già allocata
  // potrebbe essere di più).
  if(line != NULL)
    size = strlen(line) + 1;

  // Leggiamo un carattere alla volta riallocando quando necessario.
  for(char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file), ++read)
  {
    if(read == size) {
      size = size * 2 + 1;
      line = realloc(line, size);
    }

    line[read] = c;
  }

  // Ci assicuriamo che l'ultimo carattere contenga il terminatore nullo
  if(line)
    line[read] = 0;

  // Se non abbiamo letto nulla perchè si è subito verificato un errore,
  // liberiamo la memoria e restituiamo NULL. Altrimenti restituiamo la linea
  // lo stesso perchè qualcosa è stato comunque letto.
  if(read == 0 && ferror(file))
    goto exit;

  return line;

exit:
  free(line);
  return NULL;
}


void check(int code, int result, char *msg)
{
  if(code != -1) //se riceve -1
    return; //ritorna controllo al chiamante, gestisce in modo elegante

  fprintf(stderr, "%s: %s\n", msg, strerror(errno)); //stampa messaggio

  exit(result);
}
