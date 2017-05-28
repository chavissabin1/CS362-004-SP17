/*
 * sabinc
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * cardtest4.c
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"
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

void assertGreaterThan(int Test,  int left, int right)
{
	if(left > right)
		printf("\n**********************Test #%d: PASS\n\n", Test);
	else
		printf("\n**********************Test #%d: FAIL\n\n", Test);
}

/*
 * Card Rules:
 *1. Current player should receive exactly 2 cards.
 *2. Discard pile should have 2 less cards than before.
 *3. New hand's score should outscore the previous hand by at least 2 teasures 
 *	(indicating that the 2 new cards are at least coppers and above)
 * other player's score does not change //done
 * . Player's hand has two more tresures than before //done
 *5. No state change from other players //done
 *5. No state change should occur to the victory card piles and kingdom card piles.//TODO look over function
 *
 */

int main(){
    int newCards = 0;
    int discarded = 1;
	int testNum = 1;
    int shuffledCards = 0; 
	int i, j, m, n;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int minAdventererScore = 2;
	int prevScore[numPlayers], postScore[numPlayers];
	
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
	
	//gather scores from all players
	for(m = thisPlayer; m <  numPlayers; m++){
		postScore[m] = scoreFor(m,&testG);
		
	}
		
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//gather scores from all players
	for(n = thisPlayer; n <  numPlayers; n++){
		postScore[n] = scoreFor(n,&testG);
	}
	
	newCards = 2;
	
	printf("Test 1. Current player should receive exactly 2 cards.\n");
	/*1. Current player should receive exactly 2 cards.*/
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertEquals(testNum, testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	testNum++;
	
	printf("Test 2. Discard pile should have 2 less cards than before.\n");
	/*2. 2. Discard pile should have 2 less cards than before.*/
	printf("deck count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] - newCards + discarded);
	assertEquals(testNum, testG.discardCount[thisPlayer], G.discardCount[thisPlayer] - newCards + discarded);
	testNum++;

	printf("Test 3. New hand's score should outscore the previous hand by at least 2 teasures (indicating that the 2 new cards are at least coppers and above)\n\n");
	/*3.New hand's score should outscore the previous hand by at least 2 teasures (indicating that the 2 new cards are at least coppers and above) */
	printf("Score of %d should score at least 2 higher than %d\n\n",postScore[thisPlayer],prevScore[thisPlayer]);
	assertGreaterThan(testNum, postScore[thisPlayer], prevScore[thisPlayer]+minAdventererScore-1);	
	testNum++;
	
	printf("4. All other players states do not change\n");
	/*4. All other players states do not change*/
	for(i = thisPlayer+1;i < numPlayers; i++){
		printf("hand count from other player = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
		printf("deck count from other player = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
		assertEquals(testNum, testG.handCount[i], G.handCount[i]);
		assertEquals(testNum, testG.deckCount[i], G.deckCount[i]);
		printf("Score of %d should be >= %d",postScore[i],prevScore[i]);
		assertEquals(testNum, postScore[i], prevScore[i]);
		printf("\n");
	}
	testNum++;
	
	printf("5. No state change should occur to the victory card piles and kingdom card piles.\n");
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