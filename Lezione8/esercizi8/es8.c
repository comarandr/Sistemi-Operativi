#include <stdio.h>

#define SIZE 2

int main() {

   int arr[SIZE] = {10,9};

   for(int i = 1; i <= SIZE; i++) {
      int key = arr[i];
      int j = i - 1;
      while (j > 0 && arr[j] >= key) {
         arr[j+1] = arr[j];
         j = j - 1;
      }
      arr[j+1] = key;
   }

   for(int i = 0; i < SIZE; i++) {
      printf("%d ",arr[i]);
   }

   return 0;
}