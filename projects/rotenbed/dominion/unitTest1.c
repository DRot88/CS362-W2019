/*****************************
* Author: Daniel Rotenberg
* Filename: unitTest1.c
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
* unitTest1: unitTest1.c dominion.o rngs.o
*      gcc -o unitTest1 -g  unitTest1.c dominion.o rngs.o $(CFLAGS)
************************************************************************/
#define NUMBER_OF_TESTS 100
#define FUNCTION "whoseTurn"

// function definition in dominion.c

// int whoseTurn(struct gameState *state) {
//   return state->whoseTurn;
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

  struct gameState Game;
  int idx = 0;
  int playerNumTurn = 0;
  int functionReturnResult = 0;

  struct sigaction *sa;
  sa = malloc(sizeof(struct sigaction));
  sa->sa_handler = INThandler;
  sigaction(SIGINT, sa, NULL);  

  printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);

  for (idx = 0; idx < NUMBER_OF_TESTS; idx++) {
    playerNumTurn = rand() % 6;
    Game.whoseTurn = playerNumTurn;
    functionReturnResult = whoseTurn(&Game);
    printf("Expected Result: %d, Actual Result %d\n", playerNumTurn, functionReturnResult);
    assertTrue(playerNumTurn == functionReturnResult);
  }

  return 0;
}