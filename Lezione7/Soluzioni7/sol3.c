#include <stdio.h>

int main() {
  int i = 0, n = 0; // i è un indice, n è un contatore. n conta i caratteri, resettandosi a ogni spazio, tab o a capo

  for(int c = getchar(); c != EOF; c = getchar()) //per ogni carattere fino EOF
  {
    if(c != ' ' && c != '\t' && c != '\n') { // se il carattere non è uno spazio, un tab o un a capo
      n++; // incremento il contatore 
    } else { // altrimenti

      for(i = 0; i < n; i++) // stampo tanti trattini fino a quanto è arrivato n
        printf("-"); 

      if(n > 0) // se n è maggiore di 0, ovvero ho contato uno spazio, un tab o un a capo
        printf("\n"); // vado a capo

      n = 0; // resetto il contatore
    } //dopo aver resettato conterò ancora una volta, se è EOF il ciclo terminerà
  }

  return 0;
}

