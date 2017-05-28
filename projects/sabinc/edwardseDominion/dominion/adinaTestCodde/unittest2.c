/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest2.c
 * int isGameOver(struct gameState *state)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "isGameOver()"
#define DEBUGGER 0 //set to 0 to remove debug print statements

int main(){
    printf("---------- START Testing: %s ----------\n", UNDERTEST);
    int numPlayers = 2;
    int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    struct gameState gs, testGS;
    int seed = rand() % 100 + 1;
    
    initializeGame(numPlayers, kingdom, seed, &gs);
    memcpy(&testGS, &gs, sizeof(struct gameState));
    
    //int handPos = 1;
    
#if (DEBUGGER == 1)
    int currentPlayer = whoseTurn(&gs);
    printf("***Initial game state:*** \n");
    printf("**Current Player: %d**\n", currentPlayer);
    //can we print the current player's hand?
#endif





#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif


#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif


    /* TEST 1
    Gherkin:
    Given: The game has started
           And One player takes a turn
    When: We check isGameOver
    Then: The game should continue 
    */   
    
///////////////////////////  Test 1:  //////////////////////////////
    char test1Name[23] = "One player takes a turn";
    printf("----- Starting Test 1: %s -----\n", test1Name);
#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    int expected = 0;
    playAdventurer(&testGS);

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    int over = isGameOver(&testGS);
    
#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif

    printf("over is: %d, expected is: %d\n", over, expected);
    my_assert(over, expected);

#if (DEBUGGER == 1)
    printf("Reporting information.\n");
#endif

    printf("----- Finished Test 1: %s -----\n\n", test1Name);




    /* TEST 2
    Gherkin:
    Given: The game has started
           And There are zero Province cards left
    When: We check isGameOver
    Then: The game is over 
    */
    
///////////////////////////  Test 2: There are zero Province cards left //////////////////////////////
    char test2Name[34] = "There are zero Province cards left";
    printf("----- Starting Test 2: %s -----\n", test2Name);
#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    expected = 1;
    int prevQuantityProvinces = supplyCount(province, &testGS);
    printf("There were %d provinces, before the environment was set.\n", prevQuantityProvinces);
    testGS.supplyCount[province] = 0;
    printf("Now there are %d provinces.\n", supplyCount(province, &testGS));
    
#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif
    over = isGameOver(&testGS);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif

    printf("over is: %d, expected is: %d\n", over, expected);
    my_assert(over, expected);

#if (DEBUGGER == 1)
    printf("Cleaning up.\n");
#endif
    testGS.supplyCount[province] = prevQuantityProvinces;
    printf("After clean up there are %d provinces.\n", supplyCount(province, &testGS));
    printf("----- Finished Test 2: %s -----\n\n", test2Name);


    


    /* TEST 3
    Gherkin:
    Given: The game has started
           And Three kingdom cards are gone from the Supply
    When: We check isGameOver
    Then: The game is over 
    */
    
    ///////////////////////////  Test 3: Three kingdom cards are gone from the Supply //////////////////////////////
    char test3Name[44] = "Three kingdom cards are gone from the Supply";
    printf("----- Starting Test 3: %s -----\n", test3Name);
#if (DEBUGGER == 1)
    printf("Setting up environment.\n");
#endif
    expected = 1;

    //could be improved by randomizing which supply cards are out
    testGS.supplyCount[council_room] = 0;
    testGS.supplyCount[embargo] = 0;
    testGS.supplyCount[village] = 0;

#if (DEBUGGER == 1)
    printf("Exercising function under test.\n");
#endif

    over = isGameOver(&testGS);

#if (DEBUGGER == 1)
    printf("Asserting game state.\n");
#endif

    printf("over is: %d, expected is: %d\n", over, expected);
    my_assert(over, expected);

    printf("----- Finished Test 3: %s -----\n\n", test3Name);
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}