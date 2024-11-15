#ifndef _TREE_H__
#define _TREE_H__

#include "list.h"

/*
 * Struttura e funzioni per la manipolazione di alberi binari di ricerca
 */

struct tnode {
  int data;
  struct tnode *parent;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *tree_create(int data);
struct tnode *tree_insert(struct tnode *tree, int data);
struct tnode *tree_find(struct tnode *tree, int data);
struct tnode *tree_successor(struct tnode *node);
struct tnode *tree_remove(struct tnode *tree, int data);
void tree_destroy(struct tnode *tree);
void tree_print(struct tnode *tree);
struct node *tree_to_list(struct tnode *tree);
struct tnode *transplant(struct tnode *, struct tnode *);
struct tnode *tree_remove_node(struct tnode *);

#endif
