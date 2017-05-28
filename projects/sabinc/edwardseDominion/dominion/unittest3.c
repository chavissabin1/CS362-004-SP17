/*
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest3.c
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "gainCard"
#define MAX_TESTS 5
#define TEST_1 0
#define TEST_2 1
#define TEST_3 2
#define TEST_4 3
#define TEST_5 4
#define TEST_6 5
#define TEST_7 6
#define TRUE 1
#define FALSE 0
/*
 *added card for [whoseTurn] current player:
 * toFlag = 0 : add to discard
 * toFlag = 1 : add to deck
 * toFlag = 2 : add to hand
 * Card Rules:
 *1.Check if card is not in game.
 *2. Add selected card to deck
 *3. Add selected card to hand
 *4. Add selected card to discard.
 *5. Test that selected card's supply is decreased by one
 */

void assertEquals(int Test,  int prev, int post)
{
	if(prev == post)
		printf("\n**********************Test #%d: PASS\n\n", Test);
	else
		printf("\n**********************Test #%d: FAIL\n\n", Test);
}


int runTest(int testNum){
	int numPlayers = 2;
	int subTest = 1;
	int newCard = 1;
	int seed = 1000;
	int thisPlayer = 0;
	int discard = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};	
	
	int baron = 15;//used as test card that does not exists in game.
	int result;
	initializeGame(numPlayers, k, seed, &G);
    
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	switch(testNum)
	{
		case TEST_1:
			
			printf("Test 1.Check if card is not in game.\n\n");
			result = gainCard(baron, &testG, 0, thisPlayer);
			
			printf("Card not in game result = %d, expected = %d\n\n", result, -1);
			assertEquals(subTest, result, -1);
			
			return 0;
		case TEST_2:
			printf("Test 2. Add selected card to deck\n\n");
			
			result = gainCard(k[0], &testG, 1, thisPlayer);
			printf("Test 2.1. check if card is added to deck\n\n");
			
			printf("card added to deck is = %d, expected = %d\n\n", testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1], k[0]);
			assertEquals(subTest, testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1], k[0]);
			subTest++;
			
			printf("Test 2.2. check if deck has incremented\n\n");
			
			printf("Deck count = %d, expected = %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]+newCard);
			assertEquals(subTest, testG.deckCount[thisPlayer], G.deckCount[thisPlayer]+newCard);
			
			return 0;
		case TEST_3:
			printf("Test 3. Add selected card to hand\n\n");
			
			result = gainCard(k[0], &testG, 2, thisPlayer);
			printf("Test 3.1. check if card is added to deck\n\n");
			
			
			printf("card added to hand is = %d, expected = %d\n\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], k[0]);
			assertEquals(subTest, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], k[0]);
			subTest++;
						
			printf("Test 3.2. check if hand has incremented\n\n");
			
			printf("Deck count = %d, expected = %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]+newCard);
			assertEquals(subTest, testG.handCount[thisPlayer], G.handCount[thisPlayer]+newCard);
					
			return 0;
		case TEST_4:
		
			printf("Test 4. Add selected card to discard.\n\n");
			
			result = gainCard(k[0], &testG, 0, thisPlayer);
			printf("Test 4.1. check if card is added to discard\n\n");
						
			printf("card added to discard is = %d, expected = %d\n\n", testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1], k[0]);
			assertEquals(subTest, testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1], k[0]);
			subTest++;
			
			
			printf("Test 4.2. check if discard pile has incremented\n\n");
			
			printf("Deck count = %d, expected = %d\n\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+newCard);
			assertEquals(subTest, testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+newCard);
			
			return 0;
		case TEST_5:
		
			printf("Test 5. Test that selected card's supply is decreased by one\n\n");
			
			result = gainCard(k[0], &testG, 1, thisPlayer);
			
			printf("Card supply is = %d, expected = %d\n\n",testG.supplyCount[k[0]], G.supplyCount[k[0]]-discard);
			assertEquals(subTest, testG.supplyCount[k[0]], G.supplyCount[k[0]]-discard);
			
			return 0;
		default:
			return -1;
	}
}

int main(){
	int i;
	
	printf("*******************************************\n");
    printf("---------- STARTING Test: %s ----------\n", TESTFUNCTION);
	printf("*******************************************\n");
    
	for(i=0;i<MAX_TESTS;i++)
	{
		runTest(i);
	}

    printf("*******************************************\n");
    printf("---------- COMPLETED Test: %s ---------\n", TESTFUNCTION);
	printf("*******************************************\n");
	printf("\n"); 
	printf("\n"); 
    return 0;
}