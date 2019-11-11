/************************************************************************************
** Author:	Cris Shumack
** Date:	11/09/2019
** Assignment:  Assignment 3 - Unit Tests
** Description: Unit tests for the Mine card function that was refactored in
**		assignment 2. Tests Mine card's main functions, as well as finds
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

	//Gamestate 1 (G1) will test the baron card effect when the user choice is 1
	//and the user has an estate card in hand. G2 will test the baron card effect
	//when the user choice is 0 where they should gain an estate card. G3 will 
	//test baron card when the user choice is 1 but there is no estate in hand.
	struct gameState G1, G2;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2 and G3.
	r = initializeGame(2, k, seed, &G1);
	memcpy(&G2,&G1, sizeof(struct gameState));

	//Calls the gainCard function for each gamestate to ensure
	//they each have a treasure card in hand.
	gainCard(copper, &G1, 2, player1);

	printf("\n************************UNIT TEST 5*****************************\n");

	printf("\nBegin Testing mineCardEffect() on G1:\n");
	
	//Call to mineCardEffect() for G1.
	mineCardEffect(copper, silver, &G1, 0);

	count1 = G1.handCount[player1];

	//In assignment 2, the bug I tried to introduce was commenting out
	//a call to discardCard. Unfortuantely, that discardCard call was a
	//bug itself, so I just un-commented it and let that be my bug. Due to
	//this, two cards are discarded rather than just 1, making the handCount
	//1 lower than it should be.
	//**********************BUG WILL BE FOUND HERE************************
	printf("\nG1 Expected Hand Count: 6\n");
	printf("G1 Actual Hand Count: %d\n", count1);
	printf("Hand Count Test: ");
	assertInt(count1, 6);
	printf("\n");

	if (G1.hand[player1][0] == silver)
		printf("Silver Card Was Gained: PASSED\n");
	else
		printf("Silver Card Was Gained: FAILED\n");
	
	printf("\nReturn Success (0) Test: ");
		assertInt(0, mineCardEffect(copper, silver, &G1, 0));

	printf("\n\nBegin Testing baronCardEffect() on G2:\n");

	printf("\nReturn Error (-1) Test: ");
		assertInt(-1, mineCardEffect(-1, silver, &G2, 0));

	//This test will fail and return 0 due to the bug I implemented in
	//assignment 2. I commented out the if statement that checks to make
	//sure choice2 is a valid treasure card.
	//*********************BUG WILL BE FOUND HERE************************
	printf("\nReturn Error (-1) Test: ");
		assertInt(-1, mineCardEffect(copper, minion, &G2, 0));

	printf("\nTest completed!\n");

	return 0;
}
