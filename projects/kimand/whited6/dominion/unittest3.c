#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

//function to get name of card
const char* getCardName(enum CARD card)
{
	switch(card)
	{
		case estate: return "estate";
		case copper: return "copper";
		case embargo: return "embargo";
	}
}		     

//function to print out the player's hand to confirm test
int showHand(int player, struct gameState *state, int card) {
	int i, j, count = 0;
	j = state->handCount[player];
	printf("Player %d's Hand:\n", player);
	for (i=0;i<j;i++)
	{
		printf("%s\n", getCardName(state->hand[player][i]));
		if(state->hand[player][i] == card)
			count = count + 1;
	}
	return count;
}

//function to print out player's discard prior to drawing cards
int showDiscard(int player, struct gameState *state, int card) {
	int i = 0, count = 0;
	int discardCards = state->discardCount[player];
	printf("Player %d's discard pile:\n", player);
	for (i=0;i<discardCards;i++)
	{
		printf("%s\n", getCardName(state->discard[player][i]));
		if (state->discard[player][i] == card)
			count = count + 1;
	}
	return count;
}

//function to print out players deck
int showDeck(int player, struct gameState *state, int card) {
	int i = 0, count = 0;
	int deckCards = state->deckCount[player];
	printf("Player %d's deck:\n", player);
	for (i=0;i<deckCards;i++)
	{
		printf("%s\n", getCardName(state->deck[player][i]));
		if (state->deck[player][i] == card)
			count = count + 1;
	}
	return count;
}

int main() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			gardens, tribute, smithy, council_room};

	int count = 0;

	// initialize a game state
	initializeGame(numPlayers, k, seed, &G);

	memcpy(&testG, &G, sizeof(struct gameState));

	printf ("Testing function gainCard.\n\n");

	printf("Initial deck\n");

	showDeck(0,&testG, embargo);

	//---------Test 1: gain card to deck  -------------------
	
	printf("Gain embargo card to deck\n");

	gainCard(embargo, &testG, 1, 0);
	
	count = showDeck(0, &testG, embargo);

	if (count == 1)
		printf("Success!\n\n");
	else 
		printf("Test Failed\n\n");

	//---------Test 2: gain card to hand -------------------------------
	printf("Gain embargo card to hand\n\n");	

	printf("Initial hand\n");

	showHand(0, &testG, embargo);

	gainCard(embargo, &testG, 2, 0); 
	
	count = showHand(0, &testG, embargo);

	if(count == 1)
		printf("Success!\n\n");
	else
		printf("Test Failed\n\n");

	//---------Test 3: gain card to discard -------------------------------
	printf("Gain embargo card to discard\n\n");	
	
	printf("Initial discard\n\n");

	showDiscard(0, &testG, embargo);

	gainCard(embargo, &testG, 0, 0); 
	
	count = showDiscard(0, &testG, embargo);

	if(count == 1)
		printf("Success!\n\n");
	else
		printf("Test Failed\n\n");

	return 0;
}

