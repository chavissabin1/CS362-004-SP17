/*
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest1.c
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "discardCard"
#define MAX_TESTS 3
#define TEST_1 0
#define TEST_2 1
#define TEST_3 2
#define TRUE 1
#define FALSE 0
/*
 * Function Rules:
 *1. Card is added to play pile if card is not trashed.
 *2. Card is not added to play pile if card is trashed.
 *3. Selected card is removed from hand.
 *
 */

 void assertEquals(int Test,  int prev, int post)
{
	if(prev == post)
		printf("\n**********************Test #%d: PASS\n\n", Test);
	else
		printf("\n**********************Test #%d: FAIL\n\n", Test);
}

 void assertNotEquals(int Test,  int prev, int post)
{
	if(prev != post)
		printf("\n**********************Test #%d: PASS\n\n", Test);
	else
		printf("\n**********************Test #%d: FAIL\n\n", Test);
}

int runTest(int testNum){
	int numPlayers = 2;
	int newCard = 1;
	int seed = 1000;
	int thisPlayer = 0;
	int discard = 1;
	int handPos = 0;
	int selectedCard = 0;
	int trashFlag = 1;
	int subTest = 0;
	struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};	
	
	initializeGame(numPlayers, k, seed, &G);
   
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		
	switch(testNum)
	{
		case TEST_1:
					
			printf("Test 1. Card is added to play pile if card is not trashed.\n\n");
			trashFlag = 0;
			subTest = 1;
			handPos = testG.handCount[thisPlayer]-1;			
			
			//select card to discard
			selectedCard = testG.hand[thisPlayer][handPos];
			
			
			discardCard(handPos, thisPlayer, &testG, trashFlag);
			
			printf("Test 1.1 Card is added to play pile.\n\n");
			printf("Top card from played pile = %d, expected = %d\n\n", testG.playedCards[testG.playedCardCount-1], selectedCard);
			assertEquals(subTest, testG.playedCards[testG.playedCardCount-1], selectedCard);
			subTest++;
			
			printf("Test 1.2 Play pile count incremented.\n\n");
			printf("Played card count = %d, expected = %d\n\n", testG.playedCardCount, G.playedCardCount + newCard);
			assertEquals(subTest, testG.playedCardCount, G.playedCardCount + newCard);
			
			return 0;
		case TEST_2:
					
			printf("Test 2. Card is not added to play pile if card is trashed.\n\n");
			trashFlag = 1;
			subTest = 1;
			handPos = testG.handCount[thisPlayer]-1;			
			
			//select card to discard
			selectedCard = testG.hand[thisPlayer][handPos];
			
			
			discardCard(handPos, thisPlayer, &testG, trashFlag);
			
			printf("Test 2.1 Card is added to play pile.\n\n");
			printf("Top card from played pile = %d, expected = %d\n\n", testG.playedCards[testG.playedCardCount-1], selectedCard);
			assertNotEquals(subTest, testG.playedCards[testG.playedCardCount-1], selectedCard);
			subTest++;
			
			printf("Test 2.2 Play pile count incremented.\n\n");
			printf("Played card count = %d, expected = %d\n\n", testG.playedCardCount, G.playedCardCount);
			assertEquals(subTest, testG.playedCardCount, G.playedCardCount);
			
			return 0;
		case TEST_3:
		
					
			printf("Test 3. Selected card is removed from hand.\n\n");
			trashFlag = 1;
			subTest = 1;
			handPos = testG.handCount[thisPlayer]-1;			
			
			//select last card to discard
			selectedCard = testG.hand[thisPlayer][handPos];
			
			discardCard(handPos, thisPlayer, &testG, trashFlag);
			
			printf("Test 3.1 Card is removed from top of hand.\n\n");
			printf("Top card from hand = %d, expected = %d\n\n", testG.hand[thisPlayer][handPos], -1);
			assertEquals(subTest, testG.hand[thisPlayer][handPos], -1);
			subTest++;
			
			printf("Test 3.2 hand count has decremented by one.\n\n");
			printf("Hand count = %d, expected = %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discard);
			assertEquals(subTest, testG.handCount[thisPlayer], G.handCount[thisPlayer] - discard);
			subTest++;
			
			printf("Test 3.3 Card is removed from hand with more than one card in hand and top card not selected.\n\n");
			
			handPos = testG.handCount[thisPlayer]-2;			
			
			//select last card to discard
			selectedCard = testG.hand[thisPlayer][handPos];
			
			discardCard(handPos, thisPlayer, &testG, trashFlag);
			
			discard++;
			printf("Top card from hand = %d, expected = %d\n\n", testG.hand[thisPlayer][handPos], G.hand[thisPlayer][handPos-1]);
			assertEquals(subTest, testG.hand[thisPlayer][handPos], G.hand[thisPlayer][handPos-1]);
			subTest++;
			
			printf("Test 3.4 hand count has decremented by one.\n\n");
			printf("Hand count = %d, expected = %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discard);
			assertEquals(subTest, testG.handCount[thisPlayer], G.handCount[thisPlayer] - discard);
			subTest++;
			
			
			printf("Test 3.5 Last card from hand is removed.\n\n");
			
			while (testG.handCount[thisPlayer] != 1)
			{
				discardCard(testG.handCount[thisPlayer]-1, thisPlayer, &testG, trashFlag);
				discard++;
			}
			
			printf("hand count is %d\n\n", testG.handCount[thisPlayer]);
			
			
			//select last card to discard
			selectedCard = testG.hand[thisPlayer][0];
			
			printf("selectedcard = %d\n\n", selectedCard);
			
			discardCard(0, thisPlayer, &testG, trashFlag);
			
			discard++;
			printf("Last card from hand = %d, expected = %d\n\n", testG.hand[thisPlayer][0], -1);
			assertEquals(subTest, testG.hand[thisPlayer][0], -1);
			subTest++;
			
			printf("Test 3.6 hand count is 0.\n\n");
			printf("Hand count = %d, expected = %d\n\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discard);
			assertEquals(subTest, testG.handCount[thisPlayer], G.handCount[thisPlayer] - discard);
			
			
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