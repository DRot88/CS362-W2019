/*****************************
* Author: Daniel Rotenberg
* Filename: randomtestcard2.c
******************************/

#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <signal.h>
#include <time.h>

/***********************************************************************
* Include the following lines in your makefile:
*
* randomtestcard2: randomtestcard2.c dominion.o rngs.o
*      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
************************************************************************/

#define TESTCARD "salvager"
#define NUM_TESTS 100

void assertTrue(int expression) {
  if (expression == 1) {
    printf("TEST SUCCESSFULLY COMPLETED!\n\n");
  } else {
    printf("TEST FAILED\n\n");
  }
}

// signal handler
void INThandler(int sig)
{
  printf("\nSignal Interupted! Test Could Not Complete Tests!\n");
  exit(1);
}

int main() {

  struct sigaction *sa;
  sa = malloc(sizeof(struct sigaction));
  sa->sa_handler = INThandler;
  sigaction(SIGINT, sa, NULL);  

  // variables to start game
  int playerCount = 2;
  int kingdom[10] = {adventurer, salvager, village, minion, smithy, mine, cutpurse,
      remodel, tribute, council_room};
  int seed = 2000;
  struct gameState GS, testGS;

  // variables to play a card
  int handpos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int bonus = 0;

  // buy count variables
  int buyCount = 0;
  int testBuyCount = 0;

 // Initialize Game State and Player Cards
  initializeGame(playerCount,kingdom,seed, &GS);

  // Inform user which card is being tested
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);


for (int i = 0; i < NUM_TESTS; i++) {
// ----------- TEST: Using salvager adds 1 buy after playing card --------------
  printf("TEST: salvager adds 1 buy after being played\n");


// copy GameState to a test case
  memcpy(&testGS, &GS, sizeof(struct gameState));

// get buy count in hand
  buyCount = GS.numBuys;
  printf("Buy Count BEFORE playing salvager: %d\n", buyCount);  

// play salvager or nothing
  if ( i % 2 == 0) {
    cardEffect(salvager, choice1, choice2, choice3, &testGS, handpos, &bonus);
    testBuyCount = testGS.numBuys;
    printf("Buy Count AFTER playing salvager: %d\n", testBuyCount);  
    assertTrue(testBuyCount == buyCount + 1);
  } else {
    // get test buy count
    testBuyCount = testGS.numBuys;
    // salavger not played so buy count should not change
    printf("Salvager not played, buyCount: %d\n", testBuyCount);  
    assertTrue(testBuyCount == buyCount);
  }
}

  return 0;
}
