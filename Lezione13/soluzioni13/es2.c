#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Legge caratteri in input da 'file' fino ad EOF, o fino al newline '\n',
// e ritorna una stringa allocata dinamicamente con il contenuto.
// Se 'line' non è NULL, sovrascrive la stringa puntata da 'line', che deve
// essere stata precedentemente allocata dinamicamente e che verrà reallocata in
// caso di necessità.
//
// Se la funzione viene chiamata su un file già finito (feof(file) restituisce
// true), la funzione libera la memoria di 'line' e restituisce NULL.
char *fgetline(char *line, FILE *file); //se line non è null 

int main(int argc, char **argv)
{
  if(argc < 3) { //manca uno dei due file 
    fprintf(stderr, "Vanno specificati due file in input.\n");
    return 1; //controllo alla shell
  }

  char *filename1 = argv[1]; //salviamo, puntatore a carattere, primo carattere primo file
  char *filename2 = argv[2];

  FILE *file1 = fopen(filename1, "r"); //apro il primo file
  if(!file1) {
    fprintf(stderr, "Impossibile aprire il file %s: %s\n",
            filename1, strerror(errno));
    return 1;
  }

  FILE *file2 = fopen(filename2, "r"); //apro in lettura salvando in file
  if(!file2) { //se c'è errore, controllo che sia nullo
    fprintf(stderr, "Impossibile aprire il file %s: %s\n", //messaggio errore
            filename2, strerror(errno));
    return 1;
  }

  char *line1 = NULL; //line 1 prima linea del file 1
  char *line2 = NULL; //analogo
//se sono uguali ... se sono diverse
  int n = 0; //inizio ciclo
  do {
    ++n; //n pari a 1 primo ciclo
    line1 = fgetline(line1, file1); //leggo prima linea
    line2 = fgetline(line2, file2);//leggo prima linea
  } while(line1 != NULL && line2 != NULL && strcmp(line1, line2) == 0); //guardia (se uno dei due termina di esce), inoltre il confronto deve essere 0, cioè uguali fra loro
//in caso contrario si esce, casistica terminazione

  // caso 1: i due file sono finiti insieme
  if(line1 == NULL && line2 == NULL) //sono arrivato alla fine senza riscontrare differenze
    printf("I due file sono identici\n"); 
  else { // altrimenti differiscono alla riga n
    printf("I file differiscono alla riga %d\n", n);
    if(line1 && line1[0]) //se non sono nulle
      printf("  Riga %d in '%s': %s\n", n, filename1, line1); //riga numero n in file 1 è line 1
    else
      printf("  Riga vuota o file '%s' terminato\n", filename1); //altrimenti file 1

    if(line2 && line2[0]) //caso duale, nel caso sia la line di file2 è più lunga
      printf("  Riga %d in '%s': %s\n", n, filename2, line2);
    else
      printf("  Riga vuota o file '%s' terminato\n", filename2);
  }

  free(line1); //libero la memoria
  free(line2); //libero la memoria

  return 0; //esco 
}
//com'è fatta
char *fgetline(char *line, FILE *file)
{
  int size = 0;
  int read = 0;

  // Se siamo già alla fine del file, restituiamo NULL e liberiamo la memoria
  if(feof(file)) {
    free(line);
    return NULL;
  }

  // Se ci hanno passato già una stringa in input riutilizzeremo la memoria,
  // quindi ci informiamo su quanto lunga è la stringa (la memoria già allocata
  // potrebbe essere di più).
  if(line != NULL) //se line non è nullo
    size = strlen(line) + 1; //contiamo la lunghezza +1 per terminatore

  // Leggiamo un carattere alla volta riallocando quando necessario.
  for(char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file), ++read) //variabile c di tipo carattere
  { //terminiamo con a capo  e end of file
    if(read == size) { //se read == size abbiamo riempito la vecchia memoria rischiamo di sforare 
      size = size * 2 + 1; //raddoppio memoria
      line = realloc(line, size); //realloco così estendo la dimensione
    }

    line[read] = c; //possiamo leggere c con tranquillità
  } //fine ciclo

  // Ci assicuriamo che l'ultimo carattere contenga il terminatore nullo
  line[read] = 0; //metto terminatore nullo

  return line; //ritorno la linea
}
