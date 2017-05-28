/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * cardtest3.c
 * int playFeast(struct gameState *state, int choice1)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "playFeast()"
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
    
    //force feast card into hand
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
        printf("*Card at hand position %d is %d.*\n", i, handCard(i, &testGS));
    }
#endif


    /* TEST SUITE
    Gherkin:
    Given: The game has started
    When: The current player plays Feast
    Then: 
        Test 1: The Feast card is trashed
        Test 2: Current player adds a card costing up to 5 to her discard pile
        Test 3: No other player's Dominion is affected
    */
    /*PLEASE NOTE: playFeast() has an intentional bug in it from Assignment 2.  This bug
    causes the function to enter a condition that prevents it from exiting a loop.
    The bug did not cause the infinite loop itself, but did create the situation where
    a normally acceptable play cannot leave the loop.
    
    The question about turning in unit tests that exercise inifite loops has been asked
    in Piazza (@62) and, as of writting this, has no answer.  For the time being, I have
    removed the intentional bug so running the unit tests avoids hitting the infinite loop.
    
    In a production envionrment, I would discuss the infinite loop issue with the developer,
    and suggest refactoring the function to be more robust (aka, avoid the possibility
    of infinite loops.*/
    printf("\n\n------->>>>>>>NOTE TO TA AND TEACHER: \n An intentional bug from Assignment 2 causes these tests to exercise a condition that falls into an infinite loop.  This intentional bug has been commented out on line 761 of dominion.c so you will not run into the infinite loop.  For more info, please read the comment on line 65 of cardtest3.c.\n\n\n");
     

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif


#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    //could be improved by randomizing the gained card
    printf("Playing Feast now!\n");
    playFeast(&testGS, copper);
    
///////////////////////////  Test 1: The Feast card is trashed //////////////////////////////
    char test1Name[25] = "The Feast card is trashed";
    printf("----- Starting Test 1: %s -----\n", test1Name);
    /*NOTE: This test assumes that playFeast() discards the feast card.
    Other functions that play a card discard of the played card; playFeast()
    does not discard the card.  The feast card explicitly says that the feast
    card should be trashed.  I expect this test to always fail.*/

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    int originalDiscardCount = gs.discardCount[currentPlayer];
    int currentDiscardCount = testGS.discardCount[currentPlayer];
    expected = originalDiscardCount + 1;
    actual = currentDiscardCount;
    printf("Original Discard Count is: %d, Current Discard Count is: %d, Expected: %d\n", originalDiscardCount, actual, expected);
    my_assert(actual, expected);

    printf("----- Finished Test 1: %s -----\n\n", test1Name);
    
   
    
///////////////////////////  Test 2: Current player adds a card costing up to 5 to her discard pile //////////////////////////////
    char test2Name[62] = "Current player adds a card costing up to 5 to her discard pile";
    printf("----- Starting Test 2: %s -----\n", test2Name);

    int sizePrevDiscard = gs.discardCount[currentPlayer];
    int sizeCurrentDiscard = testGS.discardCount[currentPlayer];
    int newCard = testGS.discard[currentPlayer][sizeCurrentDiscard-1];//
    int cost = getCost(newCard);
    
    expected = 1;
    actual = -1;
    if(cost <=5) actual = 1;
    else if(cost > 5) actual = 0;

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif

    printf("Previously, the discard size was %d and now it's %d, which should be 1 more.\n", sizePrevDiscard, sizeCurrentDiscard);
    my_assert((sizePrevDiscard + 1), sizeCurrentDiscard);


    printf("New card is %d, and it's cost is %d\n", newCard, cost);
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