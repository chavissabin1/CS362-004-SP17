CFLAGS = -Wall -fpic -coverage -lm

testme: 
	gcc -o testme testme.c -g  $(CFLAGS)

testme.out: testme
	./testme &> testme.out

all: testme

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so
