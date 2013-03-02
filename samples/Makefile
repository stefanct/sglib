runall: arraysort arraysort1 arraybinsearch listsort \
        listinsertsort listinsertsort1 rbtree dllist \
        selftest clean


arraysort: arraysort.c ../sglib.h
	gcc -I.. arraysort.c
	a.out 6 7 3 4 1 4 1 3 5

arraysort1: arraysort1.c ../sglib.h
	gcc -I.. arraysort1.c
	a.out 6 7 3 4 1 4 1 3 5

arraybinsearch: arraybinsearch.c ../sglib.h
	gcc -I.. arraybinsearch.c
	a.out 6 7 3 4 1 4 1 3 5

listsort: listsort.c ../sglib.h
	gcc -I.. listsort.c
	a.out 6 7 3 4 1 4 1 3 5

dllist: dllist.c ../sglib.h
	gcc -I.. dllist.c
	a.out 6 7 3 4 1 4 1 3 5

listinsertsort: listinsertsort.c ../sglib.h
	gcc -I.. listinsertsort.c
	a.out 6 7 3 4 1 4 1 3 5

listinsertsort1: listinsertsort1.c ../sglib.h
	gcc -I.. listinsertsort1.c
	a.out 6 7 3 4 1 4 1 3 5

rbtree: rbtree.c ../sglib.h
	gcc -I.. rbtree.c
	a.out 6 7 3 4 1 4 1 3 5

clean:;
	rm -f a.out





selftest: selftest.c ../sglib.h
	gcc -I.. -O selftest.c
	a.out
