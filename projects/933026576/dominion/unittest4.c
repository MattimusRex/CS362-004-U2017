//Unit Test suite for numHandCards()

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int l[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

    int i;
    int j;
    int k;
    struct gameState pre;
    struct gameState post;

    //test all handsizes of all players of all player amounts and make sure nothing else changes    
    for (i = 2; i < 5; i++) {
        initializeGame(i, l, 1, &pre);
        for (j = 0; j < i; j++) {
            pre.whoseTurn = j;
            for (k = 0; k < MAX_HAND; k++) {
                pre.handCount[j] = k;
                memcpy(&post, &pre, sizeof(struct gameState));
                int numCards = numHandCards(&pre);
                if (numCards != k || memcmp(&pre, &post, sizeof(struct gameState)) != 0) {
                    printf("numHandCards: FAILED\n");
                    return -1;
                }
            }
        }
    }
    printf("numHandCards: PASSED\n");

    return 0;
}
