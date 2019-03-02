/*****************************
* Author: Daniel Rotenberg
* Filename: randomtestcard1.c
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
* randomtestcard1: randomtestcard1.c dominion.o rngs.o
*      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
************************************************************************/

#define TESTCARD "great_hall"
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
  int kingdom[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
      remodel, tribute, smithy, council_room};
  int seed = 2000;
  struct gameState GS, testGS;

  // Storage for cards
  int handCardCount = 0;
  int handCardCount2 = 0;
  int newCards = 1;
  int discarded = 1;

  // variables to play a card
  int handpos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int bonus = 0;

  // player
  int playerOne = 0;

  // return value test variables
  int retValue = -1;
  int expectedValue = 0;

  // action count
  int actionCount;
  int testActionCount;
  int expectedActionCount = 1;

  // Initialize Game State and Player Cards
  initializeGame(playerCount,kingdom,seed, &GS);

 
 for (int i = 0; i < NUM_TESTS; i++) { // run tests for the amount of times listed in NUM_TESTS
  // Inform user which card is being tested
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: Using great_hall adds 1 card after playing card --------------
  printf("TEST 1: great_hall adds 1 card less discarded\n");

  // copy GameState to a test case
  memcpy(&testGS, &GS, sizeof(struct gameState));

  // get card count in hand
  handCardCount = numHandCards(&GS);
  printf("Cards in Hand BEFORE playing great_hall: %d\n", handCardCount);

  // play great_hall card
  cardEffect(great_hall, choice1, choice2, choice3, &testGS, handpos, &bonus);

  // get card count in hand
  handCardCount2 = numHandCards(&testGS);
  printf("Cards in Hand AFTER playing great_hall: %d\n", handCardCount2);
  printf("Hand Count = %d, Expected = %d\n", testGS.handCount[playerOne], GS.handCount[playerOne] + newCards - discarded);
  assertTrue(testGS.handCount[playerOne] == GS.handCount[playerOne] + newCards - discarded);

  // ----------- TEST 2: Test Return Value --------------
  printf("TEST 2: Testing Return Value\n");
  
  // copy GameState to a test case  
  memcpy(&testGS, &GS, sizeof(struct gameState));

  retValue = cardEffect(great_hall, choice1, choice2, choice3, &testGS, handpos, &bonus);
  printf("Return Value: %d, Expected: %d\n", retValue, expectedValue);
  assertTrue(retValue == expectedValue);

  // ----------- TEST 3: Test Action Count --------------
  printf("TEST 3: Testing Action Count\n");

  // copy GameState to a test case  
  memcpy(&testGS, &GS, sizeof(struct gameState));  

  // get current actions before playing card
  actionCount = GS.numActions;
  printf("Actions BEFORE playing great_hall: %d\n", actionCount);

  // play great_hall card
  cardEffect(great_hall, choice1, choice2, choice3, &testGS, handpos, &bonus);

  //reduce number of actions after playing great_hall action card
  testGS.numActions--;
  // get action count after playing card
  testActionCount = testGS.numActions;
  printf("Actions AFTER playing great_hall: %d\n", testActionCount);
  printf("Action Count: %d, Expected Action Count: %d\n", testActionCount, expectedActionCount);
  assertTrue(testActionCount == expectedActionCount);
}
  return 0;
}

//great_hall implementation in dominion.c

// case great_hall:
//   //+1 Card
//   drawCard(currentPlayer, state);
  
//   //+1 Actions
//   state->numActions++;
  
//   //discard card from hand
//   discardCard(handPos, currentPlayer, state, 0);
//   return 0;
