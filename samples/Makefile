runall: arraysort arraysort1 arraybinsearch listsort listinsertsort listinsertsort1 rbtree dllist hash selftest
	+make clean

%.exe: %.c ../sglib.h
	gcc -std=gnu89 -Wall -Wextra -pedantic -Wno-unused-function -I.. $*.c -o $*.exe

arraysort: arraysort.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

arraysort1: arraysort1.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

arraybinsearch: arraybinsearch.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

listsort: listsort.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

dllist: dllist.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

hash: hash.exe ../sglib.h
	./$<  1 3 1 5 2 3 1 7 11 33 11

listinsertsort: listinsertsort.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

listinsertsort1: listinsertsort1.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

rbtree: rbtree.exe ../sglib.h
	./$< 6 7 3 4 1 4 1 3 5

selftest: selftest.exe ../sglib.h
	./$<
	echo Done.

clean:;
	rm -f *.exe
