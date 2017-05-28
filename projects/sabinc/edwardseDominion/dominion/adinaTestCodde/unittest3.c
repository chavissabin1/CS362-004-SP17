/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest3.c
 * int endTurn(struct gameState *state)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "endTurn()"
#define DEBUGGER 0 //set to 0 to remove debug print statements

int main(){
    printf("---------- START Testing: %s ----------\n", UNDERTEST);
    int numPlayers = 2;
    int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    struct gameState gs, testGS;
    int seed = rand() % 100 + 1;
    int actual, expected;
    
    initializeGame(numPlayers, kingdom, seed, &gs);
    memcpy(&testGS, &gs, sizeof(struct gameState));
    
    int handPos = 1;
    int prevPlayer = whoseTurn(&gs);

    
    //force specific card into hand
    testGS.hand[prevPlayer][handPos] = smithy;
#if (DEBUGGER == 1)
    int card = handCard(handPos, &testGS);
    expected = smithy;
    printf("card is %d, expected: %d\n", card, expected);
#endif
    
#if (DEBUGGER == 1)
    printf("***Initial game state:*** \n");
    printf("**Previous Player: %d**\n", prevPlayer);
    //print previous player's hand
    int i;
    for (i = 0; i < numHandCards(&testGS); i++){
        printf("Card at hand position %d is %d.\n", i, handCard(i, &testGS));
    }
#endif


    /* TEST SUITE
    Gherkin:
    Given: The game has started
           And at least one player (previous player) has played any card
    When: The previous player's turn is over
    Then: 
        Test 1: The previous player discards all cards in her hand and draws five cards from her deck
        Test 2: The next player number is incrementally higher than previous player number, or 0
        Test 3: The next player starts with 1 action
        Test 4: The next player starts with 1 buy
        Test 5: The next player has five cards in her hand
    */
     

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    playSmithy(&testGS, handPos);

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    endTurn(&testGS);
    int nextPlayer = whoseTurn(&testGS);
   
    
///////////////////////////  Test 1: The previous player discards all cards in her hand and draws five cards from her deck //////////////////////////////
    char test1Name[85] = "The previous player discards all cards in her hand and draws five cards from her deck";
    printf("----- Starting Test 1: %s -----\n", test1Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    int prevPlayerHandCount = testGS.handCount[prevPlayer];
    printf("Previous player's hand count is %d, Expected 5.\n", prevPlayerHandCount);
    my_assert(prevPlayerHandCount, 5);

    int prevPlayerOriginalDeckCount = gs.deckCount[prevPlayer];
    int prevPlayerCurrentDeckCount = testGS.deckCount[prevPlayer];
    printf("Previous player's original deck count is %d, current deck count is %d.\n", prevPlayerOriginalDeckCount, prevPlayerCurrentDeckCount);
    my_assert((prevPlayerOriginalDeckCount-5), prevPlayerCurrentDeckCount);

    printf("----- Finished Test 1: %s -----\n\n", test1Name);


///////////////////////////  Test 2: The next player number is incrementally higher than previous player number, or 0 //////////////////////////////
    char test2Name[81] = "The next player number is incrememntally higher than previous player number, or 0";
    printf("----- Starting Test 2: %s -----\n", test2Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    
    actual = nextPlayer;

    printf("Number of players is %d\n", testGS.numPlayers);
    //if prevPlayer was highest numbered player, nextPlayer should be player 0
    if(prevPlayer == testGS.numPlayers - 1){
        expected = 0;
    }
    else { expected = prevPlayer + 1; }

    printf("Previous player was %d, next player is %d.\n", prevPlayer, nextPlayer);
    my_assert(actual, expected);

#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 2: %s -----\n\n", test2Name);


///////////////////////////  Test 3: The next player starts with 1 action //////////////////////////////
    char test3Name[36] = "The next player starts with 1 action";
    printf("----- Starting Test 3: %s -----\n", test3Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    int currentActions = testGS.numActions;
    printf("Current number of actions %d.\n", currentActions);
    my_assert(currentActions, 1);   

#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 3: %s -----\n\n", test3Name);


///////////////////////////  Test 4: The next player starts with 1 buy //////////////////////////////
    char test4Name[32] = "The next player stars with 1 buy";
    printf("----- Starting Test 4: %s -----\n", test4Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    int currentBuys = testGS.numBuys;
    printf("Current number of buys %d.\n", currentBuys);
    my_assert(currentBuys, 1);   

#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 4: %s -----\n\n", test4Name);


///////////////////////////  Test 5: The next player has five cards in her hand //////////////////////////////
    char test5Name[42] = "The next player has five cards in her hand";
    printf("----- Starting Test 5: %s -----\n", test5Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    int nextPlayerHandCount = testGS.handCount[nextPlayer];
    printf("Next player's hand count is %d, Expected 5.\n", nextPlayerHandCount);
    my_assert(nextPlayerHandCount, 5);

#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 5: %s -----\n\n", test5Name);    
    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}