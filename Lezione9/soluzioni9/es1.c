#include <stdio.h>

int main()
{
  int n = 0, sum = 0;

  while(scanf("%d", &n) == 1) {
    sum += n;
  }

  printf("%d\n", sum);

  return 0;
}
