/***************************************************************************************
** Author:      Cris Shumack
** Date:        11/09/2019
** Assignment:  Assignment 3 - Unit Tests
** Description: Unit tests for the Tribute card function that was refactored in
**              assignment 2. Tests Tribute card's main functions, as well as finds
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
	int actions = 0;

	struct gameState G1, G2, G3, G4, G5;

	//memset each gamestate to get ready for initializing them.
	memset(&G1, 23, sizeof(struct gameState));
	memset(&G2, 23, sizeof(struct gameState));
	memset(&G3, 23, sizeof(struct gameState));
	memset(&G4, 23, sizeof(struct gameState));
	memset(&G5, 23, sizeof(struct gameState));

	//Inititalizes G1 and use memcpy to initialize G2 and G3.
	r = initializeGame(2, k, seed, &G1);
	memcpy(&G2,&G1, sizeof(struct gameState));
	memcpy(&G3,&G1, sizeof(struct gameState));
	memcpy(&G4,&G1, sizeof(struct gameState));
	memcpy(&G5,&G1, sizeof(struct gameState));

	//Setting different player2 hands for different gamestate
	//instances so that multiples discard scenarios are covered.
	
	//G1 will cover 2 victory cards being discarded (+4 cards).
	G1.coins = 0;
	G1.deck[player2][8] = estate;
	G1.deck[player2][9] = duchy;
	
	//G2 will cover 2 treasure cards being discarded (+4 coins).
	G2.coins = 0;
	G2.deck[player2][8] = silver;
	G2.deck[player2][9] = copper;

	//G3 will cover 2 action cards being discarded (+4 actions).
	G3.coins = 0;
	G3.deck[player2][8] = baron;
	G3.deck[player2][9] = smithy;

	//G4 will cover a case where player2 deckCount is 1 (deckCount should decrement to 0).
	G4.coins = 0;
	G4.deckCount[player2] = 1;
	G4.deck[player2][0] = copper;

	//G5 will cover a case where player2 deckCount is 0.
	G5.coins = 0;
	G5.deckCount[player2] = 0;

	//Testing for G1 begins here.
	printf("\nBegin Testing tributeCardEffect() on G1:\n");

	tributeCardEffect(&G1, 0);

	count1 = G1.handCount[player1];	
	count2 = G1.deckCount[player2];	
	actions = G1.numActions;

	printf("\nG1 Player1 Expected Hand Count: 8\n");
	printf("G1 Player1 Actual Hand Count: %d\n", count1);
	printf("Player1 Hand Count Test: ");
	assertInt(count1, 8);
	printf("\n");

	printf("G1 Player1 Expected Actions: 1\n");
	printf("G1 Player1 Actual Actions: %d\n", actions);
	printf("Player1 Actions Test: ");
	assertInt(actions, 1);
	printf("\n");

	printf("G1 Player1 Expected Coins: 0\n");
	printf("G1 Player1 Actual Coins: %d\n", G1.coins);
	printf("Player1 Coins Test: ");
	assertInt(G1.coins, 0);
	printf("\n");

	printf("G1 Player2 Expected Deck Count: 8\n");
	printf("G1 Player2 Actual Hand Count: %d\n", count2);
	printf("Player2 Hand Count Test: ");
	assertInt(count2, 8);
	printf("\n");

	//Testing for G2 begins here.
	printf("\nBegin Testing tributeCardEffect() on G2:\n");

	tributeCardEffect(&G2, 0);

	count1 = G2.handCount[player1];	
	count2 = G2.deckCount[player2];	
	actions = G2.numActions;

	printf("\nG2 Player1 Expected Hand Count: 4\n");
	printf("G2 Player1 Actual Hand Count: %d\n", count1);
	printf("Player1 Hand Count Test: ");
	assertInt(count1, 4);
	printf("\n");

	printf("G2 Player1 Expected Actions: 1\n");
	printf("G2 Player1 Actual Actions: %d\n", actions);
	printf("Player1 Actions Test: ");
	assertInt(actions, 1);
	printf("\n");

	//Due to the bug I implemented in assignment 2, this test will fail. Instead
	//of correct adding 2 coins per treasure card discarded (total of 4 coins),
	//the bug I implemented does not add any.
	//**************************BUG WILL BE FOUND HERE***************************
	printf("G2 Player1 Expected Coins: 4\n");
	printf("G2 Player1 Actual Coins: %d\n", G2.coins);
	printf("Player1 Coins Test: ");
	assertInt(G2.coins, 4);
	printf("\n");

	printf("G2 Player2 Expected Deck Count: 8\n");
	printf("G2 Player2 Actual Hand Count: %d\n", count2);
	printf("Player2 Hand Count Test: ");
	assertInt(count2, 8);
	printf("\n");

	//Testing for G3 begins here.
	printf("\nBegin Testing tributeCardEffect() on G3:\n");

	tributeCardEffect(&G3, 0);

	count1 = G3.handCount[player1];	
	count2 = G3.deckCount[player2];	
	actions = G3.numActions;

	printf("\nG3 Player1 Expected Hand Count: 4\n");
	printf("G3 Player1 Actual Hand Count: %d\n", count1);
	printf("Player1 Hand Count Test: ");
	assertInt(count1, 4);
	printf("\n");

	printf("G3 Player1 Expected Actions: 5\n");
	printf("G3 Player1 Actual Actions: %d\n", actions);
	printf("Player1 Actions Test: ");
	assertInt(actions, 5);
	printf("\n");

	printf("G3 Player1 Expected Coins: 0\n");
	printf("G3 Player1 Actual Coins: %d\n", G3.coins);
	printf("Player1 Coins Test: ");
	assertInt(G3.coins, 0);
	printf("\n");

	printf("G3 Player2 Expected Deck Count: 8\n");
	printf("G3 Player2 Actual Hand Count: %d\n", count2);
	printf("Player2 Hand Count Test: ");
	assertInt(count2, 8);
	printf("\n");

	//Testing for G4 begins here.
	printf("\nBegin Testing tributeCardEffect() on G4:\n");

	tributeCardEffect(&G4, 0);

	count2 = G4.deckCount[player2];	

	//Due to the bug I introduced in assignment 2, this test will fail. I increment
	//the deck count rather than correctly decrementing it, so the deck count will
	//be 2 rather than 0.
	//*************************BUG WILL BE CAUGHT HERE***************************
	printf("\nG4 Player2 Expected Deck Count: 0\n");
	printf("G4 Player2 Actual Hand Count: %d\n", count2);
	printf("Player2 Deck Count Test: ");
	assertInt(count2, 0);
	printf("\n");

	//Testing for G5 begins here.
	printf("\nBegin Testing tributeCardEffect() on G5:\n");

	tributeCardEffect(&G5, 0);

	count1 = G5.handCount[player1];	
	count2 = G5.deckCount[player2];	

	printf("\nG5 Player1 Expected Hand Count: 4\n");
	printf("G5 Player1 Actual Hand Count: %d\n", count1);
	printf("Player1 Hand Count Test: ");
	assertInt(count1, 4);
	printf("\n");

	printf("G5 Player2 Expected Deck Count: 0\n");
	printf("G5 Player2 Actual Deck Count: %d\n", count2);
	printf("Player2 Hand Count Test: ");
	assertInt(count2, 0);
	printf("\n");
	printf("Test completed!\n");

	return 0;
}
