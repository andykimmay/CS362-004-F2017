CFLAGS = -Wall -fpic -coverage -lm

test: testme.c
	gcc -o test -g testme.c $(CFLAGS)

clean: rm -f *.o *.gcov *.gcda *.gcno test
