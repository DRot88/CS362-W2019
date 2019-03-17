CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestcard1 >> randomtestcard1.out
	gcov randomtestcard1.c -b >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out

	./randomtestcard2 >> randomtestcard2.out
	gcov randomtestcard2.c -b >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out

	./randomtestadventurer >> randomtestadventurer.out
	gcov randomtestadventurer.c -b >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out

unittestresults: unitTest1 unitTest2 unitTest3 unitTest4

	./unitTest1 >> unittestresults.out
	gcov unitTest1.c -b >> unittestresults.out
	cat unitTest1.c.gcov >> unittestresults.out

	./unitTest2 >> unittestresults.out
	gcov unitTest2.c -b >> unittestresults.out
	cat unitTest2.c.gcov >> unittestresults.out

	./unitTest3 >> unittestresults.out
	gcov unitTest3.c -b >> unittestresults.out
	cat unitTest3.c.gcov >> unittestresults.out

	./unitTest4 >> unittestresults.out
	gcov unitTest4.c -b >> unittestresults.out
	cat unitTest4.c.gcov >> unittestresults.out	

unitTest1: unitTest1.c dominion.o rngs.o
	gcc -o unitTest1 -g  unitTest1.c dominion.o rngs.o $(CFLAGS)

unitTest2: unitTest2.c dominion.o rngs.o
	gcc -o unitTest2 -g  unitTest2.c dominion.o rngs.o $(CFLAGS)

unitTest3: unitTest3.c dominion.o rngs.o
	gcc -o unitTest3 -g  unitTest3.c dominion.o rngs.o $(CFLAGS)

unitTest4: unitTest4.c dominion.o rngs.o interface.o
	gcc -o unitTest4 -g  unitTest4.c dominion.o rngs.o interface.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestadventurer randomtestcard1 randomtestcard2 randomtestresults unitTest1 unitTest2 unitTest3 unitTest4 unittestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestadventurer.exe randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe unitTest1 unitTest2 unitTest3 unitTest4
