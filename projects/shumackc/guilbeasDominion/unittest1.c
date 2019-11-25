/************************************************************************************
** Author:	Cris Shumack
** Date:	11/09/2019
** Assignment:  Assignment 3 - Unit Tests
** Description: Unit tests for the Baron card function that was refactored in
**		assignment 2. Tests Baron card's main functions, as well as finds
**		bugs that were introduced in assignment2.
************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//Simple function that compares integers and prints PASSED if
//they are equal or FAILED if not.
void assertInt(int a, int b)
{
    	if (a == b)
		printf("PASSED\n");
	else 
		printf("FAILED\n");
}

int main()
{
	int k[10] = { adventurer, council_room, feast, gardens, mine
		      , remodel, smithy, village, baron, great_hall };

	int player1 = 0;
	int seed = 1024;
	int coins = 0;
	int i, r;
	int count1 = 0;
	int count2 = 0;

	//Gamestate 1 (G1) will test the baron card effect when the user choice is 1
	//and the user has an estate card in hand. G2 will test the baron card effect
	//when the user choice is 0 where they should gain an estate card. G3 will 
	//test baron card when the user choice is 1 but there is no estate in hand.
	struct gameState G1, G2, G3;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	memset(&G3, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2 and G3.
	r = initializeGame(2, k, seed, &G1);
	memcpy(&G2,&G1, sizeof(struct gameState));
	memcpy(&G3,&G1, sizeof(struct gameState));

	//Setting necessary variables for test cases.
	G1.coins = 0;
	G3.coins = 0;
	count1 = G1.handCount[player1];
	count2 = G2.handCount[player1];

	//Calls the gainCard function for G1 to ensure that the user
	//has an estate card in hand.	
	gainCard(estate, &G1, 2, player1);
	
	printf("\nBegin Testing baronCardEffect() on G1:\n");
	
	//Call to baronCardEffect() for G1.
	baronCardEffect(&G1, 1, 0);

	//This test will fail due to the bug I introduced, where the user only
	//gains 2 coins rather than the correct amount of 4.
	//***********BUG SHOULD BE CAUGHT HERE*****************
	printf("\nG1 Expected Coins: 4\n");
	printf("G1 Actual Coins: %d\n", G1.coins);
	printf("Coins Test: ");
	assertInt(G1.coins, 4);
	printf("\n");

	printf("G1 Expected Buys: 2\n");
	printf("G1 Actual Buys: %d\n", G1.numBuys);
	printf("Buys Test: ");
	assertInt(G1.numBuys, 2);

	printf("\nBegin Testing baronCardEffect() on G2:\n");

	//Call to baronCardEffect() for G2.
	baronCardEffect(&G2, 0, 0);

	//Based on the bug I introduced, this test should fail, since the user
	//would discard Baron and gain an Estate, but I commented out the call
	//to gainCard so they never gain an Estate card. The test here will pass
	//though, due to the Baron bug where discarding Baron never happens.
	printf("\nG2 Expected Hand Count: 5\n");
	printf("G2 Actual Hand Count: %d\n", count2);
	printf("Hand Count Test: ");
	assertInt(count2, 5); // check a condition
	printf("\n");

	//This test will fail because of the big I introduced. No call to gainCard
	//is ever made, so the user does not gain an Estate card.
	//q
	//***********BUG SHOULD BE CAUGHT HERE*****************
	if (G2.hand[player1][G1.handCount[player1]] == estate)
		printf("Estate Card Was Gained: PASSED\n");
	else
		printf("Estate Card Was Gained: FAILED\n");

	printf("\nBegin Testing baronCardEffect() on G3:\n");

	//Call to baronCardEffect() for G3.
	baronCardEffect(&G3, 1, 0);

	printf("\nG3 Expected Coins: 0\n");
	printf("G3 Actual Coins: %d\n", G3.coins);
	printf("Coins Test: ");
	assertInt(G3.coins, 0);
	printf("\n");

	printf("G3 Expected Buys: 2\n");
	printf("G3 Actual Buys: %d\n", G3.numBuys);
	printf("Buys Test: ");
	assertInt(G3.numBuys, 2);
	printf("\n");

	printf("Test completed!\n");

	return 0;
}
