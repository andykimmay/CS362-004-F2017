//
//  randomtestcard2.c
//  Unit Tests Assignment3
//
//  This program tests the stewardRef function randomly
//
//  Created by David White on 10/31/17.
//  Copyright © 2017 Oregon State University. All rights reserved.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int checkStewardRef(int choice1, int choice2, int choice3,  struct gameState *state, int handPos);
void printGameState(struct gameState *Pre, struct gameState *Post);
void fillWithCards(struct gameState *state, int cardsPlayed[]);
int addRandomCard(struct gameState *state, int card);
int getRandomCard(struct gameState *state);
int totalErrors;

int main(){
    int turn,deckCnt,discardCnt,handCnt,players,handPos,choice1,choice2, choice3;
    int seed=1000;
    int tests=100000;     //number of tests to run
   
    int k[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,
        village,baron,steward};
    
    struct gameState G;
    
    printf("Testing Steward.\n");
    printf("Random Tests.\n");
    
    srand(seed);
    totalErrors=0;
    for(int rep=0;rep<tests;rep++){
        //initialize gameState
        players=2+ rand()%(MAX_PLAYERS-1);      //range 2-4
        initializeGame(players, k, seed, &G);
        turn = rand()%players;                     //create a random players turn
        deckCnt= rand() %  MAX_DECK;   //cards in deck
        discardCnt =rand()%(MAX_DECK-deckCnt);  //cards in discard pile
        handCnt=rand() % (MAX_DECK - deckCnt - discardCnt );   //cards in hand
        G.whoseTurn = turn;
        G.deckCount[turn] =deckCnt;
        G.discardCount[turn]=discardCnt;
        G.handCount[turn]=handCnt;
        fillWithCards(&G,k);                                  //fills deck, hand and discard with random cards
        choice1=1+ floor(Random()*3);
        choice2= floor(Random()*handCnt);
        choice3 = floor(Random()*handCnt);
        handPos =addRandomCard(&G,steward);
        printf("*********************************************************\n");
        printf("\nTest %d:\t", rep);
        printf("handCnt: %d choice 1: %d, choice 2: %d, choice 3: %d handPos:%d\n ", handCnt,choice1,choice2, choice3, handPos);
        totalErrors += checkStewardRef(choice1, choice2, choice3, &G, handPos);
        printf("-----End of Test %d\n",rep);
        printf("*********************************************************\n\n\n");
    }
    printf("%d Errors found in %d tests.\n", totalErrors, tests);
}

/*checkStewardRef
 input: structure gameState
 output: none
 pre-condition: gamestate has been initialized with values
 post-condition: 
 */
int checkStewardRef(int choice1, int choice2, int choice3,  struct gameState *state, int handPos){
    int ret,  errors;
    int turn = state->whoseTurn;
    struct gameState pre;
    errors =0;
    memcpy(&pre, state, sizeof(struct gameState));            //save game state
    ret=stewardRef(choice1, choice2, choice3, state,  handPos);
    int handDiff=state->handCount[turn] -pre.handCount[turn];
    int discardFromHandDiff = pre.handCount[turn] - state->handCount[turn];
    int deckDiff=pre.deckCount[turn] - state->deckCount[turn];
    int discardDiff = pre.discardCount[turn] - state->discardCount[turn];
    int handCount = state->handCount[turn];
    
    if(!ret){
        if(state->handCount[turn]<0){
            printf("****Error---Number of  cards in hand dropped below 0.\n");
            printGameState(&pre,state);
            errors++;
        }
        
        if(choice1==1){
            if(handDiff!=1){
                printf("****Error---Incorrect number of cards in hand: \t%d\n", handDiff);
                printGameState(&pre,state);
                errors++;
            }
            if((deckDiff != 2) && (abs(deckDiff-2)!=abs(discardDiff))){
                printf("****Error---Incorrect number of cards in deck: \t %d  removed\n", deckDiff);
                printGameState(&pre,state);
                errors++;
            }
        }
        if(choice1==2){
            if(state->coins!=(pre.coins +2)){
                printf("****Error---Incorrect number of coins added.\n");
                errors++;
            }
        }
        
        if ((choice1 == 1) || (choice1 == 2)){
            if(discardDiff !=1){
                printf("****Error---Incorrect number of cards discarded. Expeceted: 1 Actual: %d\n", discardDiff);
                printGameState(&pre,state);
                errors++;
            }
        }

        if(choice1==3){
            if((discardFromHandDiff !=3 ) && (handCount > 0) ){
                printf("pre: %d post: %d\n", pre.handCount[turn], state->handCount[turn]);
                printf("****Error---Incorrect number of cards trashed from hand: \t%d \n",discardDiff);
                printGameState(&pre, state);
                errors++;
            }
            //Not sure if this is correct
            if(abs(discardDiff) != 1){
                printf("pre: %d post: %d\n", pre.discardCount[turn], state->discardCount[turn]);
                printf("****Error---Incorrect number of cards added to discard deck: \t%d \n",discardDiff);
                printGameState(&pre, state);
                errors++;
            }
    }
    //print number of errors in this iteration.
    if(errors)
        printf("%d errors in code\n",errors);
    else
        printf("Passed Tests\n");
    }
    return errors;
}
/*fillWithCards
 input: gameState
 output: nothing
 pre-condition: gamestate has been initialized
 post-condition: gamestate's discard, hand, and deck will be filled for the player whose turn it is.
 */
void fillWithCards(struct gameState *State, int cards[]){
    int turn = State->whoseTurn;
    int deckCount=State->deckCount[turn];
    int handCount=State->handCount[turn];
    int discardCount=State->discardCount[turn];
    for(int i=0;i<deckCount;i++){
        State->deck[turn][i]=cards[(int)floor(Random()*10)];
    }
    for(int i=0;i<handCount;i++){
        State->hand[turn][i]=cards[(int)floor(Random()*10)];
    }
    for(int i=0;i<discardCount;i++){
        State->discard[turn][i]=cards[(int)floor(Random()*10)];
    }
}

/*addRandomCard
 input: gamestate before the tests begin,
 output: returns the position of the randomly placed smithy
 pre-condition: The gamestate has been intiallized with cards in the players hand
 post-condition: The hand of the current player will have a smithy placed randomly in the deck
        the function will return the location within the hand
 */
int addRandomCard(struct gameState *state, int card){
    int handPos;
    int turn = state->whoseTurn;
    int handCnt = state->handCount[turn];
    handPos = floor(Random()*handCnt);
    //There must be a card in the hand in order to play the card, therefore a card is added
    //if a hand is empty, the desired card is placed in the hand.
    if(handCnt==0){
        state->hand[turn][0]=card;
        state->handCount[turn]=1;
        handPos=0;
    }
    else {
        state->hand[turn][handPos]=card;
    }
    return handPos;
}



/*printfGameState
 input: gamestate at 2 different periods
 output: nothing
 pre-condition:Pre is the earlier gamestate Post is a later gamestate
 post-condition: none
 */
void printGameState( struct gameState *Pre, struct gameState *Post){
    char card[27][15]={"Curse","Estate","Duchy","Province","Copper","Silver","Gold",
        "Adventurer", "Council_room","Feast","Gardens", "Mine","Remodel","Smithy","Village",
        "Baron", "Great Hall", "Minion","Steward","Tribute","Ambassador","Cutpurse", "Embargo",
        "Outpost", "Salvager","Sea Hag","Treasure Map"};
    int who=Post->whoseTurn;
    int preDeckCnt=Pre->deckCount[who];
    int postDeckCnt=Post->deckCount[who];
    int preHandCnt=Pre->handCount[who];
    int postHandCnt=Post->handCount[who];
    int preDiscardCnt=Pre->discardCount[who];
    int postDiscardCnt=Post->discardCount[who];
    printf("**************************************************\n");
    printf("**************************************************\n");
    printf("\t\tGame State before and after:");
    printf("\n\nDeck-  \tPre: %d  Post: %d\n",preDeckCnt, postDeckCnt);
  
    //Cards Added to deck
    if(postDeckCnt -preDeckCnt >0){
        printf("Cards Added\n\t");
        for(int i=preDeckCnt;i<postDeckCnt;i++)
            printf("%s ", card[ Post->deck[who][i] ]);
    }
    //Cards taken from Deck
    else{
        printf("Cards Removed\n\t");
        for(int i=postDeckCnt;i<preDeckCnt;i++)
            printf("%s ", card[ Pre->deck[who][i] ]);
    }
    printf("\nHand- \tPre: %d Post: %d\n",preHandCnt,postHandCnt);
    
    //Cards Added to hand
    if(postHandCnt -preHandCnt >0){
        printf("Cards Added\n\t");
        for(int i=preHandCnt;i<postHandCnt;i++)
            printf("%s ", card[ Post->hand[who][i] ]);
    }
    //Cards taken from Deck
    else{
        printf("Cards Removed\n\t");
        for(int i=postHandCnt;i<preHandCnt;i++)
            printf("%s ", card[ Pre->hand[who][i] ]);
    }
    printf("\nDiscard- \tPre: %d Post: %d\n", preDiscardCnt, postDiscardCnt);

    //Cards Added to discard
    if(postDiscardCnt -preDiscardCnt >0){
        printf("Cards Added\n\t");
        for(int i=preDiscardCnt;i<postDiscardCnt;i++)
            printf("%s ", card[ Post->discard[who][i] ]);
    }
    //Cards taken from Discard
    else{
        printf("Cards Added\n\t");
        for(int i=postDiscardCnt;i<preDiscardCnt;i++)
            printf("%s ", card[ Pre->discard[who][i] ]);
    }
    
    printf("\n**************************************************\n");
}
