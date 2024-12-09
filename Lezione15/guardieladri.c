#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <curses.h>
#include <sys/types.h>
#include <signal.h>

#define PASSO     1 /* entita' dello spostamento del ladro */

#define MAXX     80 /* Numero di colonne dello schermo */
#define MAXY     24 /* Numero di righe dello schermo */

/*
 * Struttura per la comunicazione tra figli e padre
 */
#define GUARDIA 0
#define LADRO 1

struct pos { //conviene definirsi una struttura, codifica scambio tra entità, in questi casi chi 
  int who;      // soggetto che invia il dato: ladro o guardia
  int x;        // coordinata x
  int y;        // coordinata y
};
//terzo argomento di read,write è dimensione byte, stringhe sono variabili, le strutture invece hanno dimensione stabile (quanti byte scambiarsi)
//uguale anche con le socket, pacchetto di lunghezza fissa.
// Funzioni di utilità
int processo(int *pipes, void (*f)(int)); //metafunzione, secondo argomento puntatore a funzione, per parametrizzare più chiamate a più funzioni. Nome funzione che prenda intero e restituisca void.
void quit(int ret);
void message(char *msg);

// Funzioni di controllo del gioco
void ladro(int pipeout);
void guardia(int pipeout);
void controllo(int pipein);

int main()
{
  // Funzioni fornite da ncurses
  initscr();   // inizializzazione dello schermo
  noecho();    // disabilita la visualizzazione dei tasti premuti
  keypad(stdscr, 1); // abilito la gestione dei tasti freccia
  curs_set(0); // nasconde il cursore

  int pipes[2] = { 0 };
  if(pipe(pipes) == -1) {
    perror("Errore nella creazione della pipe.");
    return 1;
  }

  int pid_ladro = processo(pipes, ladro);
  int pid_guardia = processo(pipes, guardia);

  controllo(pipes[0]);

  // Chiediamo la terminazione dei processi del ladro e della guardia.
  kill(pid_ladro,1);
  kill(pid_guardia,1);

  // Comunichiamo la vincita e usciamo quando l'utente preme 'q'
  message("Hai vinto!");
  for(int c = 0; c != 'q'; c = getch());
  quit(0);
}

/*
 * Crea un processo figlio ed esegue nel figlio la funzione 'f' fornita come
 * argomento.
 */
int processo(int *pipes, void (*f)(int))
{
  pid_t pid = fork(); //fork  
  switch(pid) {
    case -1:
      perror("fork()");
      exit(1);
    case 0:
      close(pipes[0]);
      f(pipes[1]);
  }
  return pid;
}

/*
 * Funzione chiamata per terminare il processo stando sicuri di dismettere
 * sempre ncurses correttamente
 */
void quit(int ret) {
  endwin(); // termina l'uso di ncurses
  exit(ret);
}

/*
 * Funzione di coordinazione del processo padre
 */
void controllo (int pipein) //descrittore della pipe in ingresso, gli interessa leggere
{ //inizializza
  struct pos ladro = { LADRO, -1, -1 }; 
  struct pos guardia = { GUARDIA, -1, -1 };
//ciclo controllo do while
  do
  {
    struct pos input_pos;
    // leggo la nuova posizione di uno dei due giocatori
    read(pipein, &input_pos, sizeof(struct pos)); //legge dalla pipe strutture in ingresso

    if(input_pos.who == LADRO) //se who ladro
      ladro = input_pos; //assegna struttura
    else
      guardia = input_pos;

    // pulisco lo schermo e ridisegno la posizione dei due giocatori
    clear();
    mvaddch(ladro.y, ladro.x, '$');
    mvaddch(guardia.y, guardia.x, '#');

    // questa funzione mostra effettivamente le modifiche fatte allo schermo
    refresh();
  } while (guardia.x != ladro.x || guardia.y != ladro.y);//gioco continua finché guardia e ladro non coincidono 
}

/*
 * Mostra una scritta in mezzo allo schermo
 */
void message(char *msg) {
  int x = MAXX / 2 - strlen(msg) / 2;
  int y = MAXY / 2;

  clear();
  for(int i = 0; msg[i]; ++i, ++x) {
    mvaddch(y, x, msg[i]);
  }
  refresh();
}

void ladro(int pipeout)
{
  struct pos pos_ladro = {
    .x = 0,
    .y = 0,
    .who = LADRO
  };

  // comunico la posizione iniziale del ladro
  write(pipeout, &pos_ladro, sizeof(struct pos));

  // inizializzo il seme della generazione di numeri casuali
  srandom(time(NULL));
  while(1)
  {
    int dx = PASSO;
    if(random() >= RAND_MAX / 2)
      dx = -PASSO;

    if(pos_ladro.x + dx < 0 || pos_ladro.x + dx >= MAXX)
      dx = -dx;

    pos_ladro.x += dx;

    int dy = PASSO;
    if(random() >= RAND_MAX / 2)
      dy = -PASSO;
//controllo di non uscire dallo schermo
    if(pos_ladro.y + dy < 0 || pos_ladro.y + dy >= MAXY)
      dy = -dy;

    pos_ladro.y += dy;

    write(pipeout, &pos_ladro, sizeof(struct pos)); //comunico posizione nuovo al controllo

    usleep(1000); // aspetto mezzo secondo 500000 val. standard
  }
}

void guardia(int pipeout)
{
  struct pos pos_guardia = {
    .who = GUARDIA,
    .x = MAXX - 1,
    .y = MAXY - 1
  };

  write(pipeout, &pos_guardia, sizeof(struct pos)); 

  while(1) {
    int c = getch(); // funzione di ncurses

    switch(c) {
      case KEY_UP: //freccia verso l'altro
        if(pos_guardia.y > 0)
          pos_guardia.y -= 1;
        break;
      case KEY_DOWN:
        if(pos_guardia.y < MAXY - 1)
          pos_guardia.y += 1;
        break;
      case KEY_LEFT:
        if(pos_guardia.x > 0)
          pos_guardia.x -= 1;
        break;
      case KEY_RIGHT:
        if(pos_guardia.x < MAXX - 1)
          pos_guardia.x += 1;
        break;
    }

    write(pipeout, &pos_guardia, sizeof(pos_guardia)); //scrivo posizione nuova nella pipe
  }
}
