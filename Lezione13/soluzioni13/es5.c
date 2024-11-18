#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  if(argc < 3) {
    fprintf(stderr,
            "Specificare il nome di un file e l'intervallo in secondi.\n");
    return 1;
  }

  char *endptr = NULL;
  long secondi = strtol(argv[2], &endptr, 10);
  if(*endptr != '\0') {
    fprintf(stderr,
            "Specificare il nome di un file e l'intervallo in secondi.\n");
    return 1;
  }

  char *filename = argv[1];

  struct stat sb;
  if(stat(filename, &sb) == -1)
  {
    fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
            argv[0], filename, strerror(errno));
    return 1;
  }

  time_t start = time(NULL);
  time_t mtime = sb.st_mtime;

  int n = 0;
  while(time(NULL) - start <= secondi) {
    if(stat(filename, &sb) == -1)
    {
      fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
              argv[0], filename, strerror(errno));
      return 1;
    }

    if(sb.st_mtime != mtime) {
      ++n;
      mtime = sb.st_mtime;
    }
  }

  printf("Il file %s è stato modificato %d volte negli ultimi %ld secondi\n",
         filename, n, secondi);
}

