/*
 * Funzioni per la creazione e manipolazione di liste concatenate
 * soltanto strutture e procedure dichiarate
 */

struct node_t {
  int data;
  struct node_t *next;
};

typedef struct node_t Node; //serve ad assegnare un nuovo tipo, posso usare Node invece di struct node_t, abbrevia

// Restituisce una lista vuota (ovvero semplicemente NULL)
Node *list_empty();

// Restituisce 'vero' se la lista è vuota (cioè se è NULL)
int list_is_empty(Node *head);

// Crea un nodo
Node *list_create(int data);

// Distrugge tutti i nodi di una lista
void list_destroy(Node *head);

// Restituisce la lunghezza di una lista
int list_length(Node *head);

/*
 * Trova un elemento all'interno della lista e restituisce il nodo che lo
 * contiene, oppure NULL se il nodo non viene trovato.
 */
Node *list_find(Node *, int);

// Restituisce l'ultimo elemento di una lista, o NULL se la lista è NULL
Node *list_last(Node *);

//
Node *list_append(Node *, Node *);
void list_print(Node *);

