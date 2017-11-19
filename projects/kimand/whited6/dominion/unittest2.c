#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	printf ("Testing function getCost.\n\n");

	//---------Test 1: Get cost of cards  -------------------

	int i = 0, count = 0;
	for (i=0;i<27;i++)
	{
		printf("%d\n",getCost(i));
		count++;
	}
	if(count == 27){
		printf("Success!\n\n");
	}
	else{
		printf("Test Failed\n\n");
	}

	//---------Test 2: Get cost of card that doesn't exist -------------------------------
	printf("Test card that doesn't exist\n\n");	
	i = 30;
	printf("%d\n",getCost(i));

	if(getCost(i) == -1)
		printf("Success!\n\n");
	else
		printf("Test Failed\n\n");

	return 0;
}

