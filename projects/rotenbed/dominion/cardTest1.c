/*****************************
* Author: Daniel Rotenberg
* Filename: cardTest1.c
******************************/

/***********************************************************************
* Include the following lines in your makefile:
*
* cardTest1: cardTest1.c dominion.o rngs.o
*      gcc -o cardtest1 -g  cardTest1.c dominion.o rngs.o $(CFLAGS)
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


#define TESTCARD "smithy"

// Basic Requirements of Smithy.

// 1. Current player should receive exactly 3 cards.
// 2. 3 cards should come from his own pile.
// 3. No state change should occur for other players.
// 4. No state change should occur to the victory card piles and kingdom card piles.

// assertTrue function so testing continues

void assertTrue(int expression) {
  if (expression == 1) {
    printf("TEST SUCCESSFULLY COMPLETED!\n\n");
  } else {
    printf("TEST FAILED\n\n");
  }
}

int main() {

  // variables to start game
  int playerCount = 2;
  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};
  int seed = 2000;
  struct gameState GS, testGS;

  // Storage for cards
  int handCardCount = 0;
  int handCardCount2 = 0;
  int newCards = 3;
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

  // Initialize Game State and Player Cards
  initializeGame(playerCount,kingdom,seed, &GS);

  // Inform user which card is being tested
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: Using smithy adds 3 cards to deck less discarded smithy card --------------
  printf("TEST 1: smithy adds 3 cards less discarded\n");

  // copy GameState to a test case
  memcpy(&testGS, &GS, sizeof(struct gameState));


  // get card count in hand
  handCardCount = numHandCards(&GS);
  printf("Cards in Hand BEFORE playing Smithy: %d\n", handCardCount);

  // play Smithy card
  cardEffect(smithy, choice1, choice2, choice3, &testGS, handpos, &bonus);

  // get card count in hand
  handCardCount2 = numHandCards(&testGS);
  printf("Cards in Hand AFTER playing Smithy: %d\n", handCardCount2);
  printf("Hand Count = %d, Expected = %d\n", testGS.handCount[playerOne], GS.handCount[playerOne] + newCards - discarded);
  assertTrue(testGS.handCount[playerOne] == GS.handCount[playerOne] + newCards - discarded);

  // ----------- TEST 2: Test Return Value --------------
  printf("TEST 2: Testing Return Value\n");
  
  // copy GameState to a test case  
  memcpy(&testGS, &GS, sizeof(struct gameState));

  retValue = cardEffect(smithy, choice1, choice2, choice3, &testGS, handpos, &bonus);
  printf("Return Value: %d, Expected: %d\n", retValue, expectedValue);
  assertTrue(retValue == expectedValue);

  return 0;
}