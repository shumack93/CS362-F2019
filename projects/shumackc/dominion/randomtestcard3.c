/************************************************************************************
** Author:	Cris Shumack
** Date:	11/17/2019
** Assignment:  Assignment 4 - Random Testers
** Description: Random tests for the Tribute card function that was refactored in
**		assignment 2. Tests Tribute card's main functions, as well as finds
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
int tributeCardEffect(struct gameState *state, int handPos);

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
	int actions = 0;
	struct gameState G1;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));

	printf("*************************************************Random Test Card 3*************************************************\n");

	for (i = 0; i < 50; i++)
	{
		int branch = rand() % 5;

		initializeGame(2, k, seed, &G1);

		//Depending on the random number generated above, the program sets
		//player 2's deck to contain different values so that different
		//scenarios happen within the tribute function.
		if (branch == 0)
		{
			G1.coins = 0;
			G1.deck[player2][8] = estate;
			G1.deck[player2][9] = duchy;
		}
		else if (branch == 1)
		{
			G1.coins = 0;
			G1.deck[player2][8] = silver;
			G1.deck[player2][9] = copper;
		}
		else if (branch == 2)
		{
			G1.coins = 0;
			G1.deck[player2][8] = baron;
			G1.deck[player2][9] = smithy;
		}
		else if (branch == 3)
		{
			G1.coins = 0;
			G1.deckCount[player2] = 1;
			G1.deck[player2][0] = silver;
		}
		else
		{
			G1.coins = 0;
			G1.deckCount[player2] = 0;
		}
	
		//Call to baronCardEffect() for G1.
		tributeCardEffect(&G1, 0);

		count1 = G1.handCount[player1];
		count2 = G1.handCount[player2];
		actions = G1.numActions;

		printf("\n***********************Test %d/50***********************", i + 1);

		//Depending on choice generated above, a different set of assertions
		//are run. Assertions taken from my Baron unit test code (Assignment 3).	
		if (branch == 0)
		{
			printf("\nPlayer1 Expected Hand Count: 8\n");
			printf("Player1 Actual Hand Count: %d\n", count1);
			printf("Player1 Hand Count Test: ");
			assertInt(count1, 8);
			printf("\n");

			printf("Player1 Expected Actions: 1\n");
			printf("Player1 Actual Actions: %d\n", actions);
			printf("Player1 Actions Test: ");
			assertInt(actions, 1);
			printf("\n");

			printf("Player1 Expected Coins: 0\n");
			printf("Player1 Actual Coins: %d\n", G1.coins);
			printf("Player1 Coins Test: ");
			assertInt(G1.coins, 0);
			printf("\n");
	
			printf("Player2 Expected Deck Count: 8\n");
			printf("Player2 Actual Hand Count: %d\n", count2);
			printf("Player2 Hand Count Test: ");
			assertInt(count2, 8);
			printf("\n");
		}
		else if (branch == 1)
		{
			printf("\nPlayer1 Expected Hand Count: 4\n");
			printf("Player1 Actual Hand Count: %d\n", count1);
			printf("Player1 Hand Count Test: ");
			assertInt(count1, 4);
			printf("\n");

			printf("Player1 Expected Actions: 1\n");
			printf("Player1 Actual Actions: %d\n", actions);
			printf("Player1 Actions Test: ");
			assertInt(actions, 1);
			printf("\n");

			printf("Player1 Expected Coins: 4\n");
			printf("Player1 Actual Coins: %d\n", G1.coins);
			printf("Player1 Coins Test: ");
			assertInt(G1.coins, 4);
			printf("\n");

			printf("Player2 Expected Deck Count: 8\n");
			printf("Player2 Actual Hand Count: %d\n", count2);
			printf("Player2 Hand Count Test: ");
			assertInt(count2, 8);
			printf("\n");
		}
		else if (branch == 2)
		{
			printf("\nPlayer1 Expected Hand Count: 4\n");
			printf("Player1 Actual Hand Count: %d\n", count1);
			printf("Player1 Hand Count Test: ");
			assertInt(count1, 4);
			printf("\n");

			printf("Player1 Expected Actions: 5\n");
			printf("Player1 Actual Actions: %d\n", actions);
			printf("Player1 Actions Test: ");
			assertInt(actions, 5);
			printf("\n");

			printf("Player1 Expected Coins: 0\n");
			printf("Player1 Actual Coins: %d\n", G1.coins);
			printf("Player1 Coins Test: ");
			assertInt(G1.coins, 0);
			printf("\n");

			printf("Player2 Expected Deck Count: 8\n");
			printf("Player2 Actual Hand Count: %d\n", count2);
			printf("Player2 Hand Count Test: ");
			assertInt(count2, 8);
			printf("\n");
		}
		else if (branch == 3)
		{
			printf("\nG4 Player2 Expected Deck Count: 0\n");
			printf("G4 Player2 Actual Hand Count: %d\n", count2);
			printf("Player2 Deck Count Test: ");
			assertInt(count2, 0);
			printf("\n");
		}
		else
		{
			printf("\nPlayer1 Expected Hand Count: 4\n");
			printf("Player1 Actual Hand Count: %d\n", count1);
			printf("Player1 Hand Count Test: ");
			assertInt(count1, 4);
			printf("\n");

			printf("Player2 Expected Deck Count: 0\n");
			printf("Player2 Actual Deck Count: %d\n", count2);
			printf("Player2 Hand Count Test: ");
			assertInt(count2, 0);
			printf("\n");
		}
	}
}
