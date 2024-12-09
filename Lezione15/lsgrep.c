#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
 * Questo programma esegue l'equivalente del comando shell:
 *   ls -l | grep <pattern>
 * dove <pattern> viene specificato dalla riga di comando
 */
int main(int argc, char **argv)
{
  if(argc < 2) {
    fprintf(stderr, "specificare un pattern da cercare\n");
    return 1;
  }

  int pipes[2] = { }; //creazione pipe
  if(pipe(pipes) == -1) { //gestione errore
    perror("pipe()");
    return 1;
  }

  pid_t ls = fork(); //fork, origina processo figlio che salvo il ls
  switch(ls) {
    case -1: //errori
      perror("fork()");
      exit(2);
    case 0: // figlio
      dup2(pipes[1], 1); // redirigo stdout, chiudo descrittore stdout
      close(pipes[0]); //chiudo altra parte pipe
      execlp("ls", "ls", "-l", NULL); //chiamata
      perror("ls"); // se arrivo qui, execlp() ha fallito
      return 2;
  } // il padre prosegue

  pid_t grep = fork(); //seconda fork, userò processo figlio di questa fork per usare grep
  switch(grep) {
    case -1:
      perror("fork()");
      exit(2);
    case 0: // figlio
      close(pipes[1]); //non scrivo sulla pipe
      dup2(pipes[0], 0); // redirigo stdin da tastiera che va a finire sul canale di lettura 
      execlp("grep", "grep", argv[1], NULL); //
      perror("grep"); // se arrivo qui, execlp() ha fallito
  } // il padre prosegue

  close(pipes[0]); //padre chiude
  close(pipes[1]);//padre chiude
  // aspetto entrambi i figli
  waitpid(ls,NULL,0); //variabile di wait più sofisticato, consente di aspettare un determinato processo
  waitpid(grep,NULL,0);
  return 0;
}
