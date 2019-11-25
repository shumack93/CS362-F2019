/************************************************************************************
** Author:	Cris Shumack
** Date:	11/17/2019
** Assignment:  Assignment 4 - Random Testers
** Description: Random tests for the Baron card function that was refactored in
**		assignment 2. Tests Baron card's main functions, as well as finds
**		bugs that were introduced in assignment 2.
************************************************************************************/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//To avoid the "implicit declaration" warning.
int baronCardEffect(struct gameState *state, int choice1, int currentPlayer);

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
	srand(time(NULL));

	int k[10] = { adventurer, council_room, feast, gardens, mine
		      , remodel, smithy, village, baron, great_hall };

	int player1 = 0;
	int seed = 1024;
	int i;
	int count = 0;
	struct gameState G1;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));

	printf("*************************************************Random Test Card 1*************************************************\n");

	for (i = 0; i < 50; i++)
	{
		//Generates a random choice (0 or 1) to initialize the game with.
		int choice = rand() % 2;

		//50% chance for the player to gain an estate card. That way, 
		//sometimes the player has an estate to discard if they choose
		//to, and sometimes they do not.
		int gainEstate = rand() % 2;

		initializeGame(4, k, seed, &G1);
	
		//Sets coins to 0 to make comparisons easier.
		G1.coins = 0;

		player1 = whoseTurn(&G1);

		//Depending on the random number generated above, player gains
		//an estate card.
		if (gainEstate == 1)
			gainCard(estate, &G1, 2, player1);

		//Call to baronCardEffect() for G1.
		baronCardEffect(&G1, choice, 0);

		count = G1.handCount[player1];

		printf("\n***********************Test %d/50***********************", i + 1);

		//Depending on choice generated above, a different set of assertions
		//are run. Assertions taken from my Baron unit test code (Assignment 3).	
		if (choice == 0)
		{
			printf("\nExpected Hand Count: 5\n");
			printf("Actual Hand Count: %d\n", count);
			printf("Hand Count Test: ");
			assertInt(count, 5);
			printf("\n");
			
			if (G1.hand[player1][G1.handCount[player1]] == estate)
				printf("Estate Card Was Gained: PASSED\n");
			else
				printf("Estate Card Was Gained: FAILED\n");
		}
		else if (choice == 1)
		{
			if (gainEstate == 1)
			{
				printf("\nExpected Coins: 4\n");
				printf("Actual Coins: %d\n", G1.coins);
				printf("Coins Test: ");
				assertInt(G1.coins, 4);
				printf("\n");

				printf("Expected Buys: 2\n");
				printf("Actual Buys: %d\n", G1.numBuys);
				printf("Buys Test: ");
				assertInt(G1.numBuys, 2);
			}
			else if (gainEstate == 0)
			{
				printf("\nExpected Coins: 0\n");
				printf("Actual Coins: %d\n", G1.coins);
				printf("Coins Test: ");
				assertInt(G1.coins, 0);
				printf("\n");

				printf("Expected Buys: 2\n");
				printf("Actual Buys: %d\n", G1.numBuys);
				printf("Buys Test: ");
				assertInt(G1.numBuys, 2);
			}
		}
	}
}
