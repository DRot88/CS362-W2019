/*****************************
* Author: Daniel Rotenberg
* Filename: unitTest4.c
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
* unitTest4: unitTest4.c dominion.o rngs.o interface.o
*      gcc -o unitTest4 -g  unitTest4.c dominion.o rngs.o interface.o $(CFLAGS)
************************************************************************/
#define NUMBER_OF_TESTS 100
#define FUNCTION "getCost"

// function definition in dominion.c

// int getCost(int cardNumber)


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

  // struct gameState Game;
  int idx = 0;
  int cardNumber = 0;
  int functionReturnResult = 0;
  int expectedCost = -1;
  char cardName[MAX_STRING_LENGTH];

  struct sigaction *sa;
  sa = malloc(sizeof(struct sigaction));
  sa->sa_handler = INThandler;
  sigaction(SIGINT, sa, NULL);  

  printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);


// CARD COSTS
// curse, copper = 0
// estate, embargo = 2
// village, great_hall, ambassador, steward, silver = 3
// feast, gardens, remodel, smithy, baron, cutpurse, treasure_map, sea_hag, salvager = 4   
// duchy, council_room, mine, minion, tribute, outpost = 5
// adventurer, gold  = 6
// province = 8
  
  for (idx = 0; idx < NUMBER_OF_TESTS; idx++) {
    cardNumber = rand() % 27;
    functionReturnResult = getCost(cardNumber);
    cardNumToName(cardNumber, cardName);
    if (cardNumber == curse || cardNumber == copper) {
      expectedCost = 0;
    } else if (cardNumber == estate || cardNumber == embargo) {
      expectedCost = 2;
    } else if (cardNumber == village || cardNumber == great_hall || cardNumber == ambassador || cardNumber == steward || cardNumber == silver) {
      expectedCost = 3;
    } else if (cardNumber == feast || cardNumber == gardens || cardNumber == remodel || cardNumber == smithy || cardNumber == baron 
              || cardNumber == cutpurse || cardNumber == sea_hag || cardNumber == salvager || cardNumber == treasure_map ) {
      expectedCost = 4;
    } else if (cardNumber == outpost || cardNumber == minion || cardNumber == tribute || cardNumber == mine || cardNumber == duchy || cardNumber == council_room) {
      expectedCost = 5;
    } else if (cardNumber == adventurer || cardNumber == gold) {
      expectedCost = 6;
    } else if (cardNumber == province) {
      expectedCost = 8;
    } else {
      expectedCost = -1;
    }

    printf("Card Name: %s, Expected Cost: %d, Function Result Cost: %d\n", cardName, expectedCost ,functionReturnResult);
    assertTrue(expectedCost == functionReturnResult);
  }

  return 0;
}


