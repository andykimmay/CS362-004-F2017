#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

//function to get name of card
const char* getCardName(enum CARD card)
{
	switch(card)
	{
		case estate: return "estate";
		case copper: return "copper";
		case village: return "village";
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

//function to print out player's discard pile
int showDiscard(int player, struct gameState *state) {
	int i = 0;
	int playedCards = state->playedCardCount;
	printf("Player %d's discard pile:\n", player);
	for (i=0;i<playedCards;i++)
	{
		printf("%s\n", getCardName(state->playedCards[i]));
		if (state->playedCards[i] == village)
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

	// initialize a game state
	initializeGame(numPlayers, k, seed, &G);

	G.hand[0][5] = village;
	G.handCount[0] = G.handCount[0] +1;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: confirm that village adds a card --------------
	printf("TEST 1: Confirm village adds a card and discards itself\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//hand of player 0 before cardeffect
	showHand(0,&G);	
	showHand(0,&testG);

	printf("Call village card effect\n\n");

	//call cardeffect
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	//hand of player 0 after cardeffect
	showHand(0, &testG);
	
	if ((testG.handCount[0] - G.handCount[0]) == 0)	
	{
		printf("\nSuccess - card added!\n\n");
	}
	else
		printf("\nTest Failed - village card did not add a single card\n");

	if (showDiscard(0,&testG) == 0)
		printf("\nSuccess - village discarded\n");
	else
		printf("\nTest Failed - village not discarded\n");

	// ----------- TEST 2: Confirm village adds an additional action--------------
	printf("\nTEST 2: Confirm that village adds an additional action\n");
	int actionB, actionA;
	actionB = G.numActions;
	actionA = testG.numActions;

	printf("\nNumber of Actions before Village: %d\n",actionB);
	printf("\nNumber of Actions after Village: %d\n",actionA);

	if (actionA - actionB == 1)
		printf("Success!\n");
	else
		printf("Test Failed - village card did not add a single action\n");

	// ------------------------------------------------------------------------	
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}



