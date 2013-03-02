// This program uses red-black tree to
// remove multiple occurences of the same
// value from its paramaters.
// For example:
//   a.out 6 7 3 4 1 4 1 3 5
// writes:
//   1 3 4 5 6 7


#include <stdio.h>
#include <stdlib.h>
#include "sglib.h"


typedef struct rbtree {
  int n;
  char color_field;
  struct rbtree *left;
  struct rbtree *right;
} rbtree;

#define CMPARATOR(x,y) ((x->n)-(y->n))

SGLIB_DEFINE_RBTREE_FUNCTIONS(rbtree, left, right, color_field, CMPARATOR, 0, 1);

int main(int argc, char **argv) {
  int i,a;
  struct rbtree e, *t, *the_tree;
  the_tree = NULL;
  for (i=1; i<argc; i++) {
	sscanf(argv[i],"%d", &a);
	e.n = a;
	if (sglib_rbtree_find_member(the_tree, &e)==NULL) {
	  t = malloc(sizeof(struct rbtree));
	  t->n = a;
	  sglib_rbtree_add(&the_tree, t);
	}
  }
  SGLIB_BIN_TREE_MAP_ON_ELEMENTS(struct rbtree, the_tree, left, right, {
	printf("%d ", _current_element_->n);
  });
  printf("\n");
  return(0);
}
