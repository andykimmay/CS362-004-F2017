#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council room"

//function to get name of card
const char* getCardName(enum CARD card)
{
	switch(card)
	{
		case estate: return "estate";
		case copper: return "copper";
		case council_room: return "council room";
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
		if (state->playedCards[i] == council_room)
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

	G.hand[0][5] = council_room;
	G.handCount[0] = G.handCount[0] +1;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: confirm that council room adds 4 cards --------------
	printf("TEST 1: Confirm card adds 4 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//hand of player 0 before cardeffect
	showHand(0,&G);	
	showHand(0,&testG);

	printf("Call council room card effect\n\n");

	//call cardeffect
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	//hand of player 0 after cardeffect
	showHand(0, &testG);
	
	if ((testG.handCount[0] - G.handCount[0]) == 3)	
	{
		printf("Success!\n\n");
	}
	else
		printf("Test Failed - did not add 4 cards\n");

	if (showDiscard(0,&testG) == 0)
		printf("\nSuccess - council room discarded\n\n");
	else
		printf("\nTest Failed - council room not discarded\n");


	// ----------- TEST 2: Confirm additional buy --------------
	
	printf("\nTEST 2: Confirm council room adds an additional buy\n");

	int buyB, buyA;
	buyB = G.numBuys;
	buyA = testG.numBuys;

	printf("\nNumber of Buys before council room: %d\n",buyB);
	printf("\nNumber of Buys after council room: %d\n",buyA);

	if (buyA - buyB == 1)
		printf("\nSuccess!\n\n");
	else
		printf("Test Failed - village card did not add a single action\n");

	// ------------ TEST 3: confirm additional draws for other players -------
		
	printf("\nTEST 3: Confirm council room adds a card for other players\n");

	printf("Player 1's hand before and after council room\n");

	showHand(1,&G);
	showHand(1,&testG);

	if ((testG.handCount[1] - G.handCount[1]) == 1)
		printf("\nSuccess!\n");
	else
		printf("\nTest failed!\n");
	
	// ------------------------------------------------------------------------	
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}



