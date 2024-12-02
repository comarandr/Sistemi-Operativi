#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  if(argc < 2) {
    fprintf(stderr, "Specificare il nome di un file\n");
    return 1;
  }

  int fd = open(argv[1], O_RDONLY);
  if(fd == -1) {
    fprintf(stderr, "Impossibile aprire il file %s: %s\n",
            argv[1], strerror(errno));
    return 2;
  }

  int pid = fork();
  switch(pid) {
    case -1:
      perror("fork()");
      return 3;
    case 0: // figlio
      dup2(fd, 0);
      execlp("cat", "cat", NULL);
      perror("Impossibile eseguire il comando cat");
      return 4;
    default:
      wait(NULL);
      close(fd);
  }

  return 0;
}
