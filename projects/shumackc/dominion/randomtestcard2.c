/************************************************************************************
** Author:	Cris Shumack
** Date:	11/17/2019
** Assignment:  Assignment 4 - Random Testers
** Description: Random tests for the Minion card function that was refactored in
**		assignment 2. Tests Minion card's main functions, as well as finds
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
int minionCardEffect(int choice1, int choice2, struct gameState *state, int handPos);

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
	int player2 = 1;
	int seed = 1024;
	int i;
	int count1 = 0;
	int count2 = 0;
	struct gameState G1;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));

	printf("*************************************************Random Test Card 2*************************************************\n");


	for (i = 0; i < 50; i++)
	{
		//Generates a random choice (0 or 1) to initialize the game with.
		int choice1 = rand() % 2;
		int choice2;
		
		if (choice1 == 1)
			choice2 = 0;
		else
			choice2 = 1;

		//50% chance for the player to gain an estate card. That way, 
		//sometimes the player has an estate to discard if they choose
		//to, and sometimes they do not.
		int player2GainCards = rand() % 2;

		initializeGame(2, k, seed, &G1);
	
		//Sets coins to 0 to make comparisons easier.
		G1.coins = 0;

		//Depending on the random number generated above, player 2 gains
		//cards so that the branch of code is covered.
		if (player2GainCards == 1)
		{
			gainCard(estate, &G1, 2, player2);
			gainCard(estate, &G1, 2, player2);
			gainCard(estate, &G1, 2, player2);
			gainCard(estate, &G1, 2, player2);
			gainCard(estate, &G1, 2, player2);
		}

		//Call to baronCardEffect() for G1.
		minionCardEffect(choice1, choice2, &G1, 0);

		count1 = G1.handCount[player1];
		count2 = G1.handCount[player2];

		printf("\n***********************Test %d/50***********************", i + 1);

		//Depending on choice generated above, a different set of assertions
		//are run. Assertions taken from my Baron unit test code (Assignment 3).	
		if (choice1 == 1)
		{
			printf("\nExpected Coins: 2\n");
			printf("Actual Coins: %d\n", G1.coins);
			printf("Coins Test: ");
			assertInt(G1.coins, 2);
			printf("\n");

			printf("Expected Buys: 1\n");
			printf("Actual Buys: %d\n", G1.numBuys);
			printf("Buys Test: ");
			assertInt(G1.numBuys, 1);
		}
		else if (choice2 == 1)
		{
			if (player2GainCards == 1)
			{
				printf("\nPlayer 1 Expected Hand Count: 4\n");
				printf("Player 1 Actual Hand Count: %d\n", count1);
				printf("Player 1 Hand Count Test: ");
				assertInt(count1, 4);
				printf("\n");

				printf("Player 2 Expected Hand Count: 4\n");
				printf("Player 2 Actual Hand Count: %d\n", count2);
				printf("Player 2 Hand Count Test: ");
				assertInt(count2, 4);
				printf("\n");
			}
			else if (player2GainCards == 0)
			{
				printf("\nPlayer 1 Expected Hand Count: 4\n");
				printf("Player 1 Actual Hand Count: %d\n", count1);
				printf("Player 1 Hand Count Test: ");
				assertInt(count1, 4);
				printf("\n");

				printf("Player 2 Expected Hand Count: 0\n");
				printf("Player 2 Actual Hand Count: %d\n", count2);
				printf("Player 2 Hand Count Test: ");
				assertInt(count2, 0);
				printf("\n");
			}
		}
	}
}
