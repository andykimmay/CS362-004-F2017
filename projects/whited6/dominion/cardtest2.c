//
//  cardtest1.c
//  Unit Tests Assignment3
// Test for Adventurer
//  Created by David White on 10/21/17.
//  Copyright © 2017 Oregon State University. All rights reserved.
//


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed=1000;
    int numPlayer=2;
    char card[27][15] = {"Curse","Estate","Duchy","Province","Copper","Silver","Gold",
    "Adventurer","Council_room","Feast","Gardens","Mine","Remodel","Smithy","Village",
        "Baron","Great Hall", "Minion","Steward","Tribute","Ambassador","Cutpurse",
        "Embargo",     "Outpost", "Salvager","Sea Hag","Treasure Map"};
    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron,
        great_hall};
    int count=0;
    struct gameState  G, Backup;
    initializeGame(numPlayer, k, seed, &G);
    int turn = G.whoseTurn=0;
    for(int i=0;i<=treasure_map;i++){
        G.deck[turn][i]=4;
    }
    G.deckCount[0]=4*treasure_map;
    shuffle(turn,&G);
    Backup=G;                               //back up game state to compare to after tests.
    
    adventurerRef(&G);
    int deckDiff=Backup.deckCount[0]-G.deckCount[0];
    int handDiff=Backup.handCount[0]-G.handCount[0];
    int discardDiff=Backup.discardCount[0]-G.discardCount[0];
    printf("Testing Adventurer\n");
    printf("Deck Before: %d  After:%d\n",Backup.deckCount[0],G.deckCount[0]);
    printf("Hand Before: %d  After:%d\n",Backup.handCount[0],G.handCount[0]);
    printf("\tHand Before: ");
    for (int i=0;i<Backup.handCount[turn];i++){
        printf("%s ",card[Backup.hand[turn][i]]);
    }
    printf("\n\tHand After: ");
    for (int i=0;i<G.handCount[turn];i++){
        printf("%s ",card[G.hand[turn][i]]);
    }
    printf("\nDiscard Before: %d After:%d\n",Backup.discardCount[0],G.discardCount[0]);
    
    if((abs(handDiff))>2){
        printf("***Error--- Too many treasure cards added to hand");
        count++;
    }
    
    if((deckDiff +(handDiff+discardDiff)!=0)){
        printf("***Error--- cards not moved to proper location");
        count++;
    }
    
    if(count>0)
        printf("\n****Found %d errors****\n",count);
    else
        printf("\n\n****All tests passed****\n");
    return 0;
}

