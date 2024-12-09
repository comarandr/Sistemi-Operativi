#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <curses.h>
#include <pthread.h>

#define PASSO     1 /* entita' dello spostamento del ladro */

#define MAXX     80 /* Numero di colonne dello schermo */
#define MAXY     24 /* Numero di righe dello schermo */

/*
 * Struttura per la comunicazione tra figli e padre
 */
#define GUARDIA 0
#define LADRO 1

// struct per rappresentare la posizione di un giocatore
typedef struct {
  int who;      // soggetto che invia il dato: ladro o guardia
  int x;        // coordinata x
  int y;        // coordinata y
} pos_t; // dichiarata in questo modo (ovvero usando typedef), non serve anteporre 'struct' ogni volta

// struct che rappresenta i dati condivisi tra i tre thread
typedef struct {
  pos_t pos;             // posizione del ladro o della guardia
  int modified;          // 1 -> posizione modificata, 0 -> posizione non modificata
  int end_game;          // vale 0 se la partita  è in corso, 1 altrimenti
  pthread_mutex_t mutex; // mutex
  pthread_cond_t cond;   // condition variable
} shared_pos_t;

// Funzioni di utilità
void quit(int ret);
void message(char *msg);

// Funzioni di controllo del gioco
void *ladro(void *);
void *guardia(void *);
void controllo(shared_pos_t *);

// Funzioni per accedere in lettura e scrittura alla risorsa condivisa
void put_pos(pos_t pos, shared_pos_t *shared);
pos_t get_pos(shared_pos_t *shared);
int match_in_progress(shared_pos_t *shared);
void end(shared_pos_t *shared);

int main()
{
  // Funzioni fornite da ncurses
  initscr();   // inizializzazione dello schermo
  noecho();    // disabilita la visualizzazione dei tasti premuti
  keypad(stdscr, 1); // abilita la gestione dei tasti freccia
  curs_set(0); // nasconde il cursore

  // La variabile di tipo 'pos_t' all'interno di questa struttura
  // verrà usata per comunicare una nuova posizione al thread di controllo
  shared_pos_t shared_pos = {
    { LADRO, -1, -1 },
    0,
    0,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER
  };

  pthread_t ladro_th, guardia_th;
  pthread_create(&ladro_th, NULL, ladro, &shared_pos);
  pthread_create(&guardia_th, NULL, guardia, &shared_pos);

  controllo(&shared_pos);

  // Comunichiamo la vincita e usciamo quando l'utente preme 'q'
  message("Hai vinto!");
  for(int c = 0; c != 'q'; c = getch());

  // Aspetto i thread figli dopo il termine della partita
  pthread_join(ladro_th,NULL);
  pthread_join(guardia_th,NULL);

  quit(0);
}

/*
 * Funzione di coordinamento del processo padre
 */
void controllo (shared_pos_t *shared)
{
  pos_t ladro = { LADRO, -1, -1 };
  pos_t guardia = { GUARDIA, -1, -1 };

  do
  {
    pos_t input_pos = get_pos(shared);

    if(input_pos.who == LADRO)
      ladro = input_pos;
    else
      guardia = input_pos;

    // pulisco lo schermo e ridisegno la posizione dei due giocatori
    clear();
    mvaddch(ladro.y, ladro.x, '$');
    mvaddch(guardia.y, guardia.x, '#');

    // questa funzione mostra effettivamente le modifiche fatte allo schermo
    refresh();
  } while (guardia.x != ladro.x || guardia.y != ladro.y);

  end(shared);
}

void *ladro(void *arg)
{
  shared_pos_t *shared = (shared_pos_t *)arg;//conversione del tipo di puntatore

  pos_t pos_ladro = {
    .x = 0,
    .y = 0,
    .who = LADRO
  };

  // comunico la posizione iniziale del ladro
  put_pos(pos_ladro, shared);

  // inizializzo il seme della generazione di numeri casuali
  srandom(time(NULL));
  while(match_in_progress(shared)) //determina attraverso flag endgame se pausa o no
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

    if(pos_ladro.y + dy < 0 || pos_ladro.y + dy >= MAXY)
      dy = -dy;

    pos_ladro.y += dy;

    put_pos(pos_ladro, shared);

    usleep(500000); // aspetto mezzo secondo
  }

  return NULL;
}

void *guardia(void *arg)
{
  shared_pos_t *shared = (shared_pos_t *)arg;

  pos_t pos_guardia = {
    .who = GUARDIA,
    .x = MAXX - 1,
    .y = MAXY - 1
  };

  put_pos(pos_guardia, shared);

  while(match_in_progress(shared)) {
    int c = getch(); // funzione di ncurses

    switch(c) {
      case KEY_UP:
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

    put_pos(pos_guardia, shared);
  }

  return NULL;
}

// Funzione che scrive la posizione nei dati condivisi.
// Ogni volta che scriviamo la posizione, lo segnaliamo tramite la condition
// variable
void put_pos(pos_t pos, shared_pos_t *shared)
{
  pthread_mutex_lock(&shared->mutex);

  shared->pos = pos;
  shared->modified = 1;
  pthread_cond_signal(&shared->cond);

  pthread_mutex_unlock(&shared->mutex);
}

// Funzione che legge la posizione nei dati condivisi aspettando che
// put_pos segnali la scrittura
pos_t get_pos(shared_pos_t *shared)
{
  pthread_mutex_lock(&shared->mutex);

  while(!shared->modified) {//si ricontrolla l'evento 
    pthread_cond_wait(&shared->cond, &shared->mutex);
  }
  pos_t pos = shared->pos;
  shared->modified = 0;

  pthread_mutex_unlock(&shared->mutex);

  return pos;
}

// Funzione che controlla se la partita è in corso
// oppure è terminata.
int match_in_progress(shared_pos_t *shared)
{
  int flag=0;
  pthread_mutex_lock(&shared->mutex);

  flag=!(shared->end_game);

  pthread_mutex_unlock(&shared->mutex);

  return flag;
}

// Funzione che termina la partita.
void end(shared_pos_t *shared)
{
  pthread_mutex_lock(&shared->mutex);

  shared->end_game=1;

  pthread_mutex_unlock(&shared->mutex);
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

/*
 * Funzione chiamata per terminare il processo stando sicuri di dismettere
 * sempre ncurses correttamente
 */
void quit(int ret) {
  endwin(); // termina l'uso di ncurses
  exit(ret);
}
