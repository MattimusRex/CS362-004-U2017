//random tester for the village card
//village gives +1 card and +2 actions

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>



int checkVillage(int p, struct gameState* post, int handPos) {
    //copy state
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    //play village
    cardEffect(village, -1, -1, -1, post, handPos, 0);

    //basically play village manually
    //draw 1 card
    int card;
    if (pre.deckCount[p] > 0) {
        card = pre.deck[p][--pre.deckCount[p]];
        pre.hand[p][pre.handCount[p]++] = card;                     
    }    
    else if (pre.discardCount[p] > 0) {
        card = pre.discard[p][--pre.discardCount[p]];
        pre.hand[p][pre.handCount[p]++] = card;
    }                        

    //add 2 actions
    pre.numActions += 2;

    //discard village - use their discard function because their's is broken and if you dont use their's you cant accurately test smithy effects
    discardCard(handPos, p, &pre, 0);

    // if (pre.discardCount[p] == post->discardCount[p]) {
    //     printf("discardCount PASSED\n");
    //     for (i = 0; i < pre.discardCount[p]; i++) {
    //         if (pre.discard[p][i] != post->discard[p][i]) {
    //             printf("discard count: %d    discards mismatched on card %d\n", pre.discardCount[p], i);
    //             return -1;
    //         }
    //     }
    // }
    // if (pre.deckCount[p] == post->deckCount[p]) {
    //     printf("deckCount PASSED\n");
    //     for (i = 0; i < pre.deckCount[p]; i++) {
    //         if (pre.deck[p][i] != post->deck[p][i]) {
    //             printf("deck count: %d    deck mismatched on card %d\n", pre.deckCount[p], i);
    //             return -1;
    //         }
    //     }
    // }
    // if (pre.handCount[p] == post->handCount[p]) {
    //     printf("handCount PASSED\n");
    //     for (i = 0; i < pre.handCount[p]; i++) {
    //         if (pre.hand[p][i] != post->hand[p][i]) {
    //             printf("card %d: pre: %d  post: %d\n", i, pre.hand[p][i], post->hand[p][i]);
    //         }
    //     }
    // }

    //compare pre and post
    return (memcmp(&pre, post, sizeof(struct gameState)));
} 

int main(int argc, char** argv) {
    //setup initial videos
    struct gameState state;
    srand(time(NULL));
    //randomize gameState
    int i;
    int n;
    int p;
    int j;
    int failed = 0;
    memset(&state, 0, sizeof(struct gameState));
    for (n = 0; n < 20000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&state)[i] = rand() % 256;
        }
        //change important gameState fields to valid random values
        p = rand() % 4;
        state.numPlayers = 4;
        state.whoseTurn = p;
        state.deckCount[p] = rand() % MAX_DECK;
        state.discardCount[p] = rand() % MAX_DECK;
        for (j = 0; j < state.discardCount[p]; j++) {
            int card = rand() % (treasure_map + 1);
            state.discard[p][j] = card;
        }        
        for (j = 0; j < state.deckCount[p]; j++) {
            int card = rand() % (treasure_map + 1);
            state.deck[p][j] = card;
        }
        int originalDeckCount = state.deckCount[p];
        //account for space to add the 3 drawn cards
        state.handCount[p] = (rand() % (MAX_HAND - 2)) + 1;
        state.hand[p][state.handCount[p] - 1] = village;
        state.playedCardCount = rand() % MAX_DECK;

        //run test
        int result = checkVillage(p, &state, state.handCount[p] - 1);
        //all test cases where deckCount starts at 0 will fail because of the shuffle in draw card.
        //shuffle is random and will not be the same between the test and the card effect function.  
        //the card drawn will not match.  better suited for unit test 
        if (result != 0 && originalDeckCount != 0) {
            printf("Test Case %d FAILED\n", n);
            failed = 1;
        }
    }
    if (failed == 0) {
        printf("All test cases PASSED\n");
    }
    return 0;
}