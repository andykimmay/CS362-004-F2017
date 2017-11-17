//
//  unittest3.c
//  Testing of whoseTurn function
//
//  Created by David White on 10/14/17.
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
    int seed=1000;
    int numPlayer = 2;
    int r,turn;
    int count=0;
    int passed=0;
    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState G;
    r = initializeGame(numPlayer, k, seed, &G);
    
    printf("Testing whoseTurn\n");
    for(int i=0;i<=MAX_PLAYERS+1;i++){
        G.whoseTurn=i;
        turn= whoseTurn(&G);
        if(NOISY_TEST)
            printf("whoseTurn set to %d,  actual value %d\n",i, turn);
        if(i!=turn){
            printf("Error:\n\tActual players turn does not match  %d  != %d\n",i,turn);
            count++;
            passed=0;
        }
        if(i>MAX_PLAYERS){
            printf("Error: \n\tWent beyond the number of  players allowed in the game. \n"
                   "Max Player: %d != Who's turn:%d\n",MAX_PLAYERS,i);
             count++;
            passed=0;
            }
        if(i<1){
            printf("Error: \n\tToo few players to play game: %d\n", i);
            count++;
            passed=0;
        }
    }
    if(passed)
        printf("All tests passed\n");
    else
        printf("Found %d errors\n",count);
    return 0;
}
