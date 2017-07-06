//Unit Test suite for Smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

//readys player state for testing
void setState(struct gameState* state) {
    state->hand[state->whoseTurn][state->handCount[state->whoseTurn]] = smithy;
    state->handCount[state->whoseTurn]++;
}

//tests 1 call of Smithy card
//smithy is supposed to draw 3 cards.
//check that it draws correct amount of cards
//check that it doesnt alter other aspects of game state (buys, actions, etc)
//check that it is discarded correctly
void testSmithyNormal(struct gameState* state, int handPos, int* bonus) {
    printf("testing smithy normal\n");
    int player = state->whoseTurn;
    int preHandCount = state->handCount[player];
    int preNumBuys = state->numBuys;
    int preNumActions = state->numActions;
    int preCoins = state->coins;
    int preDeckCount = state->deckCount[player];
    int preDiscardCount = state->discardCount[player];

    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);

    int postHandCount = state->handCount[player];
    int postNumBuys = state->numBuys;
    int postNumActions = state->numActions;
    int postCoins = state->coins;
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];
    
    //see if smithy still in hand. it should not be
    int i;
    int smithyFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == smithy) {
            smithyFound = 1;
        }
    }

    //draws 3 cards but discards itself for hand size increase of 2
    if (preHandCount + 2 == postHandCount)
        printf("smithy handCount: PASSED\n");
    else
        printf("smithy handCount: FAILED\n");
    
    if (preNumBuys == postNumBuys)
        printf("smithy numBuys: PASSED\n");
    else
        printf("smithy numBuys: FAILED\n");

    if (preNumActions == postNumActions)
        printf("smithy numActions: PASSED\n");
    else
        printf("smithy numActions: FAILED\n");

    if (preCoins == postCoins)
        printf("smithy coins: PASSED\n");
    else
        printf("smithy coins: FAILED\n");

    if (preDeckCount - 3 == postDeckCount)
        printf("smithy deckCount: PASSED\n");
    else
        printf("smithy deckCount: FAILED\n");

    if (preDiscardCount + 1 == postDiscardCount)
        printf("smithy discardCount: PASSED\n");
    else
        printf("smithy discardCount: FAILED\n");

    if (topDiscardCard == smithy)
        printf("smithy topDiscardCard: PASSED\n");
    else
        printf("smithy topDiscardCard: FAILED\n"); 

    if (smithyFound == 0)
        printf("smithy smithyNotInHand: PASSED\n");
    else if (smithyFound == 1)
        printf("smithy smithyNotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

//test smithy if 2 cards in deck and 3 cards in discard
void testSmithyShortDeck(struct gameState* state, int handPos, int* bonus) {
    printf("testing smithy with < 3 cards in deck\n");   
    int player = state->whoseTurn;
    int preHandCount = state->handCount[player];
    int preNumBuys = state->numBuys;
    int preNumActions = state->numActions;
    int preCoins = state->coins;

    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);

    int postHandCount = state->handCount[player];
    int postNumBuys = state->numBuys;
    int postNumActions = state->numActions;
    int postCoins = state->coins;
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];
    
    //see if smithy still in hand. it should not be
    int i;
    int smithyFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == smithy) {
            smithyFound = 1;
        }
    }

    //draws 3 cards but discards itself for hand size increase of 2
    if (preHandCount + 2 == postHandCount)
        printf("smithy handCount: PASSED\n");
    else
        printf("smithy handCount: FAILED\n");
    
    if (preNumBuys == postNumBuys)
        printf("smithy numBuys: PASSED\n");
    else
        printf("smithy numBuys: FAILED\n");

    if (preNumActions == postNumActions)
        printf("smithy numActions: PASSED\n");
    else
        printf("smithy numActions: FAILED\n");

    if (preCoins == postCoins)
        printf("smithy coins: PASSED\n");
    else
        printf("smithy coins: FAILED\n");

    //should be 2 in deck.  2 before draws to 0, then 3 from discard added to deck and 1 more drawn.
    if (2 == postDeckCount)
        printf("smithy deckCount: PASSED\n");
    else
        printf("smithy deckCount: FAILED\n");

    //dicard will empty into deck during draw and then should just be smithy in discard
    if (1 == postDiscardCount)
        printf("smithy discardCount: PASSED\n");
    else
        printf("smithy discardCount: FAILED\n");

    if (topDiscardCard == smithy)
        printf("smithy topDiscardCard: PASSED\n");
    else
        printf("smithy topDiscardCard: FAILED\n"); 

    if (smithyFound == 0)
        printf("smithy smithyNotInHand: PASSED\n");
    else if (smithyFound == 1)
        printf("smithy smithyNotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

//test smithy with 1 card in discard and 1 card in deck
void testSmithyNotEnough(struct gameState* state, int handPos, int* bonus) {
    printf("testing smithy with 1 card in deck and 1 card in discard\n");
    int player = state->whoseTurn;
    int preHandCount = state->handCount[player];
    int preNumBuys = state->numBuys;
    int preNumActions = state->numActions;
    int preCoins = state->coins;

    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);

    int postHandCount = state->handCount[player];
    int postNumBuys = state->numBuys;
    int postNumActions = state->numActions;
    int postCoins = state->coins;
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];
    
    //see if smithy still in hand. it should not be
    int i;
    int smithyFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == smithy) {
            smithyFound = 1;
        }
    }

    //should only draw 2 cards this time and discard itself
    if (preHandCount + 1 == postHandCount)
        printf("smithy handCount: PASSED\n");
    else
        printf("smithy handCount: FAILED\n");
    
    if (preNumBuys == postNumBuys)
        printf("smithy numBuys: PASSED\n");
    else
        printf("smithy numBuys: FAILED\n");

    if (preNumActions == postNumActions)
        printf("smithy numActions: PASSED\n");
    else
        printf("smithy numActions: FAILED\n");

    if (preCoins == postCoins)
        printf("smithy coins: PASSED\n");
    else
        printf("smithy coins: FAILED\n");

    //draw only card in deck.  shuffle only discard into deck and draw it.  out of cards.  none in deck
    if (0 == postDeckCount)
        printf("smithy deckCount: PASSED\n");
    else
        printf("smithy deckCount: FAILED\n");

    //dicard will empty into deck during draw and then should just be smithy in discard
    if (1 == postDiscardCount)
        printf("smithy discardCount: PASSED\n");
    else
        printf("smithy discardCount: FAILED\n");

    if (topDiscardCard == smithy)
        printf("smithy topDiscardCard: PASSED\n");
    else
        printf("smithy topDiscardCard: FAILED\n"); 

    if (smithyFound == 0)
        printf("smithy smithyNotInHand: PASSED\n");
    else if (smithyFound == 1)
        printf("smithy smithyNotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

int main(int argc, char** argv) {
    struct gameState state;
    int numberOfPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);

    //play smithy
    setState(&state);
    int bonus = 0;
    testSmithyNormal(&state, state.handCount[state.whoseTurn] - 1, &bonus);

    //play smithy with less than 3 cards in deck, but sufficient cards in discard - should work
    initializeGame(numberOfPlayers, k, 1, &state);
    int player = state.whoseTurn;
    bonus = 0;
    state.deckCount[player]--;
    state.discard[player][state.discardCount[player]] = state.deck[player][state.deckCount[player]];
    state.discardCount[player]++;
    state.deckCount[player]--;
    state.discard[player][state.discardCount[player]] = state.deck[player][state.deckCount[player]];
    state.discardCount[player]++;
    state.deckCount[player]--;
    state.discard[player][state.discardCount[player]] = state.deck[player][state.deckCount[player]];
    state.discardCount[player]++;
    assert(state.deckCount[player] == 2 && state.discardCount[player] == 3);
    setState(&state);
    testSmithyShortDeck(&state, state.handCount[state.whoseTurn] - 1, &bonus);

    //test smithy with 2 cards total in deck and discard - should only draw 2 cards
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
    bonus = 0;
    state.deckCount[player] = 1;
    state.discardCount[player] = 1;
    state.discard[player][0] = copper;
    setState(&state);
    testSmithyNotEnough(&state, state.handCount[state.whoseTurn] - 1, &bonus);

    return 0;
}