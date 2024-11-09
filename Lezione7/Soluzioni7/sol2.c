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

  

  return 0;
}

