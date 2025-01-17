#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "freadline.h"

int exec_line(char *line, int cmdargc, char **cmdargs);
char **argsdup(int argc, char **args, char *line); //duplica linea di comando

int main(int argc, char **argv)
{
  if(argc < 3) { //se argc minore di 3, informa sul corretto utilizzo
    fprintf(stderr, "Usage: file_exec <file> <comando...>\n");
    return 1;
  }

  char *filename = argv[1]; //nome file salvato
  int cmdargc = argc - 2; //perché -2? perché tolgo file_exec, file dagli argometi
  char **cmdargs = argv + 2; //perché arg0 = file_exec

  FILE *file = fopen(filename, "r");//provo ad aprire
  if(!file) { //se fallsisco
    fprintf(stderr, "file_exec: %s: %s\n", filename, strerror(errno));
    return 2;
  }

  char *line = NULL;

  int n = 0;
  do { //ciclo do while
    ++n; //n rappr. numero di linea
    line = freadline(file, line); //leggo la linea line e pongo il puntatore nell'area di memoria

    if(line) {
      if(strlen(line) == 0) // saltiamo linee vuote nel file
        continue; //fa passare alla prossima iterazione, come in java

      int result = exec_line(line, cmdargc, cmdargs); //andiamo a eseguire il comando, cmdargc = argc -2, argv +2

      if(result == -1) { //errore per convenzione
        fprintf(stderr,
                "file_exec: impossibile eseguire il comando per la riga %d: %s",
                n, strerror(errno));
        return 3; //controllo alla shell
      }
    }
  } while(line != NULL); 

  return 0;
}

int exec_line(char *line, int cmdargc, char **cmdargs) //puntatore linea, numero argomenti e argomenti stessi
{
  if(!line) //not linea = linea vuota, fallimento
    return -1;

  char **newargs = argsdup(cmdargc, cmdargs, line); //prepariamo gli argomenti, perché non posso eseguirli subito? perché @ è presente
//compito di argsdup
  // Eseguo il comando dopo tolta @
  int pid = fork();//eseguo la fork
  switch(pid) {
    case -1: // Errore di fork()
      fprintf(stderr, "file_exec: impossibile creare un processo figlio: %s\n",
              strerror(errno));
      free(newargs);
      return -1;

    case 0: // Processo figlio
      if(execvp(newargs[0], newargs) == -1) {//[0] è il comando, poi vettore argomenti
        fprintf(stderr, "file_exec: impossibile eseguire %s: %s\n",
                newargs[0], strerror(errno));
        exit(1);
      }

    default: // Processo padre
      wait(NULL); //padre aspetta...
  }

  free(newargs); //libera memoria argomenti
  return 0;
}

char **argsdup(int argc, char **args, char *line) //prepara puntatore di puntatori a caratteri, args puntatore di puntatori a carattere, array di stringhe
{
  // Alloco un nuovo array di argomenti
  char **newargs = (char **)malloc((argc + 1) * sizeof(char *)); //alloco arg c +1

  // Copio i puntatori a tutti gli argomenti così come sono tranne gli
  // argomenti che corrispondono alla stringa "@"
  for(int i = 0; i < argc; ++i) {
    if(strcmp(args[i], "@") == 0) //se argomento corrente è la chiocciola,
      newargs[i] = line; //copio line
    else
      newargs[i] = args[i]; //ricopio così com'è
  }

  newargs[argc] = NULL;

  return newargs;
}
