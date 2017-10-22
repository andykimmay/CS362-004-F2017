#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			gardens, tribute, smithy, council_room};
	int count;

	// initialize a game state
	initializeGame(numPlayers, k, seed, &G);

	printf ("Testing function supplyCount.\n\n");

	//---------Test 1: copper supply count  -------------------
	
	count = supplyCount(copper, &G);

	printf("Supply count: %d\n\n",count);

	if (count == 46)
		printf("Success!\n\n");
	else 
		printf("Test Failed\n\n");

	//---------Test 2: estate supply count -------------------------------
	
	count = supplyCount(estate, &G);

	printf("Supply count: %d\n\n",count);

	if (count == 8)
		printf("Success!\n\n");
	else 
		printf("Test Failed\n\n");

	//---------Test 3: embargo supply count -------------------------------
		
	count = supplyCount(embargo, &G);

	printf("Supply count: %d\n\n",count);

	if (count == 10)
		printf("Success!\n\n");
	else 
		printf("Test Failed\n\n");

	//--------Test 4: supply count of card not in game ---------------------
		
	count = supplyCount(outpost, &G);

	printf("Supply count: %d\n\n",count);

	if (count == -1)
		printf("Success!\n\n");
	else 
		printf("Test Failed\n\n");


	return 0;
}

