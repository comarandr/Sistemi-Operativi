/*
 * Funzioni per la manipolazione di alberi binari di ricerca
 */

#include "tree.h"

/*
 * La funzione tree_create() restituisce un nuovo albero costituito da un
 * singolo nodo, con chiave 'data'
 */
struct tnode *tree_create(int data)
{
  struct tnode *node = malloc(sizeof(struct tnode));
  node->data = data;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;

  return node;
}

/*
 * La funzione tree_insert() inserisce una nuova chiave 'data' nell'albero
 * binario di ricerca con radice 'tree'.
 *
 * Nota: per noi NULL è un albero valido, "vuoto".
 * Quindi tree_insert(NULL, 42) è equivalente a tree_create(42)
 */
struct tnode *tree_insert(struct tnode *tree, int data)
{
  if(tree == NULL)
    return tree_create(data);

  if(data <= tree->data) {
    tree->left = tree_insert(tree->left, data);
    tree->left->parent = tree;
  } else {
    tree->right = tree_insert(tree->right, data);
    tree->right->parent = tree;
  }

  return tree;
}

/*
 * La funzione tree_find() cerca la chiave 'data' nell'albero 'tree' e
 * restituisce il nodo contenente la prima occorrenza della chiave, oppure
 * NULL se la chiave non viene trovata.
 */
struct tnode *tree_find(struct tnode *tree, int data) {
  if(tree == NULL)
    return NULL;

  if(data == tree->data)
    return tree;
  else if(data < tree->data)
    return tree_find(tree->left, data);
  else
    return tree_find(tree->right, data);
}

/*
 * La funzione tree_minimum() restituisce il nodo contenente la chiave minima
 * nell'albero con radice 'tree', oppure NULL se l'albero è vuoto (ossia NULL)
 */
struct tnode *tree_minimum(struct tnode *tree) {

  if(tree == NULL)
    return NULL;

  if(tree->left == NULL)
    return tree;

  return tree_minimum(tree->left);
}

/*

 * La funzione tree_remove() rimuove dall'albero 'tree' il nodo contenente la
 * prima occorrenza della chiave 'data'. Se il nodo da rimuovere era lo stesso
 * nodo radice 'tree', restituisce il nuovo nodo radice.
 *
 * L'uso corretto della funzione prevede quindi di riassegnare il valore di
 * ritorno di tree_remove(), per tenere conto del possibile cambio di radice:
 *
 *   tree = tree_remove(tree, 42);
 *
 */
struct tnode *tree_remove(struct tnode *tree, int data)
{
  struct tnode *node = tree_find(tree, data);
  if(node==NULL)
    return tree;
  struct tnode *newnode = tree_remove_node(node);

  if(node == tree)
      return newnode;
  return tree;
}

/*
 * La funzione transplant() è utilizzata internamente da tree_remove_node() e
 * da tree_destroy()
 *
 * Sostituisce il nodo 'child', come figlio del suo nodo parent, con il nodo
 * 'newchild'. Restituisce 'newchild'.
 */
struct tnode *transplant(struct tnode *child, struct tnode *newchild) {
  if(child->parent == NULL)
    return newchild;

  if(child->parent->left == child)
    child->parent->left = newchild;
  else
    child->parent->right = newchild;

  if(newchild != NULL)
    newchild->parent = child->parent;

  child->parent = NULL;

  return newchild;
}

/*
 * La funzione tree_remove_node() è utilizzata internamente da tree_remove()
 *
 * Si occupa della rimozione vera e propria di un nodo dall'albero, occupandosi
 * anche di liberarne la memoria.
 */
struct tnode *tree_remove_node(struct tnode *node)
{
  struct tnode *newnode = NULL;

  if(node->left == NULL && node->right == NULL) {
    transplant(node, NULL);
  } else if(node->left != NULL && node->right == NULL) {
    newnode = transplant(node, node->left);
    free(node);
  } else if(node->right != NULL && node->left == NULL) {
    newnode = transplant(node, node->right);
    free(node);
  } else {
    newnode = node;
    struct tnode *min = tree_minimum(node->right);
    node->data = min->data;
    tree_remove_node(min);
  }

  return newnode;
}

/*
 * La funzione tree_destroy() libera la memoria di tutto l'albero radicato nel
 * nodo 'tree'. Se il nodo non era un nodo radice, si occupa anche di impostare
 * a NULL il puntatore al destro o sinistro del padre.
 */
void tree_destroy(struct tnode *tree) {
  if(tree == NULL)
    return;

  transplant(tree, NULL);

  tree_destroy(tree->left);
  tree_destroy(tree->right);
  free(tree);
}

/*
 * La funzione tree_print stampa sullo standard output le chiavi contenute
 * nell'albero, in ordine.
 */
void tree_print(struct tnode *tree) {
  if(tree == NULL)
    return;

  tree_print(tree->left);
  printf("%d ", tree->data);
  tree_print(tree->right);
}

/*
 * La funzione tree_to_list() converte un albero binario di ricerca in una
 * lista concatenata (vedere flist.h)
 */
struct node *tree_to_list(struct tnode *tree) {
  if(tree == NULL)
    return NULL;

  struct node *left_list = tree_to_list(tree->left);
  struct node *right_list = tree_to_list(tree->right);

  return
    append(left_list, append(create(tree->data), right_list));
}

