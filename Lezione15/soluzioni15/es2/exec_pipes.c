#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#include "freadline.h" //una linea per volte

void exec_line(char *line, int nline); //esegue linea letta dal file
void exec_cmd(char **argv, int in, int out); //due exec_cmd per ogni exec_line
char **split(char *str); //scomporre linea

int main(int argc, char **argv)
{ //check dei controlli
  if(argc < 2) {
    fprintf(stderr, "Specificare il nome di un file\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");//funzione iso apertura in sola lettura (va bene anche posix)
  if(!file) { //errore
    fprintf(stderr, "Impossibile aprire il file %s: %s\n",
            argv[1], strerror(errno));
  }
//non si farà nulla
  char *line = NULL; //linea corrente
  int n = 0; //numero di linea

  while(1)
  {
    ++n; //incrementa n
    line = freadline(file, line); //tenta di leggere linea
    if(!line) { 
      if(ferror(file)) {
        perror("Errore di lettura");
        return 2;
      }
      return 0;
    }

    pid_t pid=fork(); //fork con padre in attesa del figlio
    switch(pid) {
      case -1:
        perror("fork()");
        return 3;
      case 0:
        fclose(file); //
        exec_line(line, n);//
      default:
        waitpid(pid,NULL,0);//padre rimane in attesa
    }
  }

  fclose(file);
  return 0;
}

void exec_line(char *line, int nline) //linea e numero di linea
{
  char *first = line; //estrae il primo comando
  char *second = NULL;  //secondo comando non siamo sicuri che utente abbia imposta

  // prima salto qualsiasi cosa che sia uno spazio all'inizio della riga
  while(isspace(*line)) //testare se carattere corrente è uno spazio, in caso si va avanti
    ++line; //incremento line (puntatore) finché trovo spazi

  if(*line == '\0') // in modo da poter accorgermi di linee vuote ed ignorarle
    exit(0); //posso uscire se non trovo nulla

  if(*line == '|') { //se trovo subito il comando di pipe vuol dire che manca il primo comando!!
    fprintf(stderr, "Manca il primo comando alla riga %d\n", nline);
    exit(3);
  }

  // trovo l'inizio del secondo comando cercando il simbolo di pipe
  char *sep = strchr(line, '|'); //cerco prima occorrenza, strchr va a trovare prima occorrenza (secondo arg) nella stringa primo arg
  if(sep == NULL) { //se non trovo la pipe l'utente si è dimenticato del secondo comando
    fprintf(stderr, "Manca il secondo comando alla riga %d\n", nline);
    exit(3);
  }

  second = sep + 1; //
  *sep = 0; //effetto: taglia la stringa in due, fermo first a quel punto

  // salto eventuali spazi o tabulazioni prima dell'inizio del secondo comando
  for(; (*second)==' ' || (*second)=='\t'; second++); //salto spazi con ciclo

  char **argv1 = split(first); //in first primo comando, split divide il comando dagli argomenti, 
  char **argv2 = split(second); //in second ho il secondo comando

  int pipes[2];//creo la pipeline
  pipe(pipes);

  int pid1 = fork();//creo prima fork
  if(pid1 == -1) {
    perror("fork()");//errore
    exit(4);
  }

  if(pid1 == 0) { // figlio 1
    close(pipes[0]);//chiudo la pipe 0
    exec_cmd(argv1, 0, pipes[1]);
  }

  int pid2 = fork();
  if(pid2 == -1) {
    perror("fork()");
    exit(3);
  }

  if(pid2 == 0) { // figlio 2
    close(pipes[1]);//chiudo  pipes1
    exec_cmd(argv2, pipes[0], 1); //nome comando, canale standard output pipes 0, standard input 1
  }

  close(pipes[0]);//chiude pipe padre
  close(pipes[1]);//chiude pipe padre

  waitpid(pid1,NULL,0);//wait del padre
  waitpid(pid2,NULL,0);//wait del padre
  free(argv1);
  free(argv2);

  exit(0);
}

void exec_cmd(char **argv, int in, int out)
{
  if(in != 0) //se in è diverso da 0, vuol dire che siamo nel secondo comando
    dup2(in, 0);//devo allora reindirizzare pipe 
  if(out != 1) //discorso simile
    dup2(out, 1);//primo scrive, secondo esegue

  execvp(argv[0], argv);
  fprintf(stderr, "Impossibile eseguire %s: %s\n", argv[0], strerror(errno));
  exit(5);
}

char **split(char *str) //prepara vettore argomenti
{
  int size = 5;// argomenti
  int found = 0;
  char **strings = calloc(size, sizeof(char *));//calloc, malloc che azzora, piccolo vettore

  int parola = 0; // 1: siamo dentro ad una parola, 0: siamo in mezzo a spazi
  for(char *p = str; *p; ++p) //scandisco finché non trovo null
  {
    // se l'array è pieno lo rialloco
    if(found == size - 1) {
      size = 2 * size + 1;
      strings = realloc(strings, sizeof(char *) * size);
    }

    // All'inizio di una parola incremento 'found' e imposto il puntatore
    if(!parola && !isspace(*p)) {
      parola = 1;//inizio parola
      strings[found] = p;//puntatore alla prima parola
      ++found;//incremento found, che funge da indice
    }

    if(parola && isspace(*p)) {
      parola = 0;
      *p = 0;//imposto terminatore di parola
    }
  }

  strings[found] = NULL; //ultima posizione, quindi metto il null

  return strings;
}
