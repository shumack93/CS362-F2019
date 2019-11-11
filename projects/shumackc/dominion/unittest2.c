/************************************************************************************
** Author:      Cris Shumack
** Date:        11/09/2019
** Assignment:  Assignment 3 - Unit Tests
** Description: Unit tests for the Minion card function that was refactored in
**              assignment 2. Tests Minion card's main functions, as well as finds
**              bugs that were introduced in assignment2.
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
	int player2 = 1;
	int seed = 1024;
	int coins = 0;
	int i, r;
	int count = 0;
	int count2 = 0;

	//Gamestate 1 (G1) will test the baron card effect when the user choice is 1
	//and the user has an estate card in hand. G2 will test the baron card effect
	//when the user choice is 0 where they should gain an estate card. G3 will 
	//test baron card when the user choice is 1 but there is no estate in hand.
	struct gameState G1, G2;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2 and G3.
	r = initializeGame(4, k, seed, &G1);
	memcpy(&G2,&G1, sizeof(struct gameState));

	//Setting necessary variables for test cases.
	G1.coins = 0;

	//Gives player 2 five cards to make sure that scenario of
	//the Minion function is covered (where other players discard
	//their hand and draw four cards if they have 5 or more in hand).
	gainCard(estate, &G2, 2, player2);
	gainCard(estate, &G2, 2, player2);
	gainCard(estate, &G2, 2, player2);
	gainCard(estate, &G2, 2, player2);
	gainCard(estate, &G2, 2, player2);

	printf("\n************************UNIT TEST 2*****************************\n");	

	printf("\nBegin Testing minionCardEffect() on G1:\n");
	
	//Call to baronCardEffect() for G1.
	minionCardEffect(1, 0, &G1, 0);

	//This test will fail due to the bug I introduced, where the user
	//gains 4 coins rather than the correct amount of 2.
	//***********BUG SHOULD BE CAUGHT HERE*****************
	printf("\nG1 Expected Coins: 2\n");
	printf("G1 Actual Coins: %d\n", G1.coins);
	printf("Coins Test: ");
	assertInt(G1.coins, 2);
	printf("\n");

	printf("G1 Expected Buys: 1\n");
	printf("G1 Actual Buys: %d\n", G1.numBuys);
	printf("Buys Test: ");
	assertInt(G1.numBuys, 1);

	printf("\nBegin Testing minionCardEffect() on G2:\n");

	//Call to minionCardEffect() for G2.
	minionCardEffect(0, 1, &G2, numHandCards(&G2));

	//Gets the handCount of the player AFTER they decided to discard their
	//hand and draw 4 new ones.
	count = G2.handCount[player1];
	count2 = G2.handCount[player2];

	//Based on the bug I introduced, this test should fail, since the user
	//only draws 2 new cards rather than the 4 they're supposed to get.
	//*************BUG SHOULD BE CAUGHT HERE*****************
	printf("\nPlayer 1 Expected Hand Count: 4\n");
	printf("Player 1 Actual Hand Count: %d\n", count);
	printf("Player 1 Hand Count Test: ");
	assertInt(count, 4);
	printf("\n");

	printf("Player 2 Expected Hand Count: 4\n");
	printf("Player 2 Actual Hand Count: %d\n", count2);
	printf("Player 2 Hand Count Test: ");
	assertInt(count2, 4);
	printf("\n");
	
	printf("Test completed!\n");

	return 0;
}
