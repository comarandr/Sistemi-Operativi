#include <stdio.h>

int main() {
  int tab = 0, spazi = 0, newline = 0;

  for(int c = getchar(); c != EOF; c = getchar()) {
    switch(c) {
      case ' ':
        spazi++;
        break;
      case '\t':
        tab++;
        break;
      case '\n':
        newline++;
        break;
    }
  }

  
  printf("Numero di spazi: %d\n",spazi);
  printf("Numero di tab: %d\n",tab);
  printf("Numero di newline: %d\n",newline);
  return 0;
}

