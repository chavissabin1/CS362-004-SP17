/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * cardtest4.c
 * int playVillage(struct gameState *state, int handPos)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "playVillage()"
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
    int currentPlayer = whoseTurn(&gs);

    //force village card into hand
    testGS.hand[currentPlayer][handPos] = village;
    int card = handCard(handPos, &testGS);
    expected = village;
    printf("card is %d, expected: %d\n", card, expected);
    
#if (DEBUGGER == 1)
    printf("***Initial game state:*** \n");
    printf("**Current Player: %d**\n", currentPlayer);
    //print current player's hand
    int i;
    for (i = 0; i < numHandCards(&testGS); i++){
        printf("Card at hand position %d is %d.\n", i, handCard(i, &testGS));
    }
#endif


    /* TEST SUITE
    Gherkin:
    Given: The game has started
    When: The current player plays Village
    Then: 
        Test 1: Current player adds one card to her hand
        Test 2: Current player gets two additional actions
        Test 3: No other player's Dominion is affected
    */

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    playVillage(&testGS, handPos);
    
///////////////////////////  Test 1: Current player adds one card to her hand //////////////////////////////
    char test1Name[40] = "Current player adds one card to her hand";
    printf("----- Starting Test 1: %s -----\n", test1Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    actual = numHandCards(&testGS);
    expected = numHandCards(&gs) + 0; //gain a card, but also discard Village
    printf("Current number of cards is: %d, Expected: %d\n", actual, expected);
    my_assert(actual, expected);

    printf("----- Finished Test 1: %s -----\n\n", test1Name);
    
    
    
///////////////////////////  Test 2: Current player gets two additional actions //////////////////////////////
    char test2Name[42] = "Current player gets two additional actions";
    printf("----- Starting Test 2: %s -----\n", test2Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif

    actual = testGS.numActions;
    expected = gs.numActions + 2;
    /* DEBUGGING for intentional bug in playVillage()
    int numCoins = gs.coins;
    printf("Number of coins is: %d\n", numCoins);
    */
    printf("Current number of actions is: %d, Expected: %d\n", actual, expected);
    my_assert(actual, expected);

#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 2: %s -----\n\n", test2Name);


//////////////////////////  Test3: No Other Players' Dominion Is Affected  ////////////////////
    char test3Name[38] = "No Other Players' Dominion Is Affected";
    printf("----- Starting Test 3: %s -----\n", test3Name);
    int x = 0;
    while (x < numPlayers){
#if (DEBUGGER == 1)        
        printf("x is: %d\n", x);
        printf("currentPlayer is: %d\n", currentPlayer);
#endif
        if (x == currentPlayer) x++;
        else{
            printf("Player %d's hand count = %d, expected = %d\n", x, testGS.handCount[x], gs.handCount[x]);
            my_assert(testGS.handCount[x], gs.handCount[x]);
            printf("Player %d's deck count = %d, expected = %d\n", x, testGS.deckCount[x], gs.deckCount[x]);
            my_assert(testGS.deckCount[x], gs.deckCount[x]);
            printf("Player %d's discard count = %d, expected = %d\n", x, testGS.discardCount[x], gs.discardCount[x]);
            my_assert(testGS.discardCount[x], gs.discardCount[x]);            
            x++;   
        }
    }
    printf("----- Finished Test 3: %s -----\n\n", test3Name);
    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}