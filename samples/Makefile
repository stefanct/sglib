runall: arraysort arraysort1 arraybinsearch listsort \
        listinsertsort listinsertsort1 rbtree \
        selftest clean


arraysort: arraysort.c sglib.h
	gcc arraysort.c
	a.out 6 7 3 4 1 4 1 3 5

arraysort1: arraysort1.c sglib.h
	gcc arraysort1.c
	a.out 6 7 3 4 1 4 1 3 5

arraybinsearch: arraybinsearch.c sglib.h
	gcc arraybinsearch.c
	a.out 6 7 3 4 1 4 1 3 5

listsort: listsort.c sglib.h
	gcc listsort.c
	a.out 6 7 3 4 1 4 1 3 5

listinsertsort: listinsertsort.c sglib.h
	gcc listinsertsort.c
	a.out 6 7 3 4 1 4 1 3 5

listinsertsort1: listinsertsort1.c sglib.h
	gcc listinsertsort1.c
	a.out 6 7 3 4 1 4 1 3 5

rbtree: rbtree.c sglib.h
	gcc rbtree.c
	a.out 6 7 3 4 1 4 1 3 5

clean: sglib.h
	rm -f a.out





selftest: selftest.c sglib.h
	gcc -O selftest.c
	a.out
