#include "tree.h"

int main(int argc,char **argv)
{
  struct tnode *tree = NULL;

  for(int i=1; i<argc; i++)  {
    tree = tree_insert(tree, atoi(argv[i]));
  }

  struct node *list = tree_to_list(tree);
  printlist(list);

  tree = tree_remove(tree, 0);
  tree_print(tree);
  putchar('\n');

  destroy(list);
  tree_destroy(tree);

  return 0;
}

