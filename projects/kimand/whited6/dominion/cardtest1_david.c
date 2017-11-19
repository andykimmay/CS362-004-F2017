//
//  cardtest1.c
//  Unit Tests Assignment3
//
//  Created by Cheetah on 10/21/17.
//  Copyright © 2017 Oregon State University. All rights reserved.
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
    int numPlayer=2;
    char card[27][15] = {"Curse","Estate","Duchy","Province","Copper","Silver","Gold",
    "Adventurer","Council_room","Feast","Gardens","Mine","Remodel","Smithy","Village",
        "Baron","Great Hall", "Minion","Steward","Tribute","Ambassador","Cutpurse",
        "Embargo",     "Outpost", "Salvager","Sea Hag","Treasure Map"};
    int k[10]={adventurer,council_room,feast,gardens, mine, remodel, smithy, village, baron,
        great_hall};
    int count=0;
    struct gameState  G, Backup;
    G.whoseTurn=0;

    initializeGame(numPlayer, k, seed, &G);
    
    Backup=G;                               //back up game state to compare to after tests.
    
    smithyRef(&G,smithy);
    
    for(int turn=0;turn<numPlayer;turn++){
        printf("\n\t\tPlayer %d Turn\n",turn);
        //*******Hand***************
        printf("Hand count- before: %d after: %d\n",Backup.handCount[turn],G.handCount[turn]);
        //Hand count before Smithy
        printf("*Hand Before Smithy played*\n\t");
        if(Backup.handCount[turn]>0){
            for (int i=0;i<Backup.handCount[turn];i++){
                printf("%s ",card[Backup.hand[turn][i]]);
            }
        }
        else
            printf("No cards in handcount before Smithy\n");
        //Check hand count after Smithy
        printf("\n*After Smithy played*\n\t");
        if(G.handCount[turn]>0){
            for (int i=0;i<G.handCount[turn];i++){
                printf("%s ",card[G.hand[turn][i]]);
            }
        }
        else
            printf("No cards in hand after Smithy\n");
        if(G.whoseTurn==turn){
            //Backup.handCount[turn]+3-1 should be the count after a smithy has been played.
            if(G.handCount[turn]!= Backup.handCount[turn]+3-1){
                printf("\n****Error- Count is off  should be :%d\n", Backup.handCount[turn]+3-1);
                count++;
            }
        }
        else{
            //Check the opponent's card to ensure they haven't changed
            if(Backup.handCount[turn]!=G.handCount[turn]){
                printf("\n****Error- player %d hand has changed \n",turn);
                count++;
            }
        }
        //*****Deck*************
        printf("\n\n\nDeck count- before: %d after: %d\n",Backup.deckCount[turn],G.deckCount[turn]);
        printf("*Deck Before Smithy played*\n\t");
        if(Backup.deckCount[turn]>0)
            for (int i=0;i<Backup.deckCount[turn];i++){
                printf("%s ",card[Backup.deck[turn][i]]);
            }
        else
            printf("No cards in deck before Smithy\n");
        
        printf("\n*After Smithy played*\n\t");
        if(G.deckCount[turn]>0)
            for (int i=0;i<G.deckCount[turn];i++){
                printf("%s ",card[G.deck[turn][i]]);
            }
        else
            printf("No cards in deck after Smithy\n");
        if(G.whoseTurn==turn){
            //3 cards should be missing from the deck
            if(Backup.deckCount[turn]- G.deckCount[turn]!=3){
                printf("\n****Error- 3 Cards should have been removed instead :%d have "
                       "been removed\n", Backup.deckCount[turn]- G.deckCount[turn]);
                count++;
            }
        }
        else{
            //Check the opponent's card to ensure they haven't changed
            if(Backup.deckCount[turn]!=G.deckCount[turn]){
                printf("\n****Error- player %d deck has changed \n",turn);
                count++;
            }
        }
        
        //**********Discard********
        printf("\n\n\nDiscard count- before: %d after: %d\n",Backup.discardCount[turn],
               G.discardCount[turn]);
        
        if(Backup.discardCount[turn] >0){
            printf("*Discard Before Smithy played*\n\t");
            for (int i=0;i<Backup.discardCount[turn];i++){
                printf("%s ",card[Backup.discard[turn][i]]);
            }
        }
        else
            printf("\nNo cards in discard pile before Smithy\n");
        
        if(G.discardCount[turn]>0){
            printf("\n*After Smithy played\n\t");
            for (int i=0;i<G.discardCount[turn];i++){
                printf("%s ",card[G.discard[turn][i]]);
            }
        }
        else
            printf("\nNo cards in discard pile after Smithy\n");
        if(G.whoseTurn==turn){
            //discard pile should not have changed
            if(Backup.discardCount[turn]!= G.discardCount[turn]){
                printf("\n****Error- Cards have been discarded :%d have"
                       "been discarded\n", Backup.discardCount[turn]- G.discardCount[turn]);
                count++;
            }
        }
        else{
            //Check the opponent's card to ensure they haven't changed
            if(Backup.discardCount[turn]!=G.discardCount[turn]){
                printf("\n****Error- player %d deck has changed ",turn);
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

