#include "list.h"

int main()
{
  struct node *list =
    append(create(3), append(create(42),
    append(create(2), create(4))));

  printf("Elementi della lista: ");
  printlist(list);

  printf("Lunghezza della lista: %d\n", length(list));

  printf("Lista a partire da 'find(list, 42)': ");
  printlist(find(list, 42));

  destroy(list);

  return 0;
}

