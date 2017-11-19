//
//  cardtest1.c
//  Unit Tests Assignment3
// Test for Feast
//  Created by David White on 10/21/17.
//  Copyright © 2017 Oregon State University. All rights reserved.
//


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rngs.h"


int main() {
    int seed=1000;
    int numPlayer=2;

    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron,
        great_hall};
  
    struct gameState  G;
    initializeGame(numPlayer, k, seed, &G);
    //Setting the supply to 0 for mine and trying to buy a mine card triggers a infinite loop
    G.supplyCount[mine]=0;
    feastRef(mine,&G);
    printf("Good bye");

    return 0;
}


