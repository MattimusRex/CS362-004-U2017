//Unit Test suite for numHandCards()

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//tests all hand sizes
void numHandCardsAllSizes(struct gameState* state, int player) {
    int i;
    int failed = 0;
    for (i = 0; i < MAX_HAND; i++) {
        state->handCount[player] = i;
        int numCards = numHandCards(state);
        if (numCards != i) {
            failed = 1;
            break;
        }
    }
    if (failed == 0)
        printf("numHandCardsAllSizes: PASSED\n");
    else if (failed == 1)
        printf("numHandCardsAllSizes: FAILED\n");
    
    printf("\n");
    return;
}

void numHandCards2Players(struct gameState* state) {
    state->handCount[0] = 4;
    state->handCount[1] = 2;
    int numCards = numHandCards(state);
    if (4 == numCards && state->handCount[1] == 2)
        printf("numHandCard2Players: PASSED\n");
    else
        printf("numHandCard2Players: FAILED\n");
    
    printf("\n");
    return;    
}


int main(int argc, char** argv) {
    struct gameState state;
    int numberOfPlayers = 4;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);

    int player = state.whoseTurn;
`
    //check that numHandCards correctly reports hand size for all possible hand sizes
    numHandCardsAllSizes(&state, player);

    //check that changing a different players hand size doesnt affect current player
    numHandCards2Players(&state);

    return 0;
}
