/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 4: Random Tester
 * randomtestcard1.c
 * int playSmithy(struct gameState *state, int handPos)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "playSmithy()"
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
    int p = 0;
    int handPos;
    int test[4];
    int quantityTests = sizeof(test)/sizeof(test[0]);
    int testNum = 0;
    int aTestFailed[quantityTests];
    int deckLocation = 0;
    int card = 0;
    int discarded = -1;
    //int newCards = 0;
    int originalDeckCount;
    int originalDiscardCount;
    
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
        //gs.deckCount[currentPlayer] = 0;
        gs.deckCount[currentPlayer] = floor(Random() * MAX_DECK); //shift probability to a small number to exercise shuffling
        gs.handCount[currentPlayer] = floor(Random() * MAX_HAND);
        gs.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
        handPos = floor(Random() * gs.handCount[currentPlayer]);
        gs.numActions = floor(Random() * 5);
        gs.playedCardCount = floor(Random() * MAX_DECK);
        
        /*force deckCount to be small sometimes
        this exercises shuffle() more than having magnitutes more test iterations*/
/*         if(i < TEST_ITERATIONS/10){
            gs.deckCount[currentPlayer] = floor(Random() * 5);
        } */
        /*Give all players semi-realistic decks, discards and hands*/
        for(p=0; p<MAX_PLAYERS; p++){
            /*for player p, set DECK to be real cards*/
            for(deckLocation = 0; deckLocation < gs.deckCount[p]; deckLocation++){
                card = floor(Random() * 27); //any card in game
                gs.deck[p][deckLocation] = card;
                //printf("A %d was shoved into player %d's DECK at position %d.\n", card, p, deckLocation);
            }
            
            /*for player p, set DISCARD to be real cards, in case we have to shuffle*/
            for(deckLocation = 0; deckLocation < gs.discardCount[p]; deckLocation++){
                card = floor(Random() * 27); //any card in game
                gs.discard[p][deckLocation] = card;
                //printf("A %d was shoved into player %d's DISCARD at position %d.\n", card, p, deckLocation);
            }
            
            
            /*for player p, set the HAND to be real cards*/
            for(deckLocation = 0; deckLocation < gs.handCount[p]; deckLocation++){
                if(p == currentPlayer && deckLocation == handPos){ //put a village card in the currentPlayer's hand at handPos
                    card = smithy;
                }
                else{   
                    card = floor(Random() * 27); //any card in game
                 }
                gs.hand[p][deckLocation] = card;
                //printf("A %d was shoved into player %d's HAND at position %d.\n", card, p, deckLocation);
            }    
        }
        
        
        
        /*Copy after making random inputs*/
        memcpy(&testGS, &gs, sizeof(struct gameState));
        //printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d, handPos: %d\n\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer], handPos);
/*        if(gs.deckCount[currentPlayer] < 6){
            printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d\n\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer]);
        } */
            
            
        /*Call function under test*/
        playSmithy(&gs, handPos);
        
        
        /*Oracle Code*/
        
        // 0. Current player removes 3 cards from deck        
        //printf("Deck count before playing smithy: %d, deck count after playing smithy: %d.\n", testGS.deckCount[currentPlayer], gs.deckCount[currentPlayer]);
        originalDeckCount = testGS.deckCount[currentPlayer];
        originalDiscardCount = testGS.discardCount[currentPlayer];
        if(testGS.deckCount[currentPlayer] < 3){
            int y = 0;
            for(y=0; y<testGS.discardCount[currentPlayer]; y++){
                testGS.deck[currentPlayer][y] = testGS.discard[currentPlayer][y];
                testGS.discard[currentPlayer][y] = -1;
            }
            testGS.deckCount[currentPlayer] = testGS.discardCount[currentPlayer] + originalDeckCount;
            testGS.discardCount[currentPlayer] = 0;
        }    
        testGS.deckCount[currentPlayer] = testGS.deckCount[currentPlayer] - 3;
        
        // 1. Current player adds 3 cards to hand, and discards Smithy
        testGS.handCount[currentPlayer] = testGS.handCount[currentPlayer] + 2;

        // 2. Current player discards Smithy card
        discarded = testGS.discard[currentPlayer][testGS.discardCount[currentPlayer]-1];
        //printf("Discarded card is %d\n", discarded);
        
        // 3. No other player's Dominion is affected
        
        
        
        /*Assert actual and expected*/
        for(testNum = 0; testNum < quantityTests; testNum++){
            switch (testNum){
                case 0:  // 0. Current player removes 3 cards from deck 
                    test[testNum] = my_assert(gs.deckCount[currentPlayer], testGS.deckCount[currentPlayer]);
                    if(!test[testNum]){
                        //printf("Interation: %d, Whose Turn: %d, Original Deck Count: %d, Current Deck Count: %d, Hand Count: %d, Discard Count: %d, handPos: %d\n", i, gs.whoseTurn, originalDeckCount, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer], handPos);
                        //printf("Interation: %d, Original Deck Count: %d, Current Deck Count: %d, Original Discard Count: %d, Discard Count: %d\n", i, originalDeckCount, gs.deckCount[currentPlayer], originalDiscardCount, gs.discardCount[currentPlayer]);
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("The player actually has a deck count of %d, where we expected %d.\n\n", gs.deckCount[currentPlayer], testGS.deckCount[currentPlayer]);
                        aTestFailed[testNum]++;
                    }
                    break;
                case 1:  // 1. Current player adds 3 cards to hand, and discards Smithy
                    test[testNum] = my_assert(gs.handCount[currentPlayer], testGS.handCount[currentPlayer]);
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("The hand count is %d, where we expected %d.\n\n", gs.handCount[currentPlayer], testGS.handCount[currentPlayer]);
                        aTestFailed[testNum]++;
                    }
                    break;
                case 2:  // 2. Current player discards Smithy card
                    test[testNum] = my_assert(gs.discard[currentPlayer][gs.discardCount[currentPlayer]-1], discarded);
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("The discarded card is %d, where we expected %d (which should be 13).\n\n", gs.discard[currentPlayer][gs.discardCount[currentPlayer]-1], discarded);
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