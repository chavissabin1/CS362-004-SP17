/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest1.c
 * int fullDeckCount(int player, int card, struct gameState *state)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "fullDeckCount()"
#define DEBUGGER 1 //set to 0 to remove debug print statements

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
    
    //force specific card into hand
    testGS.hand[currentPlayer][handPos] = feast;
#if (DEBUGGER == 1)
    int card = handCard(handPos, &testGS);
    expected = feast;
    printf("card is %d, expected: %d\n", card, expected);
#endif
    
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
    Given: 
    When: 
    Then: 
        Test 1: 
        Test 2: 
    */
     

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif


#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
   
    
///////////////////////////  Test 1:  //////////////////////////////
    char test1Name[TODO] = "";
    printf("----- Starting Test 1: %s -----\n", test1Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif


#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 1: %s -----\n\n", test1Name);

//TODO put fixed Test2 code here
//////////////////////////  Test2: No Other Players' Dominion Is Affected  ////////////////////
    char test2Name[38] = "No Other Players' Dominion Is Affected";
    printf("----- Starting Test 2: %s -----\n", test2Name);
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
            x++;   
        }
    }
    printf("----- Finished Test 2: %s -----\n\n", test2Name);
    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}