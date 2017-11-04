#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "smithy"
#define iterations 50

//function to get name of card
const char* getCardName(enum CARD card)
{
	switch(card)
	{
		case estate: return "estate";
		case copper: return "copper";
		case adventurer: return "adventurer";
		case embargo: return "embargo";
		case village: return "village";
		case minion: return "minion";
		case mine: return "mine";
		case cutpurse: return "cutpurse";
		case sea_hag: return "sea_hag";
		case tribute: return "tribute";
		case smithy: return "smithy";
		case council_room: return "council_room";
	}
}		     
//function to test for various aspects of test card effects
int checkTestCard(int player, struct gameState *state)
{
	int i, hc = 0, hc2 = 0, dc = 0, dc2 = 0;
	
	//test to see if test card adds cards
	hc = state->handCount[player];
	dc = state->playedCardCount;

	//call card effect
	cardEffect(smithy, 0, 0, 0, state, state->handCount[player], 0);
	
	//adjust player handcount
	hc2 = state->handCount[player];
	dc2 = state->playedCardCount;

	//if handcount is not 3 more than previous
	if(hc2 - hc != 3)
	{
		//if the deck is not empty
		if(state->deckCount[player] == 0)
		{	
			return 0;
		}
		//return error
		else
		{
			printf("Test Failed\n");
			printf("Number of cards before: %d ",dc);
			printf("Number of cards after: %d\n",dc2);
			for (i = 0; i < state->deckCount[player]; i++)
			{
				printf("%s\n",getCardName(state->deck[player][i]));
			}
			printf("%d",state->deckCount[player]);
			return 1;
		}
	}

	//if discard count is not 1 more than previous, return error
	if(dc2 - dc != 1)
	{
		printf("Test Failed\n");
		printf("Smithy card not discarded properly\n");
		return 1;
	}

	return 0;
}


int main() {
	int i;
	int k[12] = {copper, estate, adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	SelectStream(2);
	PutSeed(3);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	for(i = 0; i < iterations; i++)
	{
		int p, j, y, x;
		
		//initialize game state
		struct gameState G;
		G.phase = 0;
		x = floor(Random() * 5);
		G.numActions = x;
		x = floor(Random() * 5);
		G.numBuys = x;
		G.playedCardCount = 0;
		
		//random number of players
		p = (floor(Random()* 3) + 1);
		G.numPlayers = p;

		//fill deck and hand with random cards
		for (j = 0; j < p; j++)
		{
			G.deckCount[j] = floor(Random() * MAX_DECK);
			//printf("deck count: %d\n",G.deckCount[j]);
			
			//fill decks with random cards
			for (y = 0; y < G.deckCount[j]; y++)
			{
				x = floor(Random() * 12);
				G.deck[j][y] = k[x];
				//printf("%d\n",y);
				//printf("%s\n",getCardName(G.deck[j][y]));
			}	
			do
			{	
				G.handCount[j] = floor(Random() * MAX_DECK);	
			}while(G.deckCount[j] < G.handCount[j]);

			//printf("hand: \n");
			for (y = 0; y < G.handCount[j]; y++)
			{	
				//drawCard(j, &G);
				x = G.deckCount[j];
				G.hand[j][y] = G.deck[j][x - 1];
				G.deckCount[j]--;
				//printf("%d\n",y);
				//printf("%s\n",getCardName(G.hand[j][y]));
			}
			G.hand[j][G.handCount[j]] = smithy;
		}
	
		//run card test
		if(checkTestCard(0,&G) == 1)
			return 1;
	}
	printf("Test Successful\n");
	return 0;
}



