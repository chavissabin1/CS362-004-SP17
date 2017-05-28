/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest1.c
 * int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "gainCard()"
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
    
    //int handPos = 1;
    int currentPlayer = whoseTurn(&gs);
    
    //improvement would be to randomize the card to gain
    int cardToGain = estate;
    int flag = -1; //0 for discard
                   //1 for deck
                   //2 for hand
    int cardGained = 1; //1 if no gain attempt
                        //0 if successfully gained
                        //-1 if failed to gain
    
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
           And 
            Test 1: A player is to add a card to her discard
            Test 2: A player is to add a card to her deck
            Test 3: A player is to add a card to her hand
            Test 4: There is no more of the desired card left in the supply
    When: 
    Then: 
        Test 1: The gaining of the card succeeded
            And the current player's discard increases by 1
            And supply decreases by 1 
            And no other player's Dominion is affected
        Test 2: The gaining of the card succeeded
            And the current player's deck increases by 1
            And supply decreases by 1
            And no other player's Dominion is affected
        Test 3: The gaining of the card succeeded
            And the current player's hand increases by 1
            And supply decreases by 1
            And no other player's Dominion is affected
        Test 4: The gaining of the card failed
    */
   
    
///////////////////////////  Test 1: A player is to add a card to her discard //////////////////////////////
    char test1Name[40] = "A player is to add a card to her discard";
    printf("----- Starting Test 1: %s -----\n", test1Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    flag = 0; //add to discard

    int prevDiscardSize = gs.discardCount[currentPlayer];
    int prevSupply = gs.supplyCount[cardToGain];

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    cardGained = gainCard(cardToGain, &testGS, flag, currentPlayer);    

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    //The gaining of the card succeeded
    expected = 0;
    printf("Gaining the card returned %d, Expected %d\n", cardGained, expected);
    my_assert(cardGained, expected);

    //And the current player's discard increases by 1
    int currentDiscardSize = testGS.discardCount[currentPlayer];
    actual = currentDiscardSize;
    expected = prevDiscardSize + 1;
    printf("Previously, the discard count was %d and now it's %d.\n", prevDiscardSize, currentDiscardSize);
    my_assert(actual, expected);
    
    //And supply decreases by 1
    int currentSupply = testGS.supplyCount[cardToGain];
    actual = currentSupply;
    expected = prevSupply - 1;
    printf("Previously, the supply count was %d and now it's %d.\n", prevSupply, currentSupply);
    my_assert(actual, expected);
   
    //And no other player's Dominion is affected
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

#if (DEBUGGER == 1)
    printf("Cleaning up environment.\n");
#endif
    memcpy(&testGS, &gs, sizeof(struct gameState));

    printf("----- Finished Test 1: %s -----\n\n", test1Name);

    
///////////////////////////  Test 2: A player is to add a card to her deck //////////////////////////////
    char test2Name[37] = "A player is to add a card to her deck";
    printf("----- Starting Test 2: %s -----\n", test2Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    flag = 1; //add to deck

    int prevDeckSize = gs.deckCount[currentPlayer];
    prevSupply = gs.supplyCount[cardToGain];

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    cardGained = gainCard(cardToGain, &testGS, flag, currentPlayer);    

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    //The gaining of the card succeeded
    expected = 0;
    printf("Gaining the card returned %d, Expected %d\n", cardGained, expected);
    my_assert(cardGained, expected);

    //And the current player's deck increases by 1
    int currentDeckSize = testGS.deckCount[currentPlayer];
    actual = currentDeckSize;
    expected = prevDeckSize + 1;
    printf("Previously, the deck count was %d and now it's %d.\n", prevDeckSize, currentDeckSize);
    my_assert(actual, expected);
    
    //And supply decreases by 1
    currentSupply = testGS.supplyCount[cardToGain];
    actual = currentSupply;
    expected = prevSupply - 1;
    printf("Previously, the supply count was %d and now it's %d.\n", prevSupply, currentSupply);
    my_assert(actual, expected);
    
    //And no other player's Dominion is affected
    x = 0;
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

#if (DEBUGGER == 1)
    printf("Cleaning up environment.\n");
#endif
    memcpy(&testGS, &gs, sizeof(struct gameState));

    printf("----- Finished Test 2: %s -----\n\n", test2Name);

    
///////////////////////////  Test 3: A player is to add a card to her hand //////////////////////////////
    char test3Name[37] = "A player is to add a card to her hand";
    printf("----- Starting Test 3: %s -----\n", test3Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    flag = 2; //add to hand

    int prevHandSize = gs.handCount[currentPlayer];
    prevSupply = gs.supplyCount[cardToGain];

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    cardGained = gainCard(cardToGain, &testGS, flag, currentPlayer);    

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    //The gaining of the card succeeded
    expected = 0;
    printf("Gaining the card returned %d, Expected %d\n", cardGained, expected);
    my_assert(cardGained, expected);

    //And the current player's hand increases by 1
    int currentHandSize = testGS.handCount[currentPlayer];
    actual = currentHandSize;
    expected = prevHandSize + 1;
    printf("Previously, the hand count was %d and now it's %d.\n", prevHandSize, currentHandSize);
    my_assert(actual, expected);
    
    //And supply decreases by 1
    currentSupply = testGS.supplyCount[cardToGain];
    actual = currentSupply;
    expected = prevSupply - 1;
    printf("Previously, the supply count was %d and now it's %d.\n", prevSupply, currentSupply);
    my_assert(actual, expected);
    
    //And no other player's Dominion is affected
    x = 0;
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

#if (DEBUGGER == 1)
    printf("Cleaning up environment.\n");
#endif
    memcpy(&testGS, &gs, sizeof(struct gameState));

    printf("----- Finished Test 3: %s -----\n\n", test3Name);

    
///////////////////////////  Test 4: There is no more of the desired card left in the supply //////////////////////////////
    char test4Name[55] = "There is no more of the desired card left in the supply";
    printf("----- Starting Test 4: %s -----\n", test4Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    flag = 0;
    testGS.supplyCount[cardToGain] = 0;

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    cardGained = gainCard(cardToGain, &testGS, flag, currentPlayer);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    expected = -1;
    printf("Gaining the card returned %d, Expected %d\n", cardGained, expected);
    my_assert(cardGained, expected);

    printf("----- Finished Test 4: %s -----\n\n", test4Name);

  
    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}