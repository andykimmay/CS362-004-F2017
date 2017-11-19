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
		case adventurer: return "adventurer";
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
	int playedCards = state->playedCardCount;
	printf("Player %d's discard pile:\n", player);
	for (i=0;i<playedCards;i++)
	{
		printf("%s\n", getCardName(state->playedCards[i]));
		if (state->playedCards[i] == card)
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
	int handpos = 5, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			gardens, tribute, smithy, council_room};
	int handC = 0, discardC = 0, deckC = 0;
	
	// initialize a game state
	initializeGame(numPlayers, k, seed, &G);
	
	//add adventurer card to hand
	G.hand[0][5] = adventurer;
	G.handCount[0] = G.handCount[0] + 1;

	memcpy(&testG, &G, sizeof(struct gameState));

	//---------Test 1: Count coppers (in hand and in deck) -------------------

	printf("Counting number of coppers\n\n");
	
	handC = showHand(0, &G, copper);
	printf("Count of coppers in hand: %d\n", handC);

	discardC = showDiscard(0, &G, copper);
	printf("Count of coppers in discard: %d\n",discardC);

	deckC = showDeck(0, &G, copper);
	printf("Count of coppers in deck: %d\n\n",deckC);

	printf("Total number of coppers: %d\n\n",(handC + discardC + deckC));

	printf("Calling full deck count for coppers: %d\n\n", fullDeckCount(0, copper, &G));

	if ((handC + discardC + deckC) == fullDeckCount(0,copper,&G))
		printf("Pass - correct count of coppers\n\n");
	else
		printf("Test Failed\n\n");
	
	//---------Test 2: Count adventurer (discard) -------------------------------
	printf("Testing for discard count\n\n");

	handC = 0, discardC = 0, deckC = 0;

	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	handC = showHand(0, &G, adventurer);
	printf("Count of adventurer in hand: %d\n", handC);

	discardC = showDiscard(0, &G, adventurer);
	printf("Count of adventurer in discard: %d\n",discardC);

	deckC = showDeck(0, &G, adventurer);
	printf("Count of adventurer in deck: %d\n\n",deckC);

	printf("\nTotal number of adventurer: %d\n\n",(handC + discardC + deckC));

	printf("Calling full deck count for adventurer: %d\n\n", fullDeckCount(0, adventurer, &G));

	if ((handC + discardC + deckC) == fullDeckCount(0,adventurer,&G))
		printf("Success!\n\n");
	else
		printf("Test Failed\n\n");
	
	return 0;
}

