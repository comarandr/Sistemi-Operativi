#include <stdio.h>

void swap(int *, int *);
void bubble(int *, int);

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void bubble(int *begin, int size)
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size - i - 1; j++)
    {
      if(begin[j] > begin[j + 1])
      {
        swap(begin + j, begin + j + 1);
      }
    }
  }
}

#define SIZE 11

int main() {
  int array[SIZE] = {};
  int read = 0;
  int n = 0;

  while(read < SIZE && scanf("%d", &n) == 1) {
    array[read] = n;
    read++;
  }

  bubble(array, read);

  printf("\n");
  for(int i = 0; i < read; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
