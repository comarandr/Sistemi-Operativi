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

  printf("Spazi: %d\nTabulazioni: %d\nNewline: %d\n", spazi, tab, newline);

  return 0;
}

