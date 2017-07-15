//Unit Test suite for Smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//readys player state for testing
void setState(struct gameState* state) {
    state->hand[state->whoseTurn][state->handCount[state->whoseTurn]] = smithy;
    state->handCount[state->whoseTurn]++;
}

int checkState(struct gameState* pre, struct gameState* post) {
    if (pre->numPlayers != post->numPlayers)
        return -1;
    int i;
    for (i = 0; i < treasure_map + 1; i++) {
        if (pre->supplyCount[i] != post->supplyCount[i])
            return -2;
    }
    if (memcmp(pre->embargoTokens, post->embargoTokens, sizeof(pre->embargoTokens)) != 0){
        return -3;
    }
    if (pre->outpostPlayed != post->outpostPlayed)
        return -4;
    if (pre->outpostTurn != post->outpostTurn)
        return -5;
    if (pre->whoseTurn != post->whoseTurn)
        return -6;
    if (pre->phase != post->phase)
        return -7;
    if (pre->numActions != post->numActions)
        return -8;
    for (i = 0; i < pre->numPlayers; i++) {
        if (i != pre->whoseTurn && memcmp(pre->hand[i], post->hand[i], sizeof(pre->hand[i])) != 0)
            return -10;
        if (i != pre->whoseTurn && pre->handCount[i] != post->handCount[i])
            return -9;
        if (i != pre->whoseTurn && memcmp(pre->deck[i], post->deck[i], sizeof(pre->deck[i])) != 0)
            return -11;
        if (i != pre->whoseTurn && pre->deckCount[i] != post->deckCount[i])
            return -12;
    }
    // if (memcmp(pre->handCount, post->handCount, sizeof(pre->handCount)) != 0)
    //     return -9;
    // if (memcmp(pre->hand, post->hand, sizeof(pre->hand)) != 0)
    //     return -10 ;
    // if (memcmp(pre->deck, post->deck, sizeof(pre->deck)) != 0)
    //     return -11;
    // if (memcmp(pre->deckCount, post->deckCount, sizeof(pre->deckCount)) != 0)
    //     return -12;
    if (pre->playedCardCount != post->playedCardCount - 1)
        return -15;
    for (i = 0; i < pre->numPlayers; i++) {
        if (i != pre->whoseTurn && memcmp(pre->discard[i], post->discard[i], sizeof(pre->discard[i])) != 0)
            return -16;
        if (i != pre->whoseTurn && pre->discardCount[i] != post->discardCount[i])
            return -17;
    }
    if (pre->numBuys != post->numBuys)
        return -18;
    if (pre->coins != post->coins)
        return -19;
    return 0;               
}



//tests 1 call of Smithy card
//smithy is supposed to draw 3 cards.
//smithy should alter state in following ways for current player:
//handCount += 2 (discard smithy and draw 3)
//hand should gain top 3 cards of deck
//discardCount += 1
//top card of discard should be smithy
//numActions should decrease by 1
//deckCountshould be 3 less
//state should not change for anyone other than current player!
void testSmithyNormal(struct gameState* state, int handPos, int* bonus) {
    printf("testing smithy normal\n");
    int player = state->whoseTurn;
    int preHandCount = state->handCount[player];
    int preDeckCount = state->deckCount[player];
    int preDiscardCount = state->discardCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
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

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
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

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
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

    //draw only card in deck.  shuffle the only discard card into deck and draw it.  out of cards.  none in deck
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

//test smithy with 3 cards in deck.
void testSmithy3Deck(struct gameState* state, int handPos, int* bonus) {
    printf("testing testSmithy3Deck\n");
    int player = state->whoseTurn;
    int preHandCount = state->handCount[player];
    int preDeckCount = state->deckCount[player];
    int preDiscardCount = state->discardCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(smithy, -1, -1, -1, state, handPos, bonus);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
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

int main(int argc, char** argv) {
    struct gameState state;
    int numberOfPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);

    //play smithy with deck > 3
    setState(&state);
    int bonus = 0;
    testSmithyNormal(&state, state.handCount[state.whoseTurn] - 1, &bonus);

    //test smithy with deck == 3
    initializeGame(numberOfPlayers, k, 1, &state);
    int player = state.whoseTurn;
    bonus = 0;
    state.deckCount[player] = 3;
    setState(&state);
    testSmithy3Deck(&state, state.handCount[state.whoseTurn] - 1, &bonus);

    //play smithy with less than 3 cards in deck, but sufficient cards in discard - should work
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
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