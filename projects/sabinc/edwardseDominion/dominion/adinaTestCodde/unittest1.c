/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest1.c
 * int buyCard(int supplyPos, struct gameState *state)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "buyCard()"
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
    
    //improvement would be to randomize the card to buy
    int cardToBuy = estate;
    int cost = getCost(cardToBuy);
    int cardBought = 1; //1 if no buy attempted
                        //0 if successfully bought
                        //-1 if failed to buy
    
#if (DEBUGGER == 1)
    printf("***Initial game state:*** \n");
    printf("**Current Player: %d**\n", currentPlayer);
    //print current player's hand
    int i;
    for (i = 0; i < numHandCards(&testGS); i++){
        printf("*Card at hand position %d is %d.*\n", i, handCard(i, &testGS));
    }
    printf("*Card to buy is %d and it costs %d*\n", cardToBuy, cost);
#endif


    /* TEST SUITE
    Gherkin:
    Given: The game has started
        Test 1: The current player has enough to buy the card
        Test 2: The current player doesn't have enough to buy the card
        Test 3: The current player has no more buys
        Test 4: There are no more of the desired card in the supply
    When: The current player buys a card
    Then: 
        Test 1: The buy process was successful
            And the current player's discard pile increases by 1
            And the supply of the purchased card decreases by 1
            And the current player's coins decrease by the cost of the purchased card
        Test 2: The buy process is prevented
        Test 3: The buy process is prevented
        Test 4: The buy process is prevented
    */
     

    
///////////////////////////  Test 1: The current player has enough to buy the card //////////////////////////////
    char test1Name[45] = "The current player has enough to buy the card";
    printf("----- Starting Test 1: %s -----\n", test1Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    //int prevCoins = gs.coins;
    testGS.coins = cost;
    int beforeCoins = testGS.coins;
    
    int prevDiscardCount = gs.discardCount[currentPlayer];
    int prevSupply = gs.supplyCount[cardToBuy];
   
#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif    
    cardBought = buyCard(cardToBuy, &testGS); 

 
#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    int currentDiscardCount = testGS.discardCount[currentPlayer];
    int currentSupply = testGS.supplyCount[cardToBuy];

    //The buy process was successful
    expected = 0;
    printf("Buying the card returned %d, Expected %d\n", cardBought, expected);
    my_assert(cardBought, expected);
    
    //And the current player's discard pile increases by 1
    printf("Previous discard pile was %d in size, now it's %d\n", prevDiscardCount, currentDiscardCount);
    my_assert((prevDiscardCount + 1), currentDiscardCount);
    
    //And the supply of the purchased card decreases by 1
    printf("Previous supply amount was %d and now it's %d\n", prevSupply, currentSupply);
    my_assert((prevSupply-1), currentSupply);
    
    //And the current player's coins decrease by the cost of the purchased card
    actual = testGS.coins;
    expected = beforeCoins - cost;
    printf("The current player had %d coins before and now has %d.\n", beforeCoins, actual);
    my_assert(expected, actual);

#if (DEBUGGER == 1)
    printf("Clean up environment.\n");
#endif
    memcpy(&testGS, &gs, sizeof(struct gameState));

    printf("----- Finished Test 1: %s -----\n\n", test1Name);

   
    
///////////////////////////  Test 2: The current player doesn't have enough to buy the card //////////////////////////////
    char test2Name[54] = "The current player doesn't have enough to buy the card";
    printf("----- Starting Test 2: %s -----\n", test2Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    //prevCoins = gs.coins;
    testGS.coins = 0;
   
#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif    
    cardBought = buyCard(cardToBuy, &testGS); 

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    expected = -1;
    printf("Buying the card returned %d, Expected %d\n", cardBought, expected);
    my_assert(cardBought, expected);

#if (DEBUGGER == 1)
    printf("Clean up environment.\n");
#endif
    memcpy(&testGS, &gs, sizeof(struct gameState));
    printf("----- Finished Test 2: %s -----\n\n", test2Name);

   
    
///////////////////////////  Test 3: The current player has no more buys //////////////////////////////
    char test3Name[35] = "The current player has no more buys";
    printf("----- Starting Test 3: %s -----\n", test3Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    //int prevBuys = gs.numBuys;
    testGS.numBuys = 0;
   
#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif    
    cardBought = buyCard(cardToBuy, &testGS);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    expected = -1;
    printf("Buying the card returned %d, Expected %d\n", cardBought, expected);
    my_assert(cardBought, expected);

#if (DEBUGGER == 1)
    printf("Clean up environment.\n");
#endif
    memcpy(&testGS, &gs, sizeof(struct gameState));
    printf("----- Finished Test 3: %s -----\n\n", test3Name);

   
    
///////////////////////////  Test 4: There are no more of the desired card in the supply //////////////////////////////
    char test4Name[51] = "There are no more of the desired card in the supply";
    printf("----- Starting Test 4: %s -----\n", test4Name);

#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    testGS.supplyCount[cardToBuy] = 0;
   
#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif    
    cardBought = buyCard(cardToBuy, &testGS);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif
    expected = -1;
    printf("Buying the card returned %d, Expected %d\n", cardBought, expected);
    my_assert(cardBought, expected);


    printf("----- Finished Test 4: %s -----\n\n", test4Name);


    
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}