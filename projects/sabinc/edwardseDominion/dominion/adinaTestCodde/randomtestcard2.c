/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 4: Random Tester
 * randomtestcard2.c
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
#define TEST_ITERATIONS 10000

int main(){
    //Input: gameState gs, handPos
    //  Important Inputs:
    //      currentPlayer
    //      cardDrawn (may have to hardcode this one)
    //Generate random inputs
    //  Initialize game, but then "randomly" fix the important inputs
    //Call SUT
    //Modify testGS to the outcome expected of playAdventurer
    //Assert that gs and testGS are the same, at least where it counts (oracle code)
    
    //Run, get coverage
    //Update generated inputs
    //  Increase propability of interesting values
    //  Hard code cases that should definitely be exercised
    //Break the SUT
    //  Update test if it doesn't catch the new bug
    //Strengthen oracle code
    
    
    printf("---------- START Testing: %s ----------\n", UNDERTEST);
    //int numPlayers = 2;
    //int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	//		sea_hag, tribute, smithy, council_room};
    struct gameState gs, testGS;
    int seed = rand() % 100 + 1;
    int currentPlayer;
    //int deckCount[MAX_DECK];
    
    /*Randomization*/
    SelectStream(2); //what does this do?
    PutSeed(seed); //puts a seed into the random generator
    int i = 0;
    int n = 0;
    int x = 0;
    int handPos;
    int test[4];
    int quantityTests = sizeof(test)/sizeof(test[0]);
    int testNum = 0;
    int aTestFailed[quantityTests];
    int deckLocation = 0;
    int card = 0;
    int discarded;
    
    //make sure all variables are initialized--don't use at end
    //initializeGame(numPlayers, kingdom, seed, &gs);    
    
/*     printf("MAX_PLAYERS is: %d\n", MAX_PLAYERS);
    printf("MAX_DECK is: %d\n", MAX_DECK); */
    
    /*Initialize failed tests to 0*/
    for(testNum=0;testNum<quantityTests;testNum++){
        aTestFailed[testNum] = 0;
    }
    
    /*Run test case TEST_ITERATIONS times*/
    for(i=0; i< TEST_ITERATIONS ; i++){
        
        /*Randomly initialize game*/
        for(n=0; n <sizeof(struct gameState); n++){
            ((char*)&gs)[n] = floor(Random() * 256);
        }

        gs.whoseTurn = floor(Random() * MAX_PLAYERS);
        currentPlayer = gs.whoseTurn;
        gs.deckCount[currentPlayer] = floor(Random() * MAX_DECK); //shift probability to a small number to exercise shuffling
        gs.handCount[currentPlayer] = floor(Random() * MAX_HAND);
        gs.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
        handPos = floor(Random() * gs.handCount[currentPlayer]);
        gs.numActions = floor(Random() * 5); //some reasonable number of actions
        gs.playedCardCount = floor(Random() * MAX_DECK);
        
        /*force deckCount to be small sometimes
        this exercises shuffle() more than having magnitutes more test iterations*/
/*         if(i < TEST_ITERATIONS/10){
            gs.deckCount[currentPlayer] = floor(Random() * 5);
        } */
        
        /*for the current player only, set DECK to be real cards*/
        for(deckLocation = 0; deckLocation < gs.deckCount[currentPlayer]; deckLocation++){
            card = floor(Random() * 26); //any card in game
            gs.deck[currentPlayer][deckLocation] = card;
            //printf("A %d was shoved into player %d's DECK at position %d.\n", card, currentPlayer, deckLocation);
        }
        
        /*for the current player only, set DISCARD to be real cards, in case we have to shuffle*/
        for(deckLocation = 0; deckLocation < gs.discardCount[currentPlayer]; deckLocation++){
            card = floor(Random() * 26); //any card in game
            gs.discard[currentPlayer][deckLocation] = card;
            //printf("A %d was shoved into player %d's DISCARD at position %d.\n", card, currentPlayer, deckLocation);
        }
        
        
        /*for the current player only, set the HAND to be real cards*/
        for(deckLocation = 0; deckLocation < gs.handCount[currentPlayer]; deckLocation++){
            if(deckLocation == handPos){ //put a village card in at handPos
                card = village;
            }
            else{   
                card = floor(Random() * 26); //any card in game
             }
            gs.hand[currentPlayer][deckLocation] = card;
            //printf("A %d was shoved into player %d's HAND at position %d.\n", card, currentPlayer, deckLocation);
        }
        
        
        /*Copy after making random inputs*/
        memcpy(&testGS, &gs, sizeof(struct gameState));
        //printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d, handPos: %d\n\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer], handPos);
/*        if(gs.deckCount[currentPlayer] < 6){
            printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d\n\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer]);
        } */
            
            
        /*Call function under test*/
        playVillage(&gs, handPos);
        
        
        /*Oracle Code*/
        
        // 0. Current player removes 1 card from deck        
        //printf("Deck count before playing village: %d, deck count after playing village: %d.\n", testGS.deckCount[currentPlayer], gs.deckCount[currentPlayer]);
        testGS.deckCount[currentPlayer] = testGS.deckCount[currentPlayer] - 1;
        
        // 1. Current player discards Village card
        discarded = testGS.discard[currentPlayer][testGS.discardCount[currentPlayer]-1];
        //printf("Discarded card is %d\n", discarded);

        // 2. Current player gets 2 additional actions
        //printf("Originally, current player had %d actions.  After playing village, she has %d actions.\n", testGS.numActions, gs.numActions);
        //NOTE: Due to intentional bug, gs.numActions will be set to gs.coins, which was poorly initialized because it wasn't supposed to be part of playVillage()
        testGS.numActions = testGS.numActions + 2;
        
        // 3. No other player's Dominion is affected
        
        
        
        /*Assert actual and expected*/
        for(testNum = 0; testNum < quantityTests; testNum++){
            switch (testNum){
                case 0:  // 0. Current player removes 1 card from deck
                    test[testNum] = my_assert(gs.deckCount[currentPlayer], testGS.deckCount[currentPlayer]);
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d, handPos: %d\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer], handPos);
                        //printf("The player actually has a deck count of %d, where we expected %d.\n", gs.deckCount[currentPlayer], testGS.deckCount[currentPlayer]);
                        aTestFailed[testNum]++;
                    }
                    break;
                case 1:  // 1. Current player discards Village card
                    test[testNum] = my_assert(gs.discard[currentPlayer][gs.discardCount[currentPlayer]-1], discarded);
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("The discarded card is %d, where we expected %d.\n\n", gs.discard[currentPlayer][gs.discardCount[currentPlayer]-1], discarded);
                        //printf("The discarded card is %d, where we expected %d (which should be 14).\n\n", gs.discard[currentPlayer][gs.discardCount[currentPlayer]-1], discarded);
                        aTestFailed[testNum]++;
                    }
                    break;
                case 2:  // 2. Current player gets 2 additional actions
                    test[testNum] = my_assert(gs.numActions, testGS.numActions);
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("The current player's number of actions is %d, where we expected %d.\n", gs.numActions, testGS.numActions);
                        aTestFailed[testNum]++;
                    }
                    break;
                case 3:  // 3. No other player's Dominion is affected
                    test[3] = 1;
                    for(x=0; x < MAX_PLAYERS; x++){
                        if (x == currentPlayer) continue;
                        else{
                            test[3] = test[3] & my_assert(gs.handCount[x], testGS.handCount[x]);
                            test[3] = test[3] & my_assert(gs.deckCount[x], testGS.deckCount[x]);
                            test[3] = test[3] & my_assert(gs.discardCount[x], testGS.discardCount[x]);
                        }
                    }
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        aTestFailed[testNum]++;
                    }
                    break;
/* 
                case 1:
                    test[testNum] = 
                    if(!test[testNum]){
                        printf("Test %d FAILED\n", testNum);
                        aTestFailed[testNum]++;
                    }
                    break;
                 */
                default:
                    printf("NO CASE FOR TEST %d\n", testNum);
            }
        }
    }  

    /*Report results*/
    for(testNum = 0; testNum < quantityTests; testNum++){
        if(aTestFailed[testNum] > 0){
            printf("Test %d FAILED %d times.\n", testNum, aTestFailed[testNum]);
        }
        else{
            printf("Test %d PASSED! :D\n", testNum);
        }
    }  
    printf("Executed %d tests %d times.\n", quantityTests, TEST_ITERATIONS);
    printf("---------- COMPLETED Testing: %s ----------\n\n\n", UNDERTEST);
    
    return 0;
}