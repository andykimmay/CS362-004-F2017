//
//  cardtest4.c
//  Unit Tests Assignment3
// Test for Steward
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
    int choice1,choice2,choice3,handpos;
    struct gameState  G, Backup;
    int turn=G.whoseTurn;
    
    for(choice1=1;choice1<=3;choice1++){
        initializeGame(numPlayer, k, seed, &G);
        G.hand[turn][G.handCount[turn]]=smithy;
        G.handCount[turn]++;
        choice2=G.handCount[turn];
        G.hand[turn][G.handCount[turn]]=adventurer;
        G.handCount[turn]++;
        choice3=G.handCount[turn];
        G.hand[turn][G.handCount[turn]]=steward;
        G.handCount[turn]++;
        handpos=G.handCount[turn];        Backup=G;
        stewardRef(choice1, choice2, choice3, &G, handpos);
        printf("\n\nTesting Steward\n\n");
        printf("Choice: %d\n",choice1);
        printf("Hand Before: %d  After:%d\n",Backup.handCount[turn],G.handCount[turn]);
        printf("\tHand Before: ");
        for (int i=0;i<Backup.handCount[turn];i++){
            printf("%s ",card[Backup.hand[turn][i]]);
        }
        printf("\n\tHand After: ");
        for (int i=0;i<G.handCount[turn];i++){
            printf("%s ",card[G.hand[turn][i]]);
        }
        //Deck
        printf("\nDeck Before: %d  After:%d\n",Backup.deckCount[turn],G.deckCount[turn]);
        printf("\tDeckBefore: ");
        for (int i=0;i<Backup.deckCount[turn];i++){
            printf("%s ",card[Backup.deck[turn][i]]);
        }
        printf("\n\tDeckAfter: ");
        for (int i=0;i<G.deckCount[turn];i++){
            printf("%s ",card[G.deck[turn][i]]);
        }
        
        //Discard
        printf("\nDiscard Before: %d  After:%d\n",Backup.discardCount[turn],G.discardCount[turn]);
        printf("\tDiscard Before: ");
        for (int i=0;i<Backup.discardCount[turn];i++){
            printf("%s ",card[Backup.discard[turn][i]]);
        }
        printf("\n\tHand After: ");
        for (int i=0;i<G.discardCount[turn];i++){
            printf("%s ",card[G.discard[turn][i]]);
        }
        printf("\nCoins Before: %d  After: %d\n",Backup.coins, G.coins);
        
        if(choice1==1){
            printf("%d",G.handCount[turn] -Backup.handCount[turn]);
            if(abs(G.handCount[turn] -Backup.handCount[turn])!=2){
               printf("****Error--- correct number of cards not added to hand");
                count++;
            }
        }
        if(choice1==2){
            if(G.coins!=(Backup.coins +2)){
                printf("****Error---incorrect number of coins added to hand");
                count++;
            }
        }
        if(choice1==3){
            if(abs(Backup.handCount[turn] -G.handCount[turn])!=2){
                printf("****Error---incorrect number of cards trashed from hand");
                count++;
            }
        }
    }
    if(count>0)
        printf("\n****Found %d errors****\n",count);
    else
        printf("\n\n****All tests passed****\n");
    return 0;
}

