// sglib selftest. This file should invoke ALL documented
// functions and macros from sglib library and check
// the internal consistency of results.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sglib.h"

#define DEBUG 0
#define REPEAT 100
#define ORDER 100

int val[ORDER];

int counts[ORDER];
int check_counts[ORDER];

struct MyIntList {
  unsigned 			n;
  struct MyIntList 	*next;

  // rbtree supplement
  char color;
  struct MyIntList *left_ptr;
  struct MyIntList *right_ptr;
};

typedef struct MyIntList SortedList;
typedef struct MyIntList ReverseSortedList;
typedef struct MyIntList SimpleList;
typedef struct MyIntList Tree;

#define ARRAY_CORRESPONDENCE_FUN(val) (((val)<<2) ^ (val)>>1)

#define MY_REVERSE_LIST_CMP(e1, e2) ((e2)->n - (e1)->n)
#define MY_AB_EXCHANGER(type, a, i, j) {\
  SGLIB_ARRAY_ELEMENTS_EXCHANGER(int, a, i, j);\
  SGLIB_ARRAY_ELEMENTS_EXCHANGER(int, b, i, j);\
}

int myListCmp(struct MyIntList *e1, struct MyIntList *e2) {
  return(e1->n - e2->n);
}

typedef int rint;


SGLIB_DEFINE_LIST_FUNCTIONS(SimpleList, myListCmp, next);

SGLIB_DEFINE_SORTED_LIST_PROTOTYPES(SortedList, myListCmp, next);
SGLIB_DEFINE_SORTED_LIST_FUNCTIONS(SortedList, myListCmp, next);
SGLIB_DEFINE_SORTED_LIST_PROTOTYPES(ReverseSortedList, MY_REVERSE_LIST_CMP, next);
SGLIB_DEFINE_SORTED_LIST_FUNCTIONS(ReverseSortedList, MY_REVERSE_LIST_CMP, next);
SGLIB_DEFINE_RBTREE_PROTOTYPES(Tree, left_ptr, right_ptr, color, myListCmp, 0, 1);
SGLIB_DEFINE_RBTREE_FUNCTIONS(Tree, left_ptr, right_ptr, color, myListCmp, 0, 1);


void generate_values() {
	int i;
	for(i=0; i<ORDER; i++) {
		val[i] = random() % ORDER;
	}
}

void compute_orders_for_array(int *a, int *counts, int max) {
	int i;
	memset(counts, 0, ORDER*sizeof(int));
	for(i=0; i<max; i++) {
		counts[a[i]]++;
	}
}

void compute_orders_for_list(struct MyIntList *list, int *counts) {
	struct MyIntList *l;
	memset(counts, 0, ORDER*sizeof(int));
	for(l=list; l!=NULL; l=l->next) {
		counts[l->n] ++;
	}
}

void compare_counts(int *counts, int *check_counts) {
	int i;
	for(i=0; i<ORDER; i++) {
		if (counts[i] != check_counts[i]) {
			fprintf(stderr,"[ERROR] DIFFERENT NUMBERS IN TEST STRUCTURE !!!!!!!!!!!!!!!\n");
			fprintf(stderr,"[ERROR] %d ", i);
			if (counts[i] > check_counts[i]) {
				fprintf(stderr,"IS MISSING\n");
			} else {
				fprintf(stderr,"APPEARED\n");
			}
			exit(1);
		}
	}
}

void compare_unique_counts(int *counts, int *check_counts) {
	int i;
	for(i=0; i<ORDER; i++) {
		if (counts[i] == 0) assert(check_counts[i]==0);
		else assert(check_counts[i]==1);
	}
}

void check_array_values(int *a, int max) {
	compute_orders_for_array(val, counts, ORDER);
	compute_orders_for_array(a, check_counts, max);
	compare_counts(counts, check_counts);
}

void check_int_list_values(struct MyIntList *list) {
	compute_orders_for_array(val, counts, ORDER);
	compute_orders_for_list(list, check_counts);
	compare_counts(counts, check_counts);
}

void check_int_unique_list_values(struct MyIntList *list) {
	compute_orders_for_array(val, counts, ORDER);
	compute_orders_for_list(list, check_counts);
	compare_unique_counts(counts, check_counts);
}

void check_list_equality(struct MyIntList *list1, struct MyIntList *list2) {
  struct MyIntList *l1, *l2;
  l1=list1; l2=list2;
  while(l1 != NULL) {
	assert(l2!=NULL && l1->n == l2->n);
	l1 = l1->next;
	l2 = l2->next;
  }
  assert(l2 == NULL);
}

void check_multiple_array_correspondence(int *a, int *b) {
	int i;
	for (i=0; i<ORDER; i++) {
		if (b[i] != ARRAY_CORRESPONDENCE_FUN(a[i])) {
			fprintf(stderr,"[ERROR] ARRAY CORRESPONDENCE PROBLEM AT INDEX %d !!!!!!!!!!!!!!!\n", i);
			exit(1);
		}
	}
}

void check_that_int_array_is_sorted(int *a, int max) {
  int i;
  for(i=0; i<max-1; i++) {
	if (a[i]>a[i+1]) {
	  fprintf(stderr,"[ERROR] ARRAY UNSORTED AT INDEX %d !!!!!!!!!!!!!!!\n", i);
	  exit(1);
	}
  }
  return;
}

void check_that_int_list_is_sorted(struct MyIntList *l) {
  if (l==NULL) return;
  for(; l->next!=NULL; l=l->next) {
	if (l->n > l->next->n) {
	  fprintf(stderr,"[ERROR] LIST UNSORTED !!!!!!!!!!!!!!!\n");
	  exit(1);
	}
  }
  return;
}


void check_that_int_list_is_reverse_sorted(struct MyIntList *l) {
  if (l==NULL) return;
  for(; l->next!=NULL; l=l->next) {
	if (l->n < l->next->n) {
	  fprintf(stderr,"[ERROR] LIST UNSORTED !!!!!!!!!!!!!!!\n");
	  exit(1);
	}
  }
  return;
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


void array_quick_sort_test(int seed) {
	int a[ORDER];
	int b[ORDER];
	int i,pass;
	srandom(seed);
	generate_values();
	for(i=0; i<ORDER; i++) {
		a[i] = val[i];
		b[i] = ARRAY_CORRESPONDENCE_FUN(val[i]);
	}
#if DEBUG
	for(i=0; i<ORDER; i++) fprintf(stderr,"%d ", a[i]);
	fprintf(stderr,"\n");
#endif
	SGLIB_ARRAY_QUICK_SORT(int, a, ORDER, SGLIB_NUMERIC_COMPARATOR, MY_AB_EXCHANGER);
#if DEBUG
	for(i=0; i<ORDER; i++) fprintf(stderr,"%d ", a[i]);
	fprintf(stderr,"\n\n");
#endif
	check_that_int_array_is_sorted(a, ORDER);
	check_array_values(a, ORDER);
	check_multiple_array_correspondence(a, b);

	//&sglib_rint_array_quick_sort(a, ORDER);
}

void array_heap_sort_test(int seed) {
	int a[ORDER];
	int b[ORDER];
	int i,pass;
	srandom(seed);
	generate_values();
	for(i=0; i<ORDER; i++) {
		a[i] = val[i];
		b[i] = ARRAY_CORRESPONDENCE_FUN(val[i]);
	}
#if DEBUG
	for(i=0; i<ORDER; i++) fprintf(stderr,"%d ", a[i]);
	fprintf(stderr,"\n");
#endif
	SGLIB_ARRAY_HEAP_SORT(int, a, ORDER, SGLIB_NUMERIC_COMPARATOR, MY_AB_EXCHANGER);
#if DEBUG
	for(i=0; i<ORDER; i++) fprintf(stderr,"%d ", a[i]);
	fprintf(stderr,"\n\n");
#endif
	check_that_int_array_is_sorted(a, ORDER);
	check_array_values(a, ORDER);
	check_multiple_array_correspondence(a, b);

	//sglib_heap_sort_rint_array(a, ORDER);
}

void list_sort_test(int seed) {
	int 		a[ORDER];
	int 		i,pass;
	SortedList	*list, *elem, *l, *lnext;
	srandom(seed);
	generate_values();
	list = NULL;
	for(i=0; i<ORDER; i++) {
		elem = malloc(sizeof(SortedList));
		elem->n = val[i];
		elem->next = list;
		list = elem;
	}
#if DEBUG
	for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n);
	fprintf(stderr,"\n");
#endif
	sglib_SimpleList_sort(&list);
#if DEBUG
	for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n);
	fprintf(stderr,"\n\n");
#endif
	check_that_int_list_is_sorted(list);
	check_int_list_values(list);

	for(l=list; l!=NULL; l=lnext) {
		lnext = l->next;
		free(l);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  LIST TEST   ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void list_test(int seed) {
	int i, len;
	int a[ORDER];
	int b[ORDER];
	struct MyIntList	*list, *list2, *l, *t, *e, *e2, te, *memb, *memb2;

	srandom(seed);
	generate_values();

	list = NULL; list2 = NULL;
	for(i=0; i<ORDER; i++) {
		assert(sglib_SimpleList_len(list) == i);
		
		a[i] = val[i];
		b[i] = i;
		e = malloc(sizeof(struct MyIntList));
		e->n = val[i];
		sglib_SimpleList_add(&list, e);
		e2 = malloc(sizeof(struct MyIntList));
		e2->n = val[i];
		e2->next = NULL;
		sglib_SimpleList_concat(&list2, e2);
	}

	check_int_list_values(list);
	check_int_list_values(list2);

	//&for(l=list2; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");
	SGLIB_LIST_REVERSE(struct MyIntList, list2, next);
	check_list_equality(list, list2);


	SGLIB_LIST_MAP_ON_ELEMENTS(SimpleList, list2, next, {
	  free(_current_element_);
	});

	//&for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");
	// this creates a permutation in b
	SGLIB_ARRAY_QUICK_SORT(int, a, ORDER, SGLIB_NUMERIC_COMPARATOR, MY_AB_EXCHANGER);
	// checkin is_member
	for(i=0; i<ORDER; i++) {
		te.n = val[i];
		assert(sglib_SimpleList_find_member(list, &te) != NULL);
		te.n = -val[i]-1;
		assert(sglib_SimpleList_find_member(list, &te) == NULL);
	}

	SGLIB_LIST_MAP_ON_ELEMENTS(SimpleList, list, next, {
	  assert(sglib_SimpleList_is_member(list, _current_element_));
	});
	assert( ! sglib_SimpleList_is_member(list, &te));

	for(i=0; i<ORDER; i++) {
		te.n = a[b[i]];
		SGLIB_LIST_FIND_MEMBER(SimpleList, list, &te, myListCmp, next, memb);
		assert(memb!=NULL);
		assert(list!=NULL);
		sglib_SimpleList_delete(&list, memb);
		free(memb);
		//&fprintf(stderr,"del(%d)  ", a[b[i]]);
		//&for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");
	}
	assert(list==NULL);


	list = NULL;
	for(i=0; i<ORDER; i++) {
		e = malloc(sizeof(struct MyIntList));
		e->n = val[i];
		sglib_SimpleList_add_if_not_member(&list, e, &memb2);
	}

	//&for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");

	check_int_unique_list_values(list);

	// checkin is_member
	for(i=0; i<ORDER; i++) {
		te.n = val[i];
		assert(sglib_SimpleList_find_member(list, &te)!=NULL);
	}

	for(i=0; i<ORDER; i++) {
		te.n = a[b[i]];
		SGLIB_LIST_FIND_MEMBER(SimpleList, list, &te, myListCmp, next, memb);
		sglib_SimpleList_delete_if_member(&list, &te, &memb2);
		assert(memb == memb2);
		if (memb!=NULL) free(memb);
	}
	assert(list==NULL);


	list = NULL;
	for(i=0; i<ORDER; i++) {
		e = malloc(sizeof(struct MyIntList));
		e->n = val[i];
		sglib_SimpleList_add(&list, e);
	}
	
	check_int_list_values(list);
	sglib_SimpleList_sort(&list);
	check_that_int_list_is_sorted(list);
	check_int_list_values(list);
	sglib_SimpleList_reverse(&list);
	check_int_list_values(list);
	check_that_int_list_is_reverse_sorted(list);

	list2 = NULL;
	SGLIB_LIST_MAP_ON_ELEMENTS(SimpleList, list, next, {
		e = malloc(sizeof(struct MyIntList));
		e->n = _current_element_->n;
		sglib_SimpleList_add(&list2, e);	  
	});

}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  SORTED LIST TEST   ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void sorted_list_test(int seed) {
	int i, len;
	int a[ORDER];
	int b[ORDER];
	struct MyIntList	*list, *l, *e, te, *memb, *memb2;

	srandom(seed);
	generate_values();

	list = NULL;
	for(i=0; i<ORDER; i++) {
		assert(sglib_SortedList_len(list) == i);
		
		a[i] = val[i];
		b[i] = i;
		e = malloc(sizeof(struct MyIntList));
		e->n = val[i];
		sglib_SortedList_add(&list, e);
		check_that_int_list_is_sorted(list);
	}

	check_int_list_values(list);

	//&for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");
	// this creates a permutation in b
	SGLIB_ARRAY_QUICK_SORT(int, a, ORDER, SGLIB_NUMERIC_COMPARATOR, MY_AB_EXCHANGER);
	// checkin is_member
	for(i=0; i<ORDER; i++) {
		te.n = val[i];
		assert(sglib_SortedList_find_member(list, &te)!=NULL);
		te.n = -val[i]-1;
		assert(sglib_SortedList_find_member(list, &te)==NULL);
	}

	SGLIB_LIST_MAP_ON_ELEMENTS(SimpleList, list, next, {
	  assert(sglib_SortedList_is_member(list, _current_element_));
	});
	assert( ! sglib_SortedList_is_member(list, &te));

	for(i=0; i<ORDER; i++) {
		te.n = a[b[i]];
		SGLIB_SORTED_LIST_FIND_MEMBER(SortedList, list, &te, myListCmp, next, memb);
		assert(memb!=NULL);
		assert(list!=NULL);
		sglib_SortedList_delete(&list, memb);
		check_that_int_list_is_sorted(list);
		free(memb);
		//&for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");
	}
	assert(list==NULL);


	list = NULL;
	for(i=0; i<ORDER; i++) {
		e = malloc(sizeof(struct MyIntList));
		e->n = val[i];
		sglib_SortedList_add_if_not_member(&list, e, &memb2);
		check_that_int_list_is_sorted(list);
	}

	check_int_unique_list_values(list);

	// checkin is_member
	for(i=0; i<ORDER; i++) {
		te.n = val[i];
		assert(sglib_SortedList_find_member(list, &te)!=NULL);
	}

	for(i=0; i<ORDER; i++) {
		te.n = a[b[i]];
		SGLIB_LIST_FIND_MEMBER(SortedList, list, &te, myListCmp, next, memb);
		sglib_SortedList_delete_if_member(&list, &te, &memb2);
		assert(memb == memb2);
		if (memb!=NULL) free(memb);
		check_that_int_list_is_sorted(list);
	}
	assert(list==NULL);


	list = NULL;
	for(i=0; i<ORDER; i++) {
		e = malloc(sizeof(struct MyIntList));
		e->n = val[i];
		sglib_SortedList_add(&list, e);
	}
	
	check_int_list_values(list);
	check_that_int_list_is_sorted(list);

	sglib_SortedList_sort(&list);

}




/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  RED_BLACK TREE TEST   ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


void sglib_Tree_dump_rec(Tree *t) {
  if (t == NULL) return;
  printf("(");fflush(stdout);
  sglib_Tree_dump_rec(t->left_ptr);
  printf("%s%d ", ((t->color==0)?"r":"b"), t->n);fflush(stdout);
  sglib_Tree_dump_rec(t->right_ptr);
  printf(")");fflush(stdout);
}

void sglib_Tree_dump(Tree *t) {
  printf("\n");fflush(stdout);
  sglib_Tree_dump_rec(t);
  printf("\n");fflush(stdout);
}

void rbtree_test(int seed) {
  int			i;
  int a[ORDER];
  int b[ORDER];
  Tree			*tree, *e, te, *memb, *memb2;
  SimpleList	*list, *l;
  srandom(seed);
  generate_values();
  tree = NULL;
  for(i=0; i<ORDER; i++) {
	a[i] = val[i];
	b[i] = i;
	e = malloc(sizeof(Tree));
	e->n = val[i];
	sglib_Tree_add(&tree, e);
	//&SGLIB_BIN_TREE_MAP_ON_ELEMENTS(Tree, tree, left_ptr, right_ptr, {fprintf(stderr,"%d ", _current_element_->n);});fprintf(stderr,"\n");
	sglib___Tree_consistency_check(tree);
  }

  SGLIB_BIN_TREE_MAP_ON_ELEMENTS(Tree, tree, left_ptr, right_ptr, {
	assert(sglib_Tree_is_member(tree, _current_element_));
  });
  te.n = val[0];
  assert(! sglib_Tree_is_member(tree, &te));

  // create a list of tree elements
  list = NULL;
  SGLIB_BIN_TREE_MAP_ON_ELEMENTS(Tree, tree, left_ptr, right_ptr, {
	sglib_SimpleList_add(&list, _current_element_);
  });

  check_int_list_values(list);

  //&for(l=list; l!=NULL; l=l->next) fprintf(stderr,"%d ", l->n); fprintf(stderr,"\n");
	
  SGLIB_ARRAY_QUICK_SORT(int, a, ORDER, SGLIB_NUMERIC_COMPARATOR, MY_AB_EXCHANGER);
  // checkin is_member
  for(i=0; i<ORDER; i++) {
	te.n = val[i];
	assert(sglib_Tree_find_member(tree, &te)!=NULL);
	te.n = -val[i]-1;
	assert(sglib_Tree_find_member(tree, &te)==NULL);
  }

  for(i=0; i<ORDER; i++) {
	te.n = a[b[i]];
	memb = sglib_Tree_find_member(tree, &te);
	assert(memb!=NULL);
	assert(tree!=NULL);
	sglib_Tree_delete(&tree, memb);
	free(memb);
	sglib___Tree_consistency_check(tree);
  }
  assert(tree==NULL);

  tree = NULL;
  for(i=0; i<ORDER; i++) {
	e = malloc(sizeof(Tree));
	e->n = val[i];
	//sglib_Tree_add(&tree, e);
	sglib_Tree_add_if_not_member(&tree, e, &memb2);
	//&SGLIB_BIN_TREE_MAP_ON_ELEMENTS(Tree, tree, left_ptr, right_ptr, {fprintf(stderr,"%d ", _current_element_->n);});fprintf(stderr,"\n");
	sglib___Tree_consistency_check(tree);
  }

  // create a list of tree elements
  list = NULL;
  SGLIB_BIN_TREE_MAP_ON_ELEMENTS(Tree, tree, left_ptr, right_ptr, {
	sglib_SimpleList_add(&list, _current_element_);
  });

  check_int_unique_list_values(list);

  // checkin is_member
  for(i=0; i<ORDER; i++) {
	te.n = val[i];
	assert(sglib_Tree_find_member(tree, &te)!=NULL);
  }

  for(i=0; i<ORDER; i++) {
	te.n = a[b[i]];
	memb = sglib_Tree_find_member(tree, &te);
	sglib_Tree_delete_if_member(&tree, &te, &memb2);
	assert(memb == memb2);
	if (memb!=NULL) free(memb);
	sglib___Tree_consistency_check(tree);
  }
  assert(tree==NULL);

}  


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


int main() {
	int pass;
	for(pass=0; pass<REPEAT; pass++) {
		array_quick_sort_test(time(NULL));
		array_quick_sort_test(0);
		array_heap_sort_test(time(NULL));
		array_heap_sort_test(0);
		list_sort_test(time(NULL));
		list_sort_test(0);
		list_test(time(NULL));
		sorted_list_test(time(NULL));
		rbtree_test(time(NULL));
	}
	return(0);
}
