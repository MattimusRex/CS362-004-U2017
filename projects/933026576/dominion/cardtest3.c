//Unit Test suite for Village card
//Village grants +2 actions and +1 draw


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//set hand to known cards
void setHand(struct gameState* state, int player) {
    int i;
    state->handCount[player] = 5;
    for (i = 0; i < state->handCount[player] - 1; i++) {
        state->hand[player][i] = estate;
    }
    state->hand[player][state->handCount[player] - 1] = village;
    return;
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
    // if (pre->numActions != post->numActions)
    //     return -8;
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
    if (pre->playedCardCount != post->playedCardCount - 1) {
        return -15;
    }
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

//should draw 1 card and increase numAction by 2 (from 1 to 3).
//discard should increase by 1 from discarding the played card, but discard currently broken
void testVillageNormal(struct gameState* state, int player, int handPos) {
    printf("testVillageNormal test\n");
    int preHandCount = state->handCount[player];
    int preNumActions = state->numActions;
    int preDeckCount = state->deckCount[player];
    int preDiscardCount = state->discardCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(village, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postNumActions = state->numActions;
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if village still in hand. it should not be
    int i;
    int villageFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == village) {
            villageFound = 1;
        }
    }

    
    //draws 1 cards but discards itself for hand size increase of 0
    if (preHandCount == postHandCount)
        printf("handCount: PASSED\n");
    else
        printf("handCount: FAILED\n");

    //increased number of actions by 2
    if (preNumActions + 2 == postNumActions)
        printf("numActions: PASSED\n");
    else
        printf("numActions: FAILED\n");

    //deck should be 1 smaller from drawing 1 card
    if (preDeckCount - 1 == postDeckCount)
        printf("deckCount: PASSED\n");
    else
        printf("deckCount: FAILED\n");

    if (preDiscardCount + 1 == postDiscardCount)
        printf("discardCount: PASSED\n");
    else
        printf("discardCount: FAILED\n");

    if (topDiscardCard == village)
        printf("topDiscardCard: PASSED\n");
    else
        printf("topDiscardCard: FAILED\n"); 

    if (villageFound == 0)
        printf("NotInHand: PASSED\n");
    else if (villageFound == 1)
        printf("NotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

//should draw 1 card and increase numAction by 2 (from 1 to 3).
//discardCount should go from 2 to 1 (shuffle discard into deck and then add village to discard)
void testVillageNoDeck(struct gameState* state, int player, int handPos) {
    printf("testVillageNoDeck test\n");
    int preHandCount = state->handCount[player];
    int preNumActions = state->numActions;

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(village, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postNumActions = state->numActions;
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if village still in hand. it should not be
    //smithy should be in hand after draw, but not before
    int i;
    int villageFound = 0;
    int smithyFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == village) {
            villageFound = 1;
        }
        if (state->hand[player][i] == smithy) {
            smithyFound = 1;
        }
    }

    
    //draws 1 cards but discards itself for hand size increase of 0
    if (preHandCount == postHandCount)
        printf("handCount: PASSED\n");
    else
        printf("handCount: FAILED\n");

    //increased number of actions by 2
    if (preNumActions + 2 == postNumActions)
        printf("numActions: PASSED\n");
    else
        printf("numActions: FAILED\n");

    //deck should be 1 because it was empty and discard(2) shuffled into deck, then 1 card drawn
    if (1 == postDeckCount)
        printf("deckCount: PASSED\n");
    else
        printf("deckCount: FAILED\n");

    //should be 1 from discard being emptied then village added
    if (1 == postDiscardCount)
        printf("discardCount: PASSED\n");
    else
        printf("discardCount: FAILED\n");

    if (topDiscardCard == village)
        printf("topDiscardCard: PASSED\n");
    else
        printf("topDiscardCard: FAILED\n"); 

    if (villageFound == 0)
        printf("NotInHand: PASSED\n");
    else if (villageFound == 1)
        printf("NotInHand: FAILED\n");

    if (smithyFound == 1)
        printf("smithyDrawn: PASSED\n");
    else if (smithyFound == 0)
        printf("smithyDrawn: FAILED\n");       
    
    printf("\n");
    return;
}

//should draw 0 cards (none available) and increase numAction by 2 (from 1 to 3).
//discardCount should go from 0 to 1 (village)
void testVillageNoDeckDiscard(struct gameState* state, int player, int handPos) {
    printf("testVillageNoDeckDiscard test\n");
    int preHandCount = state->handCount[player];
    int preNumActions = state->numActions;

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(village, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postNumActions = state->numActions;
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if village still in hand. it should not be
    int i;
    int villageFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == village) {
            villageFound = 1;
        }
    }

    
    //draws 0 cards but discards itself for hand size increase of -1
    if (preHandCount - 1 == postHandCount)
        printf("handCount: PASSED\n");
    else
        printf("handCount: FAILED\n");

    //increased number of actions by 2
    if (preNumActions + 2 == postNumActions)
        printf("numActions: PASSED\n");
    else
        printf("numActions: FAILED\n");

    //deck should be 0 because it was empty
    if (0 == postDeckCount)
        printf("deckCount: PASSED\n");
    else
        printf("deckCount: FAILED\n");

    //should be 1 from discard being empty then village added
    if (1 == postDiscardCount)
        printf("discardCount: PASSED\n");
    else
        printf("discardCount: FAILED\n");

    if (topDiscardCard == village)
        printf("topDiscardCard: PASSED\n");
    else
        printf("topDiscardCard: FAILED\n"); 

    if (villageFound == 0)
        printf("NotInHand: PASSED\n");
    else if (villageFound == 1)
        printf("NotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

int main(int argc, char** argv) {
    struct gameState state;
    int numberOfPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);
    int player = state.whoseTurn;

    //prep for first test.  5 card hand and 5 card deck.  1 action
    state.numActions = 1;
    setHand(&state, player);
    //state, player, handPos
    testVillageNormal(&state, player, state.handCount[player] - 1);

    //second test - no cards in deck, but cards in discard pile
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
    state.numActions = 1;
    setHand(&state, player);
    state.deckCount[player] = 0;
    state.discardCount[player] = 2;
    state.discard[player][0] = copper;
    state.discard[player][1] = smithy;
    testVillageNoDeck(&state, player, state.handCount[player] - 1);

    //third test - no cards in deck or discard pile.  
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
    state.numActions = 1;
    setHand(&state, player);
    state.deckCount[player] = 0;
    state.discardCount[player] = 0;
    testVillageNoDeckDiscard(&state, player, state.handCount[player] - 1);    


    return 0;
}