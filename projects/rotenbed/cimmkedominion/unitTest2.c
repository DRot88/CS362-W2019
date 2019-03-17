/*****************************
* Author: Daniel Rotenberg
* Filename: unitTest2.c
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
* unitTest2: unitTest2.c dominion.o rngs.o
*      gcc -o unitTest2 -g  unitTest2.c dominion.o rngs.o $(CFLAGS)
************************************************************************/
#define NUMBER_OF_TESTS 30
#define FUNCTION "isGameOver"

// function definition in dominion.c

// int isGameOver(struct gameState *state) {
//   int i;
//   int j;
  
//   //if stack of Province cards is empty, the game ends
//   if (state->supplyCount[province] == 0) {
//    return 1;
//   }
//   //if three supply pile are at 0, the game ends
//   j = 0;
//   for (i = 0; i < 25; i++) {
//     if (state->supplyCount[i] == 0){
//       j++;
//     }
//   }
//   if ( j >= 3) {
//    return 1;
//   }
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

  struct gameState Game;
  int seed = 2000;
  int numPlayers = 2;
  int kingdom[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
      remodel, tribute, smithy, council_room};
  initializeGame(numPlayers, kingdom, seed, &Game);

  int idx = 0;
  int functionReturnResult = -1;

  struct sigaction *sa;
  sa = malloc(sizeof(struct sigaction));
  sa->sa_handler = INThandler;
  sigaction(SIGINT, sa, NULL);  

  printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);

  for (idx = 0; idx < NUMBER_OF_TESTS; idx++) {
    functionReturnResult = isGameOver(&Game);
    printf("Expected Result: %d, Actual Result %d\n", 0, functionReturnResult);
    assertTrue(0 == functionReturnResult); // when supply count is > 0, game over set to '0'
  }

  Game.supplyCount[province] = 0;

  for (idx = 0; idx < NUMBER_OF_TESTS; idx++) {
    functionReturnResult = isGameOver(&Game);
    printf("Expected Result: %d, Actual Result %d\n", 1, functionReturnResult);
    assertTrue(1 == functionReturnResult); // when supply count is 0, game over set to '1'
  }  

  return 0;
}