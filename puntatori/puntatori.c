#include <stdio.h>
void fake_swap(int a, int b)
{
  int temp = a;
  a = b;
  b = temp;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main()
{
    int x = 42, y = 0;
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}