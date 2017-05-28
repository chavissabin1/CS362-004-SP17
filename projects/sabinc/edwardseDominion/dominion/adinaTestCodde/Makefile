CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -fprofile-arcs -ftest-coverage -Wall -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

# New Rule Assignment 4
randomTestAdventurer: randomtestadventurer.c dominion.o my_assert.c my_assert.h
	gcc -o randomtestadventurer -std=c99 -fprofile-arcs -ftest-coverage -Wall -g randomtestadventurer.c my_assert.c dominion.o rngs.o $(CFLAGS)

#New Rule Assignment 4
runRandomTestAdventurer: randomTestAdventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

    
# New Rule Assignment 4
randomTestCard1: randomtestcard1.c dominion.o my_assert.c my_assert.h
	gcc -o randomtestcard1 -std=c99 -fprofile-arcs -ftest-coverage -Wall -g randomtestcard1.c my_assert.c dominion.o rngs.o $(CFLAGS)

# New Rule Assignment 4
runRandomTestCard1: randomTestCard1
	./randomtestcard1 &> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
    
# New Rule Assignment 4
randomTestCard2: randomtestcard2.c dominion.o my_assert.c my_assert.h
	gcc -o randomtestcard2 -std=c99 -fprofile-arcs -ftest-coverage -Wall -g randomtestcard2.c my_assert.c dominion.o rngs.o $(CFLAGS)

# New Rule Assignment 4
runRandomTestCard2: randomTestCard2
	./randomtestcard2 &> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
    
# New Rule Assignment 4
runAllRandomTests: runRandomTestAdventurer runRandomTestCard1 runRandomTestCard2
	
# New Rule
unitTests: dominion.o my_assert.c my_assert.h
#unitest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	#gcc -o unitTests -g unitest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c assert.c dominion.o rngs.o $(CFLAGS)
	gcc -o unitTests -g cardtest4.c my_assert.c dominion.o rngs.o $(CFLAGS)
	
    
# New Rule
unitTest1: unittest1.c dominion.o my_assert.c my_assert.h
	gcc -o unitTest1 -fprofile-arcs -ftest-coverage -Wall -g unittest1.c my_assert.c dominion.o rngs.o $(CFLAGS)
    
# New Rule
unitTest2: unittest2.c dominion.o my_assert.c my_assert.h
	gcc -o unitTest2 -fprofile-arcs -ftest-coverage -Wall -g unittest2.c my_assert.c dominion.o rngs.o $(CFLAGS)
    
# New Rule
unitTest3: dominion.o my_assert.c my_assert.h
	gcc -o unitTest3 -fprofile-arcs -ftest-coverage -Wall -g unittest3.c my_assert.c dominion.o rngs.o $(CFLAGS)
    
# New Rule
unitTest4: dominion.o my_assert.c my_assert.h
	gcc -o unitTest4 -fprofile-arcs -ftest-coverage -Wall -g unittest4.c my_assert.c dominion.o rngs.o $(CFLAGS)
    
# New Rule
cardTest1: dominion.o my_assert.c my_assert.h
	gcc -o cardTest1 -fprofile-arcs -ftest-coverage -Wall -g cardtest1.c my_assert.c dominion.o rngs.o $(CFLAGS)    
    
# New Rule
cardTest2: dominion.o my_assert.c my_assert.h
	gcc -o cardTest2 -fprofile-arcs -ftest-coverage -Wall -g cardtest2.c my_assert.c dominion.o rngs.o $(CFLAGS)    
    
# New Rule
cardTest3: dominion.o my_assert.c my_assert.h
	gcc -o cardTest3 -fprofile-arcs -ftest-coverage -Wall -g cardtest3.c my_assert.c dominion.o rngs.o $(CFLAGS)    
    
# New Rule
cardTest4: dominion.o my_assert.c my_assert.h
	gcc -o cardTest4 -fprofile-arcs -ftest-coverage -Wall -g cardtest4.c my_assert.c dominion.o rngs.o $(CFLAGS)     

#New Rule
runUnitTests: unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4
	./unitTest1 &> unittestresult.out
	./unitTest2 >> unittestresult.out
	./unitTest3 >> unittestresult.out
	./unitTest4 >> unittestresult.out
	./cardTest1 >> unittestresult.out
	./cardTest2 >> unittestresult.out
	./cardTest3 >> unittestresult.out
	./cardTest4 >> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

#all: playdom player testDrawCard testBuyCard badTestDrawCard unitTests
all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o randomtestadventurer randomtestcard1 randomtestcard2 unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4 playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.out *.gcov *.gcda *.gcno *.so
