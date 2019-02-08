/*****************************
* Author: Daniel Rotenberg
* Filename: cardTest4.c
******************************/

/***********************************************************************
* Include the following lines in your makefile:
*
* cardTest4: cardTest4.c dominion.o rngs.o
*      gcc -o cardtest4 -g  cardTest4.c dominion.o rngs.o $(CFLAGS)
************************************************************************/

#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <signal.h>


#define TESTCARD "sea_hag"

//sea_hag implementation in dominion.c

// case sea_hag:
//   for (i = 0; i < state->numPlayers; i++){
//     if (i != currentPlayer){
//       state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];          
//       state->deckCount[i]--;
//       state->discardCount[i]++;
//       state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
//     }
//   }
//   return 0;

// assertTrue function so testing continues

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
  int kingdom[10] = {adventurer, sea_hag, village, minion, mine, cutpurse,
      remodel, tribute, smithy, council_room};
  int seed = 2300;
  struct gameState GS, testGS;

  // Storage for cards
  int handCardCount = 0;
  int handCardCount2 = 0;
  int newCards = 0; // sea_hag does not increase cards in hand
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
  int expectedActionCount = 0;

  // variable for curse card name
  char curse[MAX_STRING_LENGTH] = "Curse";

  // Initialize Game State and Player Cards
  initializeGame(playerCount,kingdom,seed, &GS);

  // Inform user which card is being tested
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: Using sea_hag does not add new cards --------------
  printf("TEST 1: sea_hag adds no new cards after being played\n");

  // copy GameState to a test case
  memcpy(&testGS, &GS, sizeof(struct gameState));

  // get card count in hand
  handCardCount = numHandCards(&GS);
  printf("Cards in Hand BEFORE playing sea_hag: %d\n", handCardCount);

  // play sea_hag card
  cardEffect(sea_hag, choice1, choice2, choice3, &testGS, handpos, &bonus);

  // get card count in hand
  handCardCount2 = numHandCards(&testGS);
  printf("Cards in Hand AFTER playing sea_hag: %d\n", handCardCount2);
  printf("Hand Count = %d, Expected = %d\n", testGS.handCount[playerOne], GS.handCount[playerOne] + newCards - discarded);
  assertTrue(testGS.handCount[playerOne] == GS.handCount[playerOne] + newCards - discarded);

  // ----------- TEST 2: Test Return Value --------------
  printf("TEST 2: Testing Return Value\n");
  
  // copy GameState to a test case  
  memcpy(&testGS, &GS, sizeof(struct gameState));

  retValue = cardEffect(sea_hag, choice1, choice2, choice3, &testGS, handpos, &bonus);
  printf("Return Value: %d, Expected: %d\n", retValue, expectedValue);
  assertTrue(retValue == expectedValue);

  // ----------- TEST 3: Test Action Count --------------
  printf("TEST 3: Testing Action Count\n");

  // copy GameState to a test case  
  memcpy(&testGS, &GS, sizeof(struct gameState));  

  // get current actions before playing card
  actionCount = GS.numActions;
  printf("Actions BEFORE playing sea_hag: %d\n", actionCount);

  // play sea_hag card
  cardEffect(sea_hag, choice1, choice2, choice3, &testGS, handpos, &bonus);

  //reduce number of actions after playing sea_hag action card
  testGS.numActions--;
  // get action count after playing card
  testActionCount = testGS.numActions;
  printf("Actions AFTER playing sea_hag: %d\n", testActionCount);
  printf("Action Count: %d, Expected Action Count: %d\n", testActionCount, expectedActionCount);
  assertTrue(testActionCount == expectedActionCount);

  // ----------- TEST 4: Other Players Discard Top Card --------------
  printf("TEST 4: Testing if Other Players Discard Top Card\n");

  for (int i = 0; i < playerCount; i++) {
    if (i != GS.whoseTurn) {
      // copy GameState to a test case    
      memcpy(&testGS, &GS, sizeof(struct gameState));  
      printf("Player %d Discard Count BEFORE Sea Hag: %d\n",i,GS.discardCount[i]);

      // play sea_hag card
      cardEffect(sea_hag, choice1, choice2, choice3, &testGS, handpos, &bonus);

      printf("Player %d Discard Count AFTER Sea Hag: %d\n",i,testGS.discardCount[i]);
      assertTrue(GS.discardCount[i] != testGS.discardCount[i]);
    }
  }

  // ----------- TEST 5: Other Players Gain Curse Onto Deck --------------
  printf("TEST 5: Testing if Other Players Gain Curse Onto Deck\n");

  // copy GameState to a test case  
  memcpy(&testGS, &GS, sizeof(struct gameState));  

  // play sea_hag card
  cardEffect(sea_hag, choice1, choice2, choice3, &testGS, handpos, &bonus);

  for(int i = 0; i < playerCount; i++) {
    if (i == testGS.whoseTurn) {
      continue;
    } else {
      int card = testGS.hand[i][0];
      char name[MAX_STRING_LENGTH];
      cardNumToName(card, name);
      printf("Player %d Card on top of deck: %s\n", i, name);
      
      int correctCard = -1;
      if (strcmp(name,curse) == 0) {
        correctCard = 1;
      }
      assertTrue(correctCard);
    }
  }

  return 0;
}