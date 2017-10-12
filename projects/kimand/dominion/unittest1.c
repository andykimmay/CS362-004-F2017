#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main () {
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int maxHandCount = 5;
	int r, p, deckCount, discardCount, handCount, bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			       remodel, smithy, village, baron, great_hall};
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	    for (i = 0; i < MAX_HAND; i++)
	    {
		    coppers[i] = copper;
		    silvers[i] = silver;
		    golds[i] = gold;
	    }

	struct gameState G;

	printf ("Testing drawCard.\n");

return 0;
}

