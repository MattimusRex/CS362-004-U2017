//Unit Test suite for buyCard()

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


/*
When card is purchased:
coins should be reduced by correct amount
card supply should be reduced by 1
The purchased card should be added to the top of the discard pile
players buy count should be reduced by 1
*/
void buyCardTestVillage(struct gameState* state, int card, int cardCost) {
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];

    buyCard(card, state);

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];
    int topDiscardCard = state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1];

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
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];

    buyCard(card, state);

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];

    if (preBuyCoins == postBuyCoins) 
        printf("buyCardInsuffcientCoins coins: PASSED\n");
    else 
        printf("buyCardInsuffcientCoins coins: FAILED\n");

    if (preBuyNumBuys == postBuyNumBuys) 
        printf("buyCardInsuffcientCoins numBuys: PASSED\n");
    else 
        printf("buyCardInsuffcientCoins numBuys: FAILED\n");

    if (preBuySupplyCount == postBuySupplyCount)
        printf("buyCardInsuffcientCoins supplyCount: PASSED\n");
    else
        printf("buyCardInsuffcientCoins supplyCount: FAILED\n");
    
    if (preBuyDiscardCount == postBuyDiscardCount)
        printf("buyCardInsuffcientCoins discardCount: PASSED\n");
    else
        printf("buyCardInsuffcientCoins discardCount: FAILED\n");
    
    printf("\n");
    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardSupplyEmpty(struct gameState* state, int card) {
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];

    buyCard(card, state);

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];

    if (preBuyCoins == postBuyCoins) 
        printf("buyCardSupplyEmpty coins: PASSED\n");
    else 
        printf("buyCardSupplyEmpty coins: FAILED\n");

    if (preBuyNumBuys == postBuyNumBuys) 
        printf("buyCardSupplyEmpty numBuys: PASSED\n");
    else 
        printf("buyCardSupplyEmpty numBuys: FAILED\n");

    if (preBuySupplyCount == postBuySupplyCount)
        printf("buyCardSupplyEmpty supplyCount: PASSED\n");
    else
        printf("buyCardSupplyEmpty supplyCount: FAILED\n");
    
    if (preBuyDiscardCount == postBuyDiscardCount)
        printf("buyCardSupplyEmpty discardCount: PASSED\n");
    else
        printf("buyCardSupplyEmpty discardCount: FAILED\n");
    
    printf("\n");
    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardNotInGame(struct gameState* state, int card) {
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];

    buyCard(card, state);

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];

    if (preBuyCoins == postBuyCoins) 
        printf("buyCardNotInGame coins: PASSED\n");
    else 
        printf("buyCardNotInGame coins: FAILED\n");

    if (preBuyNumBuys == postBuyNumBuys) 
        printf("buyCardNotInGame numBuys: PASSED\n");
    else 
        printf("buyCardNotInGame numBuys: FAILED\n");

    if (preBuySupplyCount == postBuySupplyCount)
        printf("buyCardNotInGame supplyCount: PASSED\n");
    else
        printf("buyCardNotInGame supplyCount: FAILED\n");
    
    if (preBuyDiscardCount == postBuyDiscardCount)
        printf("buyCardNotInGame discardCount: PASSED\n");
    else
        printf("buyCardNotInGame discardCount: FAILED\n");
    
    printf("\n");
    return;
}

//buyCard should return -1 and none of the items should be changed.  
void buyCardNoBuys(struct gameState* state, int card) {
    //pre buy stats
    int preBuyCoins = state->coins;
    int preBuyNumBuys = state->numBuys;
    int preBuySupplyCount = state->supplyCount[card];
    int preBuyDiscardCount = state->discardCount[state->whoseTurn];

    buyCard(card, state);

    //compare after buy
    int postBuyCoins = state->coins;
    int postBuyNumBuys = state->numBuys;
    int postBuySupplyCount = state->supplyCount[card];
    int postBuyDiscardCount = state->discardCount[state->whoseTurn];

    if (preBuyCoins == postBuyCoins) 
        printf("buyCardNoBuys coins: PASSED\n");
    else 
        printf("buyCardNoBuys coins: FAILED\n");

    if (preBuyNumBuys == postBuyNumBuys) 
        printf("buyCardNoBuys numBuys: PASSED\n");
    else 
        printf("buyCardNoBuys numBuys: FAILED\n");

    if (preBuySupplyCount == postBuySupplyCount)
        printf("buyCardNoBuys supplyCount: PASSED\n");
    else
        printf("buyCardNoBuys supplyCount: FAILED\n");
    
    if (preBuyDiscardCount == postBuyDiscardCount)
        printf("buyCardNoBuys discardCount: PASSED\n");
    else
        printf("buyCardNoBuys discardCount: FAILED\n");
    
    printf("\n");
    return;
}

//sets player ready to successfully buy cards
void setState(struct gameState* state) {
    state->coins = 10;
    state->numBuys = 10;
}

//initialize game for testing with 4 people
int main(int argc, char** argv) {
    struct gameState state;
    int numberOfPlayers = 4;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numberOfPlayers, k, 1, &state);

    //test for successful card purchase of village
    setState(&state);
    int cardCost = 3;
    buyCardTestVillage(&state, village, cardCost);

    //test for buying village with insufficient coins, village needs 3 coins
    setState(&state);
    state.coins = 2;
    buyCardInsufficientCoins(&state, village);

    //test for buying village with no villages left
    setState(&state);
    state.supplyCount[village] = 0;
    buyCardSupplyEmpty(&state, village);
    state.supplyCount[village] = 10;

    //test for buying card not in game. steward costs 3 and isn't in game
    setState(&state);
    buyCardNotInGame(&state, steward);

    //test for buy village without any buys left
    setState(&state);
    state.numBuys = 0;
    buyCardNoBuys(&state, village);

    //test for buy village with the exact amount of buys, coins, and supply required.
    state.coins = 3;
    state.numBuys = 1;
    state.supplyCount[village] = 1;
    cardCost  = 3;
    buyCardTestVillage(&state, village, cardCost);

    return 0;
}
