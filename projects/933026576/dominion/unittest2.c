//Unit Test suite for buyCard()

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

int checkState(struct gameState* pre, struct gameState* post) {
    if (pre->numPlayers != post->numPlayers)
        return -1;
    int i;
    for (i = 0; i < treasure_map + 1; i++) {
        if (i != village && pre->supplyCount[i] != post->supplyCount[i])
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
    if (pre->numActions != post->numActions)
        return -8;
    if (memcmp(pre->handCount, post->handCount, sizeof(pre->handCount)) != 0)
        return -9;
    if (memcmp(pre->hand, post->hand, sizeof(pre->hand)) != 0)
        return -10 ;
    if (memcmp(pre->deck, post->deck, sizeof(pre->deck)) != 0)
        return -11;
    if (memcmp(pre->deckCount, post->deckCount, sizeof(pre->deckCount)) != 0)
        return -12;
    if (memcmp(pre->handCount, post->handCount, sizeof(pre->handCount)) != 0)
        return -13;
    if (memcmp(pre->playedCards, post->playedCards, sizeof(pre->playedCards)) != 0)
        return -14;
    if (pre->playedCardCount != post->playedCardCount)
        return -15;
    for (i = 0; i < pre->numPlayers; i++) {
        if (i != pre->whoseTurn && memcmp(pre->discard[i], post->discard[i], sizeof(pre->discard[i])) != 0)
            return -16;
        if (i != pre->whoseTurn && pre->discardCount[i] != post->discardCount[i])
            return -17;
    }
    return 0;               
}


/*
When card is purchased:
coins should be reduced by correct amount
card supply should be reduced by 1
The purchased card should be added to the top of the discard pile
players buy count should be reduced by 1
phase should change to indicate change from buy to action.
*/
void buyCardTestVillage(struct gameState* state, int card, int cardCost) {
    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];
    int preBuyPhase = state->phase;

    buyCard(card, state);
    if (checkState(&pre, state) != 0) {
        printf("Incorrect state field altered: error: %d\n", checkState(&pre, state));
    }
    else {
        printf("State not altered in incorrect fields\n");
    }

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];
    int topDiscardCard = state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1];
    int postBuyPhase = state->phase;

    if (preBuyPhase == postBuyPhase) 
        printf("buyCardTestVillage phase: FAILED\n");
    else 
        printf("buyCardTestVillage phase: PASSED\n");        

    if (preBuyCoins - cardCost == postBuyCoins) 
        printf("buyCardTestVillage coins: PASSED\n");
    else 
        printf("buyCardTestVillage coins: FAILED\n");

    if (preBuyNumBuys - 1 == postBuyNumBuys) 
        printf("buyCardTestVillage numBuys: PASSED\n");
    else 
        printf("buyCardTestVillage numBuys: FAILED\n");

    if (preBuySupplyCount - 1 == postBuySupplyCount)
        printf("buyCardTestVillage supplyCount: PASSED\n");
    else
        printf("buyCardTestVillage supplyCount: FAILED\n");
    
    if (preBuyDiscardCount + 1 == postBuyDiscardCount)
        printf("buyCardTestVillage discardCount: PASSED\n");
    else
        printf("buyCardTestVillage discardCount: FAILED\n");
    
    if (topDiscardCard == card)
        printf("buyCardTestVillage discardedCard: PASSED\n");
    else
        printf("buyCardTestVillage discardedCard: FAILED\n");
    
    printf("\n");
    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardInsufficientCoins(struct gameState* state, int card) {
    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    buyCard(card, state);
    if (memcmp(&pre, state, sizeof(struct gameState)) == 0) {
        printf("buyCardInsufficientCoins: PASSED\n");
    }
    else
        printf("buyCardInsufficientCoins: FAILED\n");

    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardSupplyEmpty(struct gameState* state, int card) {
    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    buyCard(card, state);
    if (memcmp(&pre, state, sizeof(struct gameState)) == 0) {
        printf("buyCardSupplyEmpty: PASSED\n");
    }
    else
        printf("buyCardSupplyEmpty: FAILED\n");
    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardNotInGame(struct gameState* state, int card) {
    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    buyCard(card, state);
    if (memcmp(&pre, state, sizeof(struct gameState)) == 0) {
        printf("buyCardNotInGame: PASSED\n");
    }
    else
        printf("buyCardNotInGame: FAILED\n");
    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardNoBuys(struct gameState* state, int card) {
    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    buyCard(card, state);
    if (memcmp(&pre, state, sizeof(struct gameState)) == 0) {
        printf("buyCardNoBuys: PASSED\n");
    }
    else
        printf("buyCardNoBuys: FAILED\n");
    return;
}

//Should be same as normal buy village, but phase should not change because player still has buy left.  
void buyCard2Buys(struct gameState* state, int card, int cardCost) {
    struct gameState pre;
    memcpy(&pre, state, sizeof(struct gameState));
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];
    int preBuyPhase = state->phase;

    buyCard(card, state);
    if (checkState(&pre, state) != 0) {
        printf("Incorrect state field altered: error: %d\n", checkState(&pre, state));
    }
    else {
        printf("State not altered in incorrect fields\n");
    }

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];
    int topDiscardCard = state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1];
    int postBuyPhase = state->phase;

    if (preBuyPhase == postBuyPhase) 
        printf("buyCard2Buys phase: PASSED\n");
    else 
        printf("buyCard2Buys phase: FAILED\n");        

    if (preBuyCoins - cardCost == postBuyCoins) 
        printf("buyCard2Buys coins: PASSED\n");
    else 
        printf("buyCard2Buys coins: FAILED\n");

    if (preBuyNumBuys - 1 == postBuyNumBuys) 
        printf("buyCard2Buys numBuys: PASSED\n");
    else 
        printf("buyCard2Buys numBuys: FAILED\n");

    if (preBuySupplyCount - 1 == postBuySupplyCount)
        printf("buyCard2Buys supplyCount: PASSED\n");
    else
        printf("buyCard2Buys supplyCount: FAILED\n");
    
    if (preBuyDiscardCount + 1 == postBuyDiscardCount)
        printf("buyCard2Buys discardCount: PASSED\n");
    else
        printf("buyCard2Buys discardCount: FAILED\n");
    
    if (topDiscardCard == card)
        printf("buyCard2Buys discardedCard: PASSED\n");
    else
        printf("buyCard2Buys discardedCard: FAILED\n");
    
    printf("\n");
    return;
}

//sets player ready to successfully buy cards
void setState(struct gameState* state) {
    state->coins = 10;
    state->numBuys = 1;
}

//initialize game for testing with 4 people
int main(int argc, char** argv) {
    struct gameState state;
    int numberOfPlayers = 4;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);

    //test for successful card purchase of village
    initializeGame(numberOfPlayers, k, 1, &state);
    setState(&state);
    int cardCost = 3;
    buyCardTestVillage(&state, village, cardCost);

    //test for buying village with insufficient coins, village needs 3 coins
    initializeGame(numberOfPlayers, k, 1, &state);    
    setState(&state);
    state.coins = 2;
    buyCardInsufficientCoins(&state, village);

    //test for buying village with no villages left
    initializeGame(numberOfPlayers, k, 1, &state);    
    setState(&state);
    state.supplyCount[village] = 0;
    buyCardSupplyEmpty(&state, village);
    state.supplyCount[village] = 10;

    //test for buying card not in game. steward costs 3 and isn't in game
    initializeGame(numberOfPlayers, k, 1, &state);    
    setState(&state);
    buyCardNotInGame(&state, steward);

    //test for buy village without any buys left
    initializeGame(numberOfPlayers, k, 1, &state);    
    setState(&state);
    state.numBuys = 0;
    buyCardNoBuys(&state, village);

    //test for buy village with the exact amount of buys, coins, and supply required.
    initializeGame(numberOfPlayers, k, 1, &state);    
    state.coins = 3;
    state.numBuys = 1;
    state.supplyCount[village] = 1;
    cardCost  = 3;
    buyCardTestVillage(&state, village, cardCost);

    //test buying village with 2 buys
    initializeGame(numberOfPlayers, k, 1, &state);    
    setState(&state);
    state.numBuys = 2;
    buyCard2Buys(&state, village, cardCost);    

    return 0;
}
