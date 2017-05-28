/*
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * cardtest3.c
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Counsel Room"
#define TRUE 1
#define FALSE 0
#define MAX_S 16

void assertEquals(int Test,  int prev, int post)
{
	if(prev == post)
		printf("\n**********************Test #%d: PASS\n\n", Test);
	else
		printf("\n**********************Test #%d: FAIL\n\n", Test);
}


/*
 * Card Rules:
 *1. Current player should receive exactly 4 cards.
 *2. 4 cards should come from player's own pile.
 *3. Current player should receive exactly 1 buy.
 *4. All other players draw a card
 *5. No state change should occur to the victory card piles and kingdom card piles.
 *
 */

int main(){
    int newCards = 0;
    int discarded = 1;
	int testNum = 1;
	int newBuys = 0;
    int shuffledCards = 0; 
	int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int OppCardDrawCnt = 0;
	struct gameState G, testG;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
			
	int supply[MAX_S] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room, estate, duchy, province, copper,
			silver, gold};

	char *str_sup[MAX_S] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse",
			"sea_hag", "tribute", "smithy", "council_room", "estate", "duchy", "province", "copper",
			"silver", "gold"};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("*******************************************\n");
    printf("---------- STARTING Test: %s ----------\n", TESTCARD);
	printf("*******************************************\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));	

	
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 4;
	newBuys = 1;
	OppCardDrawCnt = 1;
	
	printf("Test 1. Current player should receive exactly 4 cards.\n");
	/*1. Current player should receive exactly 4 cards.*/
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertEquals(testNum, testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	testNum++;
	
	printf("Test 2. Current player's cards should come from player's own pile.\n");
	/*2. s cards should come from player's own pile.*/
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	assertEquals(testNum,testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	testNum++;
	
	printf("Test 3. Current player should receive exactly 1 buy.\n");
	/*3. Current player should receive exactly 1 buy.*/
	printf("Player action count = %d, expected = %d\n", testG.numBuys, G.numBuys + newBuys);
	assertEquals(testNum,testG.numBuys, G.numBuys + newBuys);
	testNum++;
	
	printf("Test 4. All other players draw a card\n");
	/*4. All other players draw a card*/
	for(i = thisPlayer+1; i < numPlayers; i++){
		printf("hand count from other player = %d, expected = %d\n", testG.handCount[i], G.handCount[i] + OppCardDrawCnt);
		assertEquals(testNum,testG.handCount[i], G.handCount[i] + OppCardDrawCnt);
		printf("deck count from other player = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i] - OppCardDrawCnt + shuffledCards);
		assertEquals(testNum,testG.deckCount[i], G.deckCount[i] - OppCardDrawCnt + shuffledCards);
		printf("\n");
	}
	testNum++;
	
	printf("Test 5. No state change should occur to the victory card piles and kingdom card piles.\n");
	
	/*5. No state change should occur to the victory card piles and kingdom card piles.*/
	for(j=0;j<MAX_S; j++)
	{
		printf("supply count for %s = %d, expected %d\n", str_sup[j], testG.supplyCount[supply[j]],G.supplyCount[supply[j]]);
		assertEquals(testNum, testG.supplyCount[supply[j]], G.supplyCount[supply[j]]);
		printf("\n"); 
	}

    printf("*******************************************\n");
    printf("---------- COMPLETED Test: %s ---------\n", TESTCARD);
	printf("*******************************************\n");
	printf("\n"); 
	printf("\n"); 
    return 0;
}