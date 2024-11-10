#include <stdio.h>
//Scrivere un programma C che conti il numero di parole immesse sullo standard input
int main() {
  int n = 0, inizio_parola = 0; //

  for(int c = getchar(); c != EOF; c = getchar()) { //ciclo che si interrmpe con EOF

    if(c ==' ' || c == '\t' || c == '\n') //se c'è uno spazio
    {
      if(inizio_parola) { //se inizio_parola è 1
        n++; //incrementa n
        inizio_parola=0; //e metti inizio_parola a 0
      }
    } else
      inizio_parola=1; //altrimenti metti inizio_parola a 1
  } //fine for

  if(inizio_parola) //se inizio_parola è 1
    n++; //incrementa n

  printf("Numero di parole: %d\n",n);
  return 0;
}

 
