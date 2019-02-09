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

cardTest1: cardTest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardTest1.c dominion.o rngs.o $(CFLAGS)

cardTest2: cardTest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardTest2.c dominion.o rngs.o $(CFLAGS)

cardTest3: cardTest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardTest3.c dominion.o rngs.o $(CFLAGS)

cardTest4: cardTest4.c dominion.o rngs.o interface.o
	gcc -o cardtest4 -g  cardTest4.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest1: unitTest1.c dominion.o rngs.o interface.o
	gcc -o unitTest1 -g  unitTest1.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest2: unitTest2.c dominion.o rngs.o interface.o
	gcc -o unitTest2 -g  unitTest2.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest3: unitTest3.c dominion.o rngs.o interface.o
	gcc -o unitTest3 -g  unitTest3.c dominion.o rngs.o interface.o $(CFLAGS)

unitTest4: unitTest4.c dominion.o rngs.o interface.o
	gcc -o unitTest4 -g  unitTest4.c dominion.o rngs.o interface.o $(CFLAGS)	

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: cardTest1 cardTest2 cardTest3 cardTest4 unitTest1 unitTest2 unitTest3 unitTest4
	./cardTest1 >> unittestresults.out
	gcov cardTest1.c -b >> unittestresults.out
	cat cardTest1.c.gcov >> unittestresults.out

	./cardTest3 >> unittestresults.out
	gcov cardTest3.c -b >> unittestresults.out
	cat cardTest3.c.gcov >> unittestresults.out

	./cardTest4 >> unittestresults.out
	gcov cardTest4.c -b >> unittestresults.out
	cat cardTest4.c.gcov >> unittestresults.out

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

# CARD TEST 2 WILL CAUSE INFINITE LOOP, CTRL+C TO CLOSE
	./cardTest2 >> unittestresults.out
	gcov cardTest2.c -b >> unittestresults.out
	cat cardTest2.c.gcov >> unittestresults.out	
					
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player cardTest1 cardTest2 cardTest3 cardTest4 unitTest1 unitTest2 unitTest3 unitTest4

clean:
	rm -f *.o playdom.exe playdom player player.exe cardTest1 cardTest1.exe cardTest2 cardTest2.exe cardTest3 cardTest3.exe	cardTest4 cardTest4.exe unitTest1 unitTest1.exe unitTest2 unitTest2.exe unitTest3 unitTest3.exe unitTest4 unitTest4.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
