//Unit Test suite for Adventurer card
//Adventurer draws cards until 2 treasure cards are drawn or it runs out of drawable cards
//Should change handCount (+2), hand, deckCount, deck, discardCount, and discard depending on state of deck
//Should not change coins, numBuys, numActions, or any other state


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
    state->hand[player][state->handCount[player] - 1] = adventurer;
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

//should draw 2 cards, both copper.  deck should have 3 cards left in it. hand should increase by 2.
//discard should increase by 1 from discarding the played card, but discard currently broken
void advDeckAllCopper(struct gameState* state, int player, int handPos) {
    printf("advDeckAllCopper test\n");
    int preHandCount = state->handCount[player];
    int preDeckCount = state->deckCount[player];
    int preDiscardCount = state->discardCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(adventurer, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if adventurer still in hand. it should not be
    int i;
    int advFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == adventurer) {
            advFound = 1;
        }
    }

    
    //draws 2 cards but discards itself for hand size increase of 1
    if (preHandCount + 1 == postHandCount)
        printf("adv handCount: PASSED\n");
    else {
        printf("adv handCount: FAILED\n");
        printf("preHandCount: %d, postHandCount: %d\n", preHandCount, postHandCount);
    }

    //should be reduced by 2 for this test
    if (preDeckCount - 2 == postDeckCount)
        printf("adv deckCount: PASSED\n");
    else
        printf("adv deckCount: FAILED\n");

    if (preDiscardCount + 1 == postDiscardCount)
        printf("adv discardCount: PASSED\n");
    else
        printf("adv discardCount: FAILED\n");

    if (topDiscardCard == adventurer)
        printf("adv topDiscardCard: PASSED\n");
    else
        printf("adv topDiscardCard: FAILED\n"); 

    if (advFound == 0)
        printf("adv NotInHand: PASSED\n");
    else if (advFound == 1)
        printf("adv NotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

//should draw all 5 cards in deck to get 1 silver and 1 gold.
//deck should be 0 after and discard should be 4 (adv + 3 villages)
void advDeck2TreasureAtBottom(struct gameState* state, int player, int handPos) {
    printf("advDeck2TreasureAtBottom test\n");
    int preHandCount = state->handCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(adventurer, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if adventurer still in hand. it should not be
    int i;
    int advFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == adventurer) {
            advFound = 1;
        }
    }

    
    //draws 2 cards but discards itself for hand size increase of 1
    if (preHandCount + 1 == postHandCount)
        printf("adv handCount: PASSED\n");
    else
        printf("adv handCount: FAILED\n");
        printf("preHandCount: %d, postHandCount: %d\n", preHandCount, postHandCount);
    //should be empty for this test
    if (0 == postDeckCount)
        printf("adv deckCount: PASSED\n");
    else
        printf("adv deckCount: FAILED\n");

    //discard empty when test started.
    if (4 == postDiscardCount)
        printf("adv discardCount: PASSED\n");
    else
        printf("adv discardCount: FAILED\n");

    if (topDiscardCard == adventurer)
        printf("adv topDiscardCard: PASSED\n");
    else
        printf("adv topDiscardCard: FAILED\n"); 

    if (advFound == 0)
        printf("adv NotInHand: PASSED\n");
    else if (advFound == 1)
        printf("adv NotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

//should draw all 3 cards in deck and 2 cards in discard to get 2 treasure.
//deck should be 0 after and discard should be 4 (adv + 3 village);
void advDeckAndDiscard(struct gameState* state, int player, int handPos) {
    printf("advDeckAndDiscard test\n");
    int preHandCount = state->handCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(adventurer, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if adventurer still in hand. it should not be
    int i;
    int advFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == adventurer) {
            advFound = 1;
        }
    }

    
    //draws 2 cards but discards itself for hand size increase of 1
    if (preHandCount + 1 == postHandCount)
        printf("adv handCount: PASSED\n");
    else
        printf("adv handCount: FAILED\n");
        printf("preHandCount: %d, postHandCount: %d\n", preHandCount, postHandCount);

    //should be empty for this test
    if (0 == postDeckCount)
        printf("adv deckCount: PASSED\n");
    else
        printf("adv deckCount: FAILED\n");

    //discard had 2 cards when started.  should have been shuffled into deck during drawing.
    if (4 == postDiscardCount)
        printf("adv discardCount: PASSED\n");
    else
        printf("adv discardCount: FAILED\n");

    if (topDiscardCard == adventurer)
        printf("adv topDiscardCard: PASSED\n");
    else
        printf("adv topDiscardCard: FAILED\n"); 

    if (advFound == 0)
        printf("adv NotInHand: PASSED\n");
    else if (advFound == 1)
        printf("adv NotInHand: FAILED\n");     
    
    printf("\n");
    return;
}

//should draw all 5 cards in deck and only get 1 treasure, thens top because there is no discard.
//deck should be 0 after and discard should be 5 (adv + 4 village);
void advDeckNotEnoughTreasure(struct gameState* state, int player, int handPos) {
    printf("advDeckNotEnoughTreasure test\n");
    int preHandCount = state->handCount[player];

    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    cardEffect(adventurer, -1, -1, -1, state, handPos, 0);
    if (checkState(&pre, state) != 0) {
        printf("Altered incorrect state field: %d\n", checkState(&pre, state));
    }

    int postHandCount = state->handCount[player];
    int postDeckCount = state->deckCount[player];
    int postDiscardCount = state->discardCount[player];
    int topDiscardCard = state->discard[player][state->discardCount[player] - 1];

    //see if adventurer still in hand. it should not be
    int i;
    int advFound = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == adventurer) {
            advFound = 1;
        }
    }

    
    //draws 1 cards but discards itself for hand size increase of 0
    if (preHandCount == postHandCount)
        printf("adv handCount: PASSED\n");
    else
        printf("adv handCount: FAILED\n");
        printf("preHandCount: %d, postHandCount: %d\n", preHandCount, postHandCount);

    //should be empty for this test
    if (0 == postDeckCount)
        printf("adv deckCount: PASSED\n");
    else
        printf("adv deckCount: FAILED\n");

    //discard had 0 cards when started.
    if (5 == postDiscardCount)
        printf("adv discardCount: PASSED\n");
    else
        printf("adv discardCount: FAILED\n");

    if (topDiscardCard == adventurer)
        printf("adv topDiscardCard: PASSED\n");
    else
        printf("adv topDiscardCard: FAILED\n"); 

    if (advFound == 0)
        printf("adv NotInHand: PASSED\n");
    else if (advFound == 1)
        printf("adv NotInHand: FAILED\n");     
    
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

    //prep deck for first test
    //put 5 cards in hand, including adventurer
    setHand(&state, player);
    //set deck 5 copper
    int i;
    for (i = 0; i < state.deckCount[player]; i++) {
        state.deck[player][i] = copper;
    }
    //first test is with a deck that should draw 2 treasure cards first and stop
    //state, player, handPos
    advDeckAllCopper(&state, player, state.handCount[player]-1);

    //reset for second test - this test has 3 village cards, then 2 treasure cards.  
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
    setHand(&state, player);
    state.deckCount[player] = 5;
    state.deck[player][0] = silver;
    state.deck[player][1] = gold;
    state.deck[player][2] = village;
    state.deck[player][3] = village;
    state.deck[player][4] = village;
    advDeck2TreasureAtBottom(&state, player, state.handCount[player]-1);

    //reset for third test - deck: 2 village, 1 copper  discard: 1 village, 1 copper
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
    setHand(&state, player);
    state.deckCount[player] = 3;
    state.deck[player][0] = copper;
    state.deck[player][1] = village;
    state.deck[player][2] = village;
    state.discardCount[player] = 2;
    state.discard[player][0] = copper;
    state.discard[player][1] = village;
    advDeckAndDiscard(&state, player, state.handCount[player]-1);

    //reset for fourth test - not 2 treasure cards available
    initializeGame(numberOfPlayers, k, 1, &state);
    player = state.whoseTurn;
    setHand(&state, player);
    state.deckCount[player] = 5;
    state.deck[player][0] = copper;
    state.deck[player][1] = village;
    state.deck[player][2] = village;
    state.deck[player][3] = village;
    state.deck[player][4] = village;
    advDeckNotEnoughTreasure(&state, player, state.handCount[player]-1);
    return 0;
}
