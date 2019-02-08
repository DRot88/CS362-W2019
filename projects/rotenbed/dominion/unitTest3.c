/*****************************
* Author: Daniel Rotenberg
* Filename: unitTest3.c
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
* unitTest3: unitTest3.c dominion.o rngs.o
*      gcc -o unitTest3 -g  unitTest3.c dominion.o rngs.o $(CFLAGS)
************************************************************************/
#define NUMBER_OF_TESTS 100
#define FUNCTION "smithy_function"

// function definition in dominion.c

// int smithy_function(int handPos, struct gameState *state) 
// {
//   int i;
//   int currentPlayer = whoseTurn(state);
//   //+3 Cards
//   for (i = 0; i < 4; i++) // BUG INTRODUCED: current player draws 4 cards instead of 3
//   {
//     drawCard(currentPlayer, state);
//   }
  
//   //discard card from hand
//   discardCard(handPos, currentPlayer, state, 0);
//   return 0;  
// }

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

  srand(time(0)); 

  struct gameState GS;
  struct gameState testGS;
  int seed = 2000;
  int numPlayers = 2;
  int handPos = 0;
  int kingdom[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
      remodel, tribute, smithy, council_room};
  initializeGame(numPlayers, kingdom, seed, &GS);
  int preSmithyCardCount, postSmithyCardCount = 0;
  int idx = 0;


  struct sigaction *sa;
  sa = malloc(sizeof(struct sigaction));
  sa->sa_handler = INThandler;
  sigaction(SIGINT, sa, NULL);  

  printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);

  memcpy(&testGS, &GS, sizeof(struct gameState));
  for (idx = 0; idx < NUMBER_OF_TESTS; idx++) {
    testGS.handCount[0] = rand() % 10 + 1; // set hand count to random betwen 1-10
    preSmithyCardCount = testGS.handCount[0]; // capture count
    smithy_function(handPos, &testGS); // play card
    postSmithyCardCount = testGS.handCount[0]; // recapture count
    printf("Expected Result: %d, Actual Result %d\n", preSmithyCardCount+2, postSmithyCardCount); 
    assertTrue(preSmithyCardCount+2 == postSmithyCardCount);
    memcpy(&testGS, &GS, sizeof(struct gameState)); // reset to orginal game state
  }

  return 0;
}