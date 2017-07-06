//Unit Test suite for whoseTurn()

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//tests that whoseTurn accurately reports the correct players turn.
//@param player: the correct player index
//@param state: current gameState 
void whoseTurnTest(struct gameState* state, int player) {
    printf("whoseTurnTest: ");
    if (whoseTurn(state) == player) {
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
    int numberOfPlayers = 4;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);
    
    //tests that whoseTurn correctly returns player
    int i;  
    for (i = 0; i < numberOfPlayers + 1; i++) {
        whoseTurnTest(&state, i);
        state.whoseTurn++;
    }
    return 0;
}
