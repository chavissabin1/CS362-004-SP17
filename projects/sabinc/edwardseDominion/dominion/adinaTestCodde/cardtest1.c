/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * cardtest1.c
 * int playSmithy()
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "playSmithy()"
#define DEBUGGER 0 //set to 0 to remove debug print statements

int my_assert( int first, int second);

int main(){
    printf("\n\n---------- START Testing: %s ----------\n", UNDERTEST);
    int numPlayers = 2;
    int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    struct gameState gs, testGS;
    int seed = rand() % 100 + 1;
    
    initializeGame(numPlayers, kingdom, seed, &gs);
    memcpy(&testGS, &gs, sizeof(struct gameState));
    
    int handPos = 1;
    int currentPlayer = whoseTurn(&gs);
    
    /* NEEDS TESTING!!!!!!*/
    //force specific card into hand
    testGS.hand[currentPlayer][handPos] = smithy;
#if (DEBUGGER == 1)
    int expected;
    int card = handCard(handPos, &testGS);
    expected = smithy;
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
    Given: The game has started
           And it's the current player's turn
    When: The Smithy card is played
    Then: 
        Test 1: The current player will remove three cards from her deck
                And place them in her hand
        Test 2: No Other Players' Dominion Is Affected
    */

//////////  Test1: Player Puts Three Cards from Deck into Hand  //////
    char test1Name[43] = "Player Puts Three Cards from Deck into Hand";
    printf("----- Starting Test 1: %s -----\n", test1Name);
    
#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    int discarded = 1; /*Discard Smithy once played*/
    int drawnCards = 3; /*Specific to Smithy*/
    int shuffledCards = 0;
    
    memcpy(&testGS, &gs, sizeof(struct gameState));
    

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    playSmithy(&testGS, handPos);

    
#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    printf("hand count = %d, expected = %d\n", testGS.handCount[currentPlayer], gs.handCount[currentPlayer] + drawnCards - discarded);
    my_assert(testGS.handCount[currentPlayer], gs.handCount[currentPlayer] + drawnCards - discarded);
    printf("deck count = %d, expected = %d\n", testGS.deckCount[currentPlayer], gs.deckCount[currentPlayer] - drawnCards + shuffledCards);
    my_assert(testGS.deckCount[currentPlayer], gs.deckCount[currentPlayer] - drawnCards + shuffledCards);

    printf("----- Finished Test 1: %s -----\n\n", test1Name);
    

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
            printf("Player %d's discard count = %d, expected = %d\n", x, testGS.discardCount[x], gs.discardCount[x]);
            my_assert(testGS.discardCount[x], gs.discardCount[x]);   
            x++;   
        }
    }
    printf("----- Finished Test 2: %s -----\n\n", test2Name);
    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}
