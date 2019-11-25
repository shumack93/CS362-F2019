/***************************************************************************************
** Author:      Cris Shumack
** Date:        11/09/2019
** Assignment:  Assignment 3 - Unit Tests
** Description: Unit tests for the Ambassador card function that was refactored in
**              assignment 2. Tests Ambassador card's main functions, as well as finds
**              bugs that were introduced in assignment2.
***************************************************************************************/

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
	gainCard(estate, &G3, 2, player2);
	gainCard(estate, &G3, 2, player2);
	gainCard(estate, &G3, 2, player2);
	gainCard(estate, &G3, 2, player2);
	gainCard(estate, &G3, 2, player2);
	count1 = G3.handCount[player1];
	count2 = G3.handCount[player2];

	//Calls the gainCard function for G1 to ensure that the user
	//has an estate card in hand.	
//	gainCard(estate, &G1, 2, player1);
	
	printf("\nBegin Testing ambassadorCardEffect() on G1:\n");
	
	//Testing a case where choice2 is greater than 2, which should
	//immediately return a value of -1.	
	printf("\nReturn Error (-1) Test: ");
	assertInt(-1, ambassadorCardEffect(&G1, 1, 3, 0, 0));

	printf("\nBegin Testing ambassadorCardEffect() on G2:\n");
	
	//One of the bugs I introduced in assignment2 caused the program to always
	//return -1 at the if (j < choice2) statement by replacing j++ with j--. To
	//gain coverage, I corrected the bug. However, it would be caught here.
	//*********BUG WOULD BE CAUGHT HERE IF NOT CORRECTED FOR COVERAGE********
	printf("\nReturn Error (-1) Test: ");
	assertInt(-1, ambassadorCardEffect(&G2, 0, 1, 0, 0));

	printf("\nBegin Testing ambassadorCardEffect() on G3:\n");

	printf("\nReturn Success (0) Test: ");
	assertInt(0, ambassadorCardEffect(&G3, 1, 1, 0, 0));

	count1 = G3.handCount[player1];
	count2 = G3.handCount[player2];

	//You would expect two cards to be discarded from Player1's hand: the
	//Ambassador card and the card effect card. However, the bug I introducted
	//in assignment 2 causes the Ambassador card to stay in hand.
	//******************BUG SHOULD BE CAUGHT HERE************************
	printf("G3 Player1 Expected Hand Count: 3\n");
	printf("G3 Player1 Actual Hand Count: %d\n", count1);
	assertInt(count1, 3);
	printf("\n");

	printf("G3 Player2 Expected Hand Count: 6\n");
	printf("G3 Player2 Actual Hand Count: %d\n", count2);
	assertInt(count2, 6);
	printf("\n");
	
	printf("Test completed!\n");

	return 0;
}
