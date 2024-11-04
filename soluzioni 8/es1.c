#include <stdio.h>

int is_whitespace(char);

int main() {
  int i = 0, n = 0;

  for(int c = getchar(); c != EOF; c = getchar())
  {
    if(!is_whitespace(c)) {
      n++;
    } else {

      for(i = 0; i < n; i++)
        printf("-");

      if(n > 0)
        printf("\n");

      n = 0;
    }
  }

  return 0;
}

int is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}
