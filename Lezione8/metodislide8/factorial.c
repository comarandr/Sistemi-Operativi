#include <stdio.h>

int power(int,int); // dichiarazione della funzione power

int main() {
  int n;
  for(int i = 0; i < 10; i++)
  printf("%d %3d %6d\n",i,power(2,i),power(-3,i));
    return 0;
}

int power (int m, int n) {
  int p = 1;
  for(int i = 1; i <= n; i++)
    p = p * m;
  return p;
}