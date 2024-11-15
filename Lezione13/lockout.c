#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  if(argc < 2) {
    fprintf(stderr, "Specificare il nome di un file.\n");
    return 1;
  }

  char *file = argv[1];

  struct stat sb;
  if(stat(file, &sb) == -1)
  {
    fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
            argv[0], file, strerror(errno));
    return 1;
  }

  time_t mtime = sb.st_mtime;

  while(1) {
    if(stat(file, &sb) == -1)
    {
      fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
              argv[0], file, strerror(errno));
      return 1;
    }

    if(sb.st_mtime != mtime) {
      printf("Il file %s è stato modificato\n", file);
      return 0;
    }

    sleep(5);
  }
}
