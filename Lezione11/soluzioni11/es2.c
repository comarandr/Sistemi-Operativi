#include <stdio.h>
#include <stdlib.h>
//più semplice da scrivere visto gestione di puntatori, però è sempre meno efficiente in quanto chiamate di procedura con maggiore allocazione
#include "es2.h" //file header definito dell'utente, uso delle virgolette invece delle virgolette angoletti (cercati nella dir corrente

Node *list_empty() { //deve rappresentare il puntatore nullo
  return NULL;
}

int list_is_empty(Node *head) { //confronta puntatore argomento con null
  return head == NULL;
}

Node *list_create(int data) { //alloca memoria, crea singoli nodi
  Node *ptr = malloc(sizeof(Node)); //alloca memoria, struttura in un altro file header (tipi, strutture)
  ptr->data = data; //etichetta
  ptr->next = NULL; //nodi isolati, lo capiamo da qua

  return ptr;
}

int list_length(Node *head) { //puntatore di lista , occhio procedimento ricorsione
  if(head == NULL) //casbo base: lista vuota
    return 0; //torna zero

  return 1 + list_length(head->next); //altrimenti ritorna 1 più prossima lista
}
//trova il nodo contente l'etichetta
Node *list_find(Node *head, int data) { //due argomenti
  if(head == NULL) 
    return NULL;

  if(head->data == data)
    return head;

  return list_find(head->next, data);
}

Node *list_last(Node *head) {
  if(head == NULL)
    return NULL;

  if(head->next == NULL)
    return head;

  return list_last(head->next);
}
//prende due liste e le collega
Node *list_append(Node *head1, Node *head2) {
  if(head1 == NULL) //se head1 nulla
    return head2; //lista 2

  Node *last1 = list_last(head1); //trovo l'ultimo elemento
  last1->next = head2; //sostituisco il riferimento

  return head1; //ritorno primo nodo
}

void list_print(Node *head) {
  if(head == NULL) {
    putchar('\n');
    return;
  }

  printf("%d ", head->data);
  list_print(head->next);
}
//duale funzione crea nodi
void list_destroy(Node *head) {
  if(head == NULL) //se nodo è null
    return; //nulla da deallcolare

  Node *next = head->next; //IMPORTANTE: salvo il puntatore del nodo successivo!!

  free(head);
  list_destroy(next);
}

int main() {
  Node *list =
    list_append(list_create(3), list_append(list_create(42),
    list_append(list_create(2), list_create(4))));

  printf("Elementi della lista: ");
  list_print(list);

  printf("Lunghezza della lista: %d\n", list_length(list));

  printf("Lista a partire da 'find(list, 42)': ");
  list_print(list_find(list, 42));

  list_destroy(list);

  return 0;
}

