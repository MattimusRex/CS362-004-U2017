//Unit Test suite for whoseTurn()

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//tests that whoseTurn accurately reports the correct players turn.
//@param player: the correct player index
//@param state: current gameState 
void whoseTurnTest(struct gameState* state, int player) {
    struct gameState preState;
    memcpy(&preState, state, sizeof(struct gameState));
    printf("whoseTurnTest: player %d ", player);
    if (whoseTurn(state) == player && memcmp(&preState, state, sizeof(struct gameState)) == 0) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
    return;		
}


int main (int argc, char** argv) {
    //initialize game for testing with 4 people
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    //tests that whoseTurn correctly returns player and doesnt adjust state
    int i;
    int j;
    for (i = 2; i < 5; i++) {
        initializeGame(i, k, 1, &state);
        state.whoseTurn = 0;
        for (j = 0; j < i; j++) {
            whoseTurnTest(&state, j);
            state.whoseTurn++;
        }
    }  
    return 0;
}
