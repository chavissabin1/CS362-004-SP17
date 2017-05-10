/* ***************************************************************************
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 4
 * randomcardtest2.c
 *****************************************************************************/
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Village"
#define TRUE 1
#define FALSE 0
#define MAX_S 16
#define TEST_MAX 2000
#define MAX_PLAYERS 4

 /* ***************************************************************************
 * Card Rules:
 *1. Current player should receive exactly 1 card.
 *2. 1 card should come from player's own pile.
 *3. Current player should receive exactly 2 actions.
 *4. No state change should occur for other players.
 *5. No state change should occur to the victory card piles and kingdom card piles.
 *
 *****************************************************************************/
 
/* **************************************************************************
 * Function: main
 * Description: main function runs random teser
 * Arguments:
 * Returns:
 * History: Date ---- Name ---- Change ----------------------------------
 * *******: 5/7/17		CS		Created
 ****************************************************************************/
int main()
{
	int i;
	
	printf("*******************************************\n");
    printf("---------- STARTING Random Tests: %s ----------\n", TESTCARD);
	printf("*******************************************\n");
  
	for(i = 0; i < TEST_MAX; i++)
	{
		randomTestVillage(i);
	}
   
	printf("*******************************************\n");
	printf("---------- COMPLETED Test: %s ---------\n", TESTCARD);
	printf("*******************************************\n");
	printf("\n"); 
	printf("\n"); 
	return 0;
}

/* **************************************************************************
 * Function: randomTestVillage
 * Description: setups struct randomly and calls cardEffect to play Village
 * Arguments: int test: test number
 * Returns: 
 * History: Date ---- Name ---- Change ----------------------------------
 * *******: 5/7/17		CS		Created
 ****************************************************************************/
void randomTestVillage(int test)
{
	int newCards = 1;
	int newActions = 2;
    int discard = 1;
    int shuffledCards = 0; 
	int i, j;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
	int errorFlag = 0;
	int player, handPos;
	struct gameState G, testG;
      
	//set up random number generator
	SelectStream(1);
	PutSeed((long)seed);
			
	int supply[MAX_S] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room, estate, duchy, province, copper,
			silver, gold};

	char *str_sup[MAX_S] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse",
			"sea_hag", "tribute", "smithy", "council_room", "estate", "duchy", "province", "copper",
			 "silver", "gold"};
			  
	player = floor(rand() % MAX_PLAYERS+1);
	G.deckCount[player] = floor(rand() % MAX_DECK+1);
	G.discardCount[player] = floor(rand() % MAX_DECK+1);
	G.handCount[player] = floor(rand() % MAX_HAND+1);
	handPos = floor(rand() % G.handCount[player]+1);
	G.numBuys = 1;
	G.numActions = 1;
	G.playedCardCount = 0;
	G.playedCards[G.playedCardCount] = 0;
	G.whoseTurn = player;
			
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));	
	
	cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);
	
	/*Test 1. Current player should receive exactly 1 card*/
	if(assertEquals(testG.handCount[player],G.handCount[player] + newCards - discard) == FALSE)
	{
		printf("ERROR: hand count = %d, expected = %d\n", testG.handCount[player], G.handCount[player] + newCards - discard);	
		errorFlag++;
	}
	
	/*Test 2. 1 card should come from player's pile*/
	if(assertEquals(testG.deckCount[player],G.deckCount[player] - newCards + shuffledCards) == FALSE)
	{
		printf("ERROR: deck count = %d, expected = %d\n", testG.deckCount[player], G.deckCount[player] - newCards + shuffledCards);
		errorFlag++;
	}
	
	/*Test 3. Current player should receive exactly 2 actions.*/
	if(assertEquals(testG.numActions, G.numActions + newActions) == FALSE)
	{
		printf("ERROR: Action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
		errorFlag++;
	}
	
	/*Test 4. No state change should occur for other players*/
	for(i = 0;i < MAX_PLAYERS; i++){
		if(assertEquals(testG.handCount[i], G.handCount[i]) == FALSE)
		{
			printf("ERROR: hand count from player %d = %d, expected = %d\n", i+1, testG.handCount[i], G.handCount[i]);
			errorFlag++;
		}
		
		if(assertEquals(testG.deckCount[i], G.deckCount[i]) == FALSE)
		{
			printf("ERROR: deck count from player %d = %d, expected = %d\n", i+1, testG.deckCount[i], G.deckCount[i]);
			errorFlag++;
		}
	}
	
	/*Test 5. No state change should occur to the victory card piles and kingdom card piles.*/
	for(j=0;j<MAX_S; j++)
	{
		if(assertEquals(testG.supplyCount[supply[j]], G.supplyCount[supply[j]]) == FALSE)
		{
			printf("ERROR: supply count for %s = %d, expected %d\n", str_sup[j], testG.supplyCount[supply[j]],G.supplyCount[supply[j]]);
			errorFlag++;
		}
	}
	
	//print test pass if errorFlag is 0
	if (errorFlag == 0)
	{
		printf("Test: %d PASS\n\n", test);
	}
	else if (errorFlag == 1)
	{
		printf("Test %d: %d error found\n\n",test, errorFlag);
	}
	else
	{
		printf("Test %d: %d errors found\n\n",test, errorFlag);
	}
}

/* **************************************************************************
 * Function: assertEquals
 * Description: compares two integers
 * Arguments: int left: number from test
 *		      int right: number from what is expected
 * Returns: True if left equals right
 *			False otherwise
 * History: Date ---- Name ---- Change ----------------------------------
 * *******: 5/3/17		CS		Created
 ****************************************************************************/
int assertEquals(int left, int right)
{
	if(left == right)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}