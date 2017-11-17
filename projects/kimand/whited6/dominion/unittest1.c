//
//  unittest1.c
//  Testing of getCost function
//
//  Created by David Whiteon 10/14/17.
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

    char card[27][15]={"curse","estate","duchy","province","copper","silver","gold","adventurer","council_room","feast",
        "gardens","mine","remodel","smithy","village","baron","great_hall","minion","steward","tribute","ambassador",
        "cutpurse","embargo","outpost","salvager","sea_hag","treasure_map"};
    int cost;
    int count=0;        //error count
    printf("Testing getCost(int cardNumber):\n");
   
    for (int i=curse-1; i<=treasure_map+1; i++ )
    {
        cost= getCost(i);
        if(NOISY_TEST){
            if(i>=curse && i<=treasure_map)
                printf("%s= %d\n",card[i],cost);
            else
                printf("Outside of range: %d\n",i);
        }
        switch (i)
        {
         //Cost of 0
            case curse:
            case copper:
                if(NOISY_TEST)
                    printf("Expected Cost: 0 Actual Cost: %d\n", cost);
                if(cost!=0){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };
                break;
        //Cost of 2
            case estate:
            case embargo:
                if(NOISY_TEST)
                    printf("Expected Cost: 2 Actual Cost: %d\n", cost);
                if(cost!=2){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };
                break;
        //Cost of 3
            case silver:
            case village:
            case great_hall:
            case steward:
            case ambassador:
                if(NOISY_TEST)
                    printf("Expected Cost: 3 Actual Cost: %d\n", cost);
                if(cost!=3){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };
                break;
        //Cost of 4
            case feast:
            case gardens:
            case remodel:
            case smithy:
            case baron:
            case cutpurse:
            case salvager:
            case sea_hag:
            case treasure_map:
                if(NOISY_TEST)
                    printf("Expected Cost: 4 Actual Cost: %d\n", cost);
                if(cost!=4){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };
                break;
        //Cost of 5
            case duchy:
            case council_room:
            case mine:
            case minion:
            case tribute:
            case outpost:
                if(NOISY_TEST)
                    printf("Expected Cost: 5 Actual Cost: %d\n", cost);
                if(cost!=5){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };
                break;
        //Cost of 6
            case gold:
            case adventurer:
                if(NOISY_TEST)
                    printf("Expected Cost: 6 Actual Cost: %d\n", cost);
                if(cost!=6){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };
                break;
        //Cost of 8
            case province:
                if(NOISY_TEST)
                    printf("Expected Cost: 8 Actual Cost: %d\n", cost);
                if(cost!=8){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };;
                break;
            default:
                if(NOISY_TEST)
                    printf("Value outside of range: %d\n", cost);
                if(cost!=-1){
                    printf("Error:\n\tUnexpected result: cost= %d\n",cost);
                    count++;
                };;
                break;
        }
    }
    
    if(count>0)
        printf("Found %d errors\n",count);
    else
        printf("All tests passed\n");
    return 0;
}