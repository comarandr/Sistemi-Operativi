#ifndef _LIST_H__
#define _LIST_H__

#include <stdio.h>
#include <stdlib.h>

/*
 * Struttura e funzioni per la manipolazione di liste concatenate
 */

struct node {
  int data;
  struct node *next;
};

struct node *create(int);
void destroy(struct node *);
int length(struct node *);
struct node *find(struct node *, int);
struct node *last(struct node *);
struct node *append(struct node *, struct node *);
void printlist(struct node *);

#endif
