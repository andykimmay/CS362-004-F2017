#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

//function to get name of card
const char* getCardName(enum CARD card)
{
	switch(card)
	{
		case estate: return "estate";
		case copper: return "copper";
		case adventurer: return "adventurer";
	}
}		     

//function to print out the player's hand to confirm test
int showHand(int player, struct gameState *state, int *tc) {
	int i, j;
	*tc=0;
	j = state->handCount[player];
	printf("Player %d's Hand:\n", player);
	for (i=0;i<j;i++)
	{
		printf("%s\n", getCardName(state->hand[player][i]));
		if(state->hand[player][i] == copper)
			(*tc)++;
	}
	printf("Number of treasure cards: %d\n\n",*tc);
	return *tc;
}

//function to print out player's deck prior to drawing cards
int showDiscard(int player, struct gameState *state) {
	int i = 0;
	int playedCards = state->playedCardCount;
	printf("Player %d's discard pile:\n", player);
	for (i=0;i<playedCards;i++)
	{
		printf("%s\n", getCardName(state->playedCards[i]));
		if (state->playedCards[i] == copper)
			return 1;
		else if (state->playedCards[i] == adventurer)
			return 2;
	}
	return 0;
}

int main() {
	int handpos = 5, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    	int treasure1 = 0, treasure2 = 0;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state
	initializeGame(numPlayers, k, seed, &G);

	//add adventurer card to game state
	G.hand[0][5] = adventurer;
	G.handCount[0] = G.handCount[0] + 1;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: confirm that adventurer adds 3 treasure cards --------------
	printf("TEST 1: Confirm card adds 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//hand of player 0 before cardeffect
	showHand(0,&G, &treasure1);	
	showHand(0,&testG, &treasure2);

	printf("Call adventurer card effect\n\n");

	//call cardeffect
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//hand of player 0 after cardeffect
	showHand(0, &testG, &treasure2);
	
	if ((treasure2 - treasure1) == 2)	
	{
		//hand of player 1 after cardeffect
		showHand(1,&G, &treasure1);
		showHand(1, &testG, &treasure2);
		if((treasure1 - treasure2) == 0)
			printf("Success!\n");
		else
			printf("Test Failed - Affected Player 1's hand\n");
	}
	else
		printf("Test Failed - Adventurer card did not add 2 treasure cards\n");

	// ----------- TEST 2 & 3: Confirm discard of non-treasure cards + adventurer --------------
	printf("\nTEST 2: Confirm discard of adventurer card and non-treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//print out the cards in the discard pile
	showDiscard(0,&G);
	showDiscard(0,&testG);

	printf("\nCall adventurer card effect\n\n");

	//call cardeffect
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	int result;
	result = showDiscard(0,&testG);

	if (result == 1)
		printf("\nTest Failed\n\n");
	else if (result == 2)
		printf("\nSuccess - Adventurer card discarded and non-treasure cards\n\n");
	else
		printf("\nTest Failed - Non-treasure cards discarded but not adventurer card\n\n");
	
	return 0;
}



