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

#define TESTFUNCTION "updateCoins"
#define MAX_TESTS 6
#define MAX_K 10
#define TEST_1 0
#define TEST_2 1
#define TEST_3 2
#define TEST_4 3
#define TEST_5 4
#define TEST_6 5
#define TRUE 1
#define FALSE 0

/*
 * Function Rules:
 *1. Hand with one copper and 0 bonus will result in 1 coin count.
 *2. Hand with one silver and 0 bonus will result in 2 coin count.
 *3. Hand with one gold and 0 bonus will result in 3 coin count.
 *4. Hand with zero coin cards and 1 bonus will result in 1 coin count.
 *5. Hand with more than one coin card and bonus will result in sum of all coins and bonus;
 *6. Hand with no coin cards and bonus will result with 0 coins.
 *
 */

void assertEquals(int Test,  int prev, int post)
{
	if(prev == post)
		printf("\n**********************Test #%d: PASS\n\n", Test);
	else
		printf("\n**********************Test #%d: FAIL\n\n", Test);
}


int main(){
	int i, j, l, m, n;
	int numPlayers = 2;
	int seed = 1000;
	int thisPlayer = 0;
	int newCoin = 0;
	int testNum = 1;
	int bonus = 0;
	struct gameState G, testG;
	int k[MAX_K] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};	
		
	initializeGame(numPlayers, k, seed, &G);
	
	//clear the coin state
	G.coins = 0;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("*******************************************\n");
    printf("---------- STARTING Test: %s ----------\n", TESTFUNCTION);
	printf("*******************************************\n");
  
	printf("Test 1. Hand with one copper and 0 bonus will result in 1 coin count.\n\n");
	
	newCoin = 1;
	bonus = 0;
	//modify hand to have one copper. 
	testG.hand[thisPlayer][0] = copper;
	//printf("Card %d in Hand contains %d, expected %d \n\n",0,testG.hand[thisPlayer][0],copper);
	
	//fill remaining hand with non coin cards
	for (i=1; i< testG.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = smithy;
	//printf("Card %d in Hand contains %d, expected %d \n\n",i,testG.hand[thisPlayer][i],smithy);
	}
	
	updateCoins(thisPlayer, &testG, bonus);
	
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + newCoin + bonus);
	assertEquals(testNum, testG.coins, G.coins + newCoin + bonus);;
	testNum++;
	
	
	printf("Test 2. Hand with one silver and 0 bonus will result in 2 coin count.\n\n");
	
	newCoin = 2;
	bonus = 0;
	//modify hand to have one copper. 
	testG.hand[thisPlayer][0] = silver;
	//printf("Card %d in Hand contains %d, expected %d \n\n",0,testG.hand[thisPlayer][0],silver);
	
	//fill remaining hand with non coin cards
	for (j=1; j< testG.handCount[thisPlayer]; j++)
	{
		testG.hand[thisPlayer][j] = smithy;
	//printf("Card %d in Hand contains %d, expected %d \n\n",i,testG.hand[thisPlayer][i],smithy);
	}
	
	updateCoins(thisPlayer, &testG, bonus);
	
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + newCoin + bonus);
	assertEquals(testNum, testG.coins, G.coins + newCoin + bonus);
	testNum++;
	
	printf("Test 3. Hand with one gold and 0 bonus will result in 3 coin count.\n\n");
	
	newCoin = 3;
	bonus = 0;
	//modify hand to have one copper. 
	testG.hand[thisPlayer][0] = gold;
	
	//fill remaining hand with non coin cards
	for (n=1; n< testG.handCount[thisPlayer]; n++)
	{
		testG.hand[thisPlayer][n] = smithy;
	}
	
	updateCoins(thisPlayer, &testG, bonus);
	
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + newCoin + bonus);
	assertEquals(testNum, testG.coins, G.coins + newCoin + bonus);
	testNum++;
	
	printf("Test 4. Hand with zero coin cards and 1 bonus will result in 1 coin count.\n\n");
	
	newCoin = 0;
	bonus = 1;
	
	//fill hand with non coin cards
	for (l=0; l< testG.handCount[thisPlayer]; l++)
	{
		testG.hand[thisPlayer][l] = smithy;
	}
	
	updateCoins(thisPlayer, &testG, bonus);
	
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + newCoin + bonus);
	assertEquals(testNum, testG.coins, G.coins + newCoin + bonus);
	testNum++;
	
	
	printf("Test 5. Hand with more than one coin card and bonus will result in sum of all coins and bonus;\n\n");
	
	newCoin = 10;//2 copper + 1 silver + 2 gold = 10
	bonus = 1;
	
	//fill hand with fixed coin cards
	testG.hand[thisPlayer][0] = copper;
	testG.hand[thisPlayer][1] = copper;
	testG.hand[thisPlayer][2] = silver;
	testG.hand[thisPlayer][3] = gold;
	testG.hand[thisPlayer][4] = gold;
	
	
	updateCoins(thisPlayer, &testG, bonus);
	
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + newCoin + bonus);
	assertEquals(testNum, testG.coins, G.coins + newCoin + bonus);
	testNum++;
	
	printf("Test 6. Hand with no coin cards and bonus will result with 0 coins.\n\n");
	
	newCoin = 0;
	bonus = 0;
	
	//fill hand with non coin cards
	for (m=0; m< testG.handCount[thisPlayer]; m++)
	{
		testG.hand[thisPlayer][m] = smithy;
	}
	
	updateCoins(thisPlayer, &testG, bonus);
	
	printf("coin count = %d, expected = %d\n", testG.coins, G.coins + newCoin + bonus);
	assertEquals(testNum, testG.coins, G.coins + newCoin + bonus);
	
    printf("*******************************************\n");
    printf("---------- COMPLETED Test: %s ---------\n", TESTFUNCTION);
	printf("*******************************************\n");
	printf("\n"); 
	printf("\n"); 
    return 0;
}
