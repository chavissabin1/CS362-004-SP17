/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * cardtest2.c
 * int playAdventurer(struct gameState *state)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "playAdventurer()"
#define DEBUGGER 0 //set to 0 to remove debug print statements

int main(){
    printf("---------- START Testing: %s ----------\n", UNDERTEST);
    int numPlayers = 2;
    int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    struct gameState gs, testGS;
    int seed = rand() % 100 + 1;

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    
    initializeGame(numPlayers, kingdom, seed, &gs);
    memcpy(&testGS, &gs, sizeof(struct gameState));
    int currentPlayer = whoseTurn(&gs);
    
    
    /* NEEDS TESTING!!!!!!*/
    int handPos = 1;
    //force specific card into hand
    testGS.hand[currentPlayer][handPos] = adventurer;
#if (DEBUGGER == 1)
    int expected;
    int card = handCard(handPos, &testGS);
    expected = adventurer;
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
    Given: It is the current player's turn
    When: The current player plays Adventurer
    Then: 
          Test1: The current player's hand should increase by two
          Test2: The current player's new cards in hand are Treasures
          Test3: And the current player's discard pile should increase by the number of cards drawn minus two
          Test4: No other player's Dominion should be affected
    */
    
/////////////////////  Test1: The current player's hand should increase by two  /////////////////////////
    char test1Name[40] = "Player's Hand Increases by Two Treasures";
    printf("----- Starting Test 1: %s -----\n", test1Name);

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    playAdventurer(&testGS);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    //make sure handCount has increased by two
    printf("hand count = %d, expected = %d\n", testGS.handCount[currentPlayer], gs.handCount[currentPlayer] + 2);
    my_assert(testGS.handCount[currentPlayer], gs.handCount[currentPlayer] + 2);

    printf("----- Finished Test 1: %s -----\n\n", test1Name);

    
//////////////////  Test 2: The current player's new cards in hand are Treasures ////////////////////////    
    char test2Name[52] = "The current player's new cards in hand are Treasures";
    printf("----- Starting Test 2: %s -----\n", test2Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif

    //get top two cards
    //make sure they are both treasures

    int topCard = testGS.hand[currentPlayer][testGS.handCount[currentPlayer]-1];
    int topCardIsTreasure = 0;
    int secondTopCard = testGS.hand[currentPlayer][testGS.handCount[currentPlayer]-2];
    int secondTopCardIsTreasure = 0;
    
    if(topCard == copper || topCard == silver || topCard == gold) topCardIsTreasure = 1;
    printf("topCardIsTreasure is: %d, topCard is: %d, Expecting 4, 5 or 6\n", topCardIsTreasure, topCard);
    my_assert(topCardIsTreasure, 1);
    
    if(secondTopCard == copper || secondTopCard == silver || secondTopCard == gold) secondTopCardIsTreasure = 1;
    printf("secondTopCardIsTreasure is: %d, topCard is: %d, Expecting 4, 5 or 6\n", secondTopCardIsTreasure, secondTopCard);
    my_assert(secondTopCardIsTreasure, 1);


    printf("----- Finished Test 2: %s -----\n\n", test2Name);


    
//////////  Test3: And the current player's discard pile should increase by the number of cards drawn minus two  //////
    char test3Name[92] = "And the current player's discard pile should increase by the number of cards drawn minus two";
    printf("----- Starting Test 3: %s -----\n", test3Name);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
//get current size of discard pile
//get number of cards drawn during Adventurer (can I do this without having playAdventurer() provide more info outside it's namespace?
//oooooh!  I can compare originalDeckCount + originalDiscardCount == currentDeckCount + currentDiscardCount + 2
    int originalDeckCount = gs.deckCount[currentPlayer];
    int originalDiscardCount = gs.discardCount[currentPlayer];

    int currentDeckCount = testGS.deckCount[currentPlayer];
    int currentDiscardCount = testGS.discardCount[currentPlayer]; 

    printf("Original Deck Count is: %d, Original Discard Count is: %d.  Total: %d\n", originalDeckCount, originalDiscardCount, (originalDeckCount + originalDiscardCount));
    printf("Current Deck Count is: %d, Current Discard Count is: %d.  Total w/ Treasures: %d\n", currentDeckCount, currentDiscardCount, (currentDeckCount + currentDiscardCount + 2));
    //printf("Expected: ");

    my_assert( originalDeckCount + originalDiscardCount, currentDeckCount + currentDiscardCount + 2);

    printf("----- Finished Test 3: %s -----\n\n", test3Name);    
    
///////////////////  Test4: No Other Players' Dominion Is Affected  //////////////////////////
    char test4Name[38] = "No Other Players' Dominion Is Affected";
    printf("----- Starting Test 4: %s -----\n", test4Name);
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
    printf("----- Finished Test 4: %s -----\n\n", test4Name);
    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}