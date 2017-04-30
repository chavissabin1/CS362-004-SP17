/*
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * unittest4.c
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"
#define MAX_TESTS 3
#define TEST_1 0
#define TEST_2 1
#define TEST_3 2
#define TRUE 1
#define FALSE 0

/*
 * Function Rules:
 *1. function returns 1 if stack of province cards is empty
 *2. function returns 1 if three or more supply piles are at zero
 *3. function returns 0 if less than three supply piles and province is not zero
 *3. Otherwise return 0
 *4.
 *
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
	int seed = 1000;
	struct gameState G, testG;
	int result;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &G);
   
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
		
	switch(testNum)
	{
		case TEST_1:
			//in order to proove that having no provinces in supply will end the game we must first empty the supply
			testG.supplyCount[province] = 0; 
			
			printf("Test 1.Check if game ends if Province supply is empty.\n\n");
			result = isGameOver(&testG);
			
			printf("Game end state is = %d, expected = %d\n\n", result, 1);
			assertEquals(TEST_1, result,1);
			
			return 0;
		case TEST_2:
			//in order to proove that having at least three cards empty in supply will end the game we must first empty the supply cards
			testG.supplyCount[smithy] = 0; 
			testG.supplyCount[adventurer] = 0; 
			testG.supplyCount[village] = 0; 
			
			printf("Test 2. Game over if three or more supply cards are empty.\n\n");
			result = isGameOver(&testG);
			
			
			printf("Game end state is = %d, expected = %d\n\n", result, 1);
			assertEquals(TEST_2, result,1);
			
			return 0;
		case TEST_3:
		
			//leave game state alone after initialization. 
			//All supply cards are not empty. Therefore game should not end.
			printf("Test 2. Game is not over if test 1 & 2 conditions are not met.\n\n");
			result = isGameOver(&testG);
			
			printf("Game end state is = %d, expected = %d\n\n", result, 0);
			assertEquals(TEST_3, result,0);
			
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