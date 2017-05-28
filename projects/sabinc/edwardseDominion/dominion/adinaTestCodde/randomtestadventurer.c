/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 4: Random Tester
 * randomtestadventurer.c
 * int playAdventurer(struct gameState *state, int handPos)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "my_assert.h"
#include "rngs.h"
#include <stdlib.h>

#define UNDERTEST "playAdventurer()"
#define TEST_ITERATIONS 10000

int main(){
    //Input: gameState gs
    //  Important Inputs:
    //      currentPlayer
    //      deckCount[currentPlayer]
    //          0, 1, <3, <5, MAX_DECK
    //      cardDrawn (may have to hardcode this one)
    //          copper, silver, gold, others
    //      handCount[currentPlayer] -- if hardcoding cardDrawn, be careful about handCount
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
    int test[3];
    int quantityTests = sizeof(test)/sizeof(test[0]);
    int testNum = 0;
    int aTestFailed[quantityTests];
    int deckLocation = 0;
    int card = 0;
    int count = 0;
    
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
        //uh...I don't trust Random() and I don't trust using * instead of % here
        // https://linux.die.net/man/3/random
        gs.whoseTurn = floor(Random() * MAX_PLAYERS);
        currentPlayer = gs.whoseTurn;

        //cardDrawn; //look into drawCard and how to stack deck to my favor
        
        /*force deckCount to be small sometimes
        this exercises shuffle() more than having magnitutes more test iterations*/
/*         if(i < TEST_ITERATIONS/10){
            gs.deckCount[currentPlayer] = floor(Random() * 5);
        } */
        
        /*Give all players semi-realistic decks, discards and hands*/
        count = 0;
        for(p=0; p<MAX_PLAYERS; p++){
            gs.deckCount[p] = floor(Random() * MAX_DECK); //shift probability to a small number to exercise shuffling
            gs.handCount[p] = floor(Random() * MAX_HAND);
            gs.discardCount[p] = floor(Random() * MAX_DECK);
            
            /*for player p, set DECK to be real cards*/
            for(deckLocation = 0; deckLocation < gs.deckCount[p]; deckLocation++){ //add treasures to deck, randomly
                if(p == currentPlayer){
                    count++;
                    if( count % 5 == 0){
                        card = floor(Random() * 3 + 4); //value between copper and gold
                        gs.deck[currentPlayer][deckLocation] = card;
                        //printf("At iteration %d, a %d was shoved into player %d's deck at position %d.\n", i, card, currentPlayer, deckLocation);
                    }
                    else{
                        card = floor(Random() * 26); //any card in game, including treasures
                        gs.deck[currentPlayer][deckLocation] = card;
                        //printf("A %d was shoved into player %d's deck at position %d.\n", card, currentPlayer, deckLocation);
                    }
                }
                 else{ //if not current Player
                    card = floor(Random() * 26); //any card in game, including treasures
                    gs.deck[p][deckLocation] = card;
                    //printf("A %d was shoved into player %d's deck at position %d.\n", card, currentPlayer, deckLocation);
                } 
            }
            
            /*for player p, set DISCARD to be real cards, in case we have to shuffle*/
            for(deckLocation = 0; deckLocation < gs.discardCount[p]; deckLocation++){
                    card = floor(Random() * 26); //any card in game
                    gs.discard[p][deckLocation] = card;
                    //printf("A %d was shoved into player %d's discard at position %d.\n", card, p, deckLocation);
            }
            
            
            /*for player p, set the HAND to be real cards*/
            for(deckLocation = 0; deckLocation < gs.handCount[p]; deckLocation++){
                    card = floor(Random() * 26); //any card in game
                    gs.hand[p][deckLocation] = card;
                    //printf("A %d was shoved into player %d's hand at position %d.\n", card, p, deckLocation);
            }
            
        }
        
        /*Copy after making random inputs*/
        memcpy(&testGS, &gs, sizeof(struct gameState));
/*         printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d\n\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer]);
        if(gs.deckCount[currentPlayer] < 6){
            printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d\n\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer]);
        } */
            
        /*Call function under test*/
        playAdventurer(&gs);
        
        /*Oracle Code*/
        // 0. Current player has two additional treasures
        testGS.handCount[currentPlayer] = testGS.handCount[currentPlayer]+2;
            //IMPROVEMENT--check that top cards are treasures
            //will need to force some treasures into random input for this
        
        // 1. The total of (deckCount + discardCount) has dropped by 2
        //If all but two cards are drawn from the deck and put into the discard,
        //then (testGS.deckCount + testGS.discardCount) = (gs.deckCount + gs.discardCount + 2)
        //wait, does playAdventurer discard the Adventurer card? no
        int deckSize = testGS.deckCount[currentPlayer];
        int discardSize = testGS.discardCount[currentPlayer];
        
        // 2. No other player's Dominion is affected
        
        /*Assert actual and expected*/
        for(testNum = 0; testNum < quantityTests; testNum++){
            switch (testNum){
                case 0:  // 0. The current player's hand increases by 2
                    test[testNum] = my_assert(gs.handCount[currentPlayer], testGS.handCount[currentPlayer]);
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        aTestFailed[testNum]++;
                    }
                    break;
                    
                case 1:  // 1. The total of (deckCount + discardCount) has dropped by 2
                    test[testNum] = my_assert( (gs.deckCount[currentPlayer] + gs.discardCount[currentPlayer] + 2) , (deckSize + discardSize) );
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        aTestFailed[testNum]++;
                    }
                    break;
                    
                case 2:  // 2. No other player's Dominion is affected
                    test[testNum] = 1;
                    for(x=0; x < MAX_PLAYERS; x++){
                        if (x == currentPlayer) continue;
                        else{
                            test[2] = test[2] & my_assert(gs.handCount[x], testGS.handCount[x]);
                            //if(test[2]==0){printf("my_assert(gs.handCount[x], testGS.handCount[x]): %d\n", my_assert(gs.handCount[x], testGS.handCount[x]));}
                            test[2] = test[2] & my_assert(gs.deckCount[x], testGS.deckCount[x]);
                            //if(test[2]==0){printf("my_assert(gs.deckCount[x], testGS.deckCount[x]): %d\n", my_assert(gs.deckCount[x], testGS.deckCount[x]));}
                            test[2] = test[2] & my_assert(gs.discardCount[x], testGS.discardCount[x]);
                            //if(test[2]==0){printf("For player %d, the actual discardCount is %d and the expected discardCount is %d\n", x, gs.discardCount[x], testGS.discardCount[x]);}
                        }
                    }
                    if(!test[testNum]){
                        //printf("Test %d FAILED during iteration %d.\n", testNum, i);
                        //printf("test[2]: %d\n\n\n", test[2]);
                        //printf("my_assert(gs.handCount[x], testGS.handCount[x]): %d\n", my_assert(gs.handCount[x], testGS.handCount[x]));
                        //printf("my_assert(gs.deckCount[x], testGS.deckCount[x]): %d\n", my_assert(gs.deckCount[x], testGS.deckCount[x]));
                        //printf("my_assert(gs.discardCount[x], testGS.discardCount[x]): %d\n", my_assert(gs.discardCount[x], testGS.discardCount[x]));
                        //printf("Interation: %d, Whose Turn: %d, Deck Count: %d, Hand Count: %d, Discard Count: %d\n", i, gs.whoseTurn, gs.deckCount[currentPlayer], gs.handCount[currentPlayer], gs.discardCount[currentPlayer]);
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

        //test[1] = my_assert(gs.handcurrentPlayer][gs.handCount[currentPlayer]-1], 4) || my_assert(gs.handcurrentPlayer][gs.handCount[currentPlayer]-1], 5) || my_assert(gs.handcurrentPlayer][gs.handCount[currentPlayer]-1], 6);

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