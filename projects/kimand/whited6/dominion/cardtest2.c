#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

//function to get name of card
const char* getCardName(enum CARD card)
{
	switch(card)
	{
		case estate: return "estate";
		case copper: return "copper";
		case smithy: return "smithy";
	}
}		     

//function to print out the player's hand to confirm test
int showHand(int player, struct gameState *state) {
	int i, j;
	j = state->handCount[player];
	printf("Player %d's Hand:\n", player);
	for (i=0;i<j;i++)
	{
		printf("%s\n", getCardName(state->hand[player][i]));
	}
	printf("Number of cards in hand: %d\n\n",j);
	return j;
}

//function to print out player's deck prior to drawing cards
int showDiscard(int player, struct gameState *state) {
	int i = 0;
	int playedCards = state->playedCardCount;
	printf("Player %d's discard pile:\n", player);
	for (i=0;i<playedCards;i++)
	{
		printf("%s\n", getCardName(state->playedCards[i]));
		if (state->playedCards[i] == smithy)
			return 0;
	}
	return 1;
}

int main() {
	int handpos = 5, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards//
	initializeGame(numPlayers, k, seed, &G);
	
	//add smithy to the hand
	G.hand[0][5] = smithy;
	G.handCount[0] = G.handCount[0] +1;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: confirm that smithy adds 3 cards --------------
	printf("TEST 1: Confirm card adds 3 cards (and discards smithy)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//hand of player 0 before cardeffect
	showHand(0,&G);	
	showHand(0,&testG);

	printf("Call smithy card effect\n\n");

	//call cardeffect
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	//hand of player 0 after cardeffect
	showHand(0, &testG);
	
	if ((testG.handCount[0] - G.handCount[0]) == 2)	
	{
		printf("Success!\n");
	}
	else
		printf("Test Failed - did not add 3 cards\n");

	// ----------- TEST 2: Confirm discard of smithy card --------------
	printf("\nTEST 2: Confirm discard of smithy card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//print out the cards in the discard pile
	showDiscard(0,&G);
	showDiscard(0,&testG);

	printf("\nCall smithy card effect\n\n");

	//call cardeffect
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (showDiscard(0,&testG) == 1)
		printf("\nTest Failed\n");
	else
		printf("\nSuccess!\n");
	
	// ------------------------------------------------------------------------	
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}



