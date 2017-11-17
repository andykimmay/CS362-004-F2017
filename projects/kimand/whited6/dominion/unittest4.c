//
//  unittest4.c
//  Testing of kingdomCards function
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
    int count=0;
    int value;
    int *cards = NULL;
    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron, great_hall};
    char cardName[27][15]={"curse","estate","duchy","province","copper","silver","gold","adventurer","council_room","feast",
        "gardens","mine","remodel","smithy","village","baron","great_hall","minion","steward","tribute","ambassador",
        "cutpurse","embargo","outpost","salvager","sea_hag","treasure_map"};
    
    printf("Testing kingdomCards\n");
    cards = kingdomCards(k[0],k[1],k[2],k[3],k[4],k[5],k[6],k[7],k[8],k[9]);
    if(cards ==NULL){
        printf("Error:\n\t array not filled by kingdomCards()\n");
        count++;
    }
    else{
        if(NOISY_TEST)
            printf("Successfully passed cards back to function\n");
        for (int i=0;i<10;i++){
            value=cards[i];
            if(NOISY_TEST)
                printf("Card Expected: %s \n\tActual Card: %s\n",cardName[k[i]], cardName[value]);
            if(cardName[k[i]] !=cardName[value]){
                printf("Error:\n\tCard Expected: %s \n\tActual Card: %s\n",cardName[k[i]], cardName[value]);
                count++;
            }
        }
    }
      if(count==0)
        printf("All tests passed\n");
    else
        printf("Found %d errors\n",count);
    return 0;
}



