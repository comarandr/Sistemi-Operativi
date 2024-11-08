#include <stdio.h>

int main() {
  int n = 0, inizio_parola = 0;

  for(int c = getchar(); c != EOF; c = getchar()) {

    if(c ==' ' || c == '\t' || c == '\n')
    {
      if(inizio_parola) {
        n++;
        inizio_parola=0;
      }
    } else
      inizio_parola=1;
  }

  if(inizio_parola)
    n++;

  printf("Numero di parole: %d\n",n);
  return 0;
}


