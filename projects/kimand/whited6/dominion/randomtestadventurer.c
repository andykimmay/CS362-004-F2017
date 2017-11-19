#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "adventurer"
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
	int i, x, y, tc = 0, tc2 = 0;
	
	x = state->handCount[player];
	
	//test to see if test card adds treasure cards
	for (i = 0; i < x; i++)
	{
		if (state->hand[player][i] == copper)
			tc++;
	}
	
	//cardEffect(adventurer, 0, 0, 0, state, 0, 0);
	//adjust player handcount
	y = state->handCount[player];

	//recount treasure cards
	for (i = 0; i < y; i++)
	{
		if (state->hand[player][i] == copper)
			tc2++;
	}

	tc2 += 3;

	if(tc2 - tc != 3)
	{
		if(state->deckCount[player] == 0)
		{	
			return 0;
		}
		else
		{
			/*
			printf("Test Failed\n");
			printf("tc: %d ",tc);
			printf("tc2: %d\n",tc2);
			
			for (i = 0; i < state->deckCount[player]; i++)
			{
				printf("%s\n",getCardName(state->deck[player][i]));
			}
			printf("%d",state->deckCount[player]);
			*/
			return 1;
		}
	}

	if((tc2 - tc) != (y - x))
	{
		printf("Test Failed\n");
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
				//printf("deck count: %d\n",y);
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
			G.hand[j][G.handCount[j]] = adventurer;
		}
	
		//run adventurer card test
		if(checkTestCard(0,&G) == 1)
			return 1;
	}
	printf("Test Successful\n");
	return 0;
}



