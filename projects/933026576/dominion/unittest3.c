//Unit Test suite for updateCoins()

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//tests 5 copper
void updateCoinsAllCopper(int player, struct gameState* state, int coins) {
    state->coins = 0;
    updateCoins(player, state, 0);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsAllCopper: PASSED\n");
    else {
        printf("updateCoinsAllCopper: FAILED\n");
    }
    printf("\n");
    return;
}

//tests 500 gold
void updateCoinsMaxHandGold(int player, struct gameState* state, int coins) {
    state->coins = 0;
    updateCoins(player, state, 0);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsMaxHandGold: PASSED\n");
    else {
        printf("updateCoinsMaxHandGold: FAILED\n");
    }
    printf("\n");
    return;
}

//tests 2 gold, 2 silver, 2 copper
void updateCoins2OfEach(int player, struct gameState* state, int coins) {
    state->coins = 0;    
    updateCoins(player, state, 0);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoins2OfEach: PASSED\n");
    else {
        printf("updateCoins2OfEach: FAILED\n");
    }
    printf("\n");
    return;
}

//tests hand size of 0
void updateCoinsEmptyHand(int player, struct gameState* state, int coins) {
    state->coins = 0;    
    updateCoins(player, state, 0);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsEmptyHand: PASSED\n");
    else {
        printf("updateCoinsEmptyHand: FAILED\n");
    }
    printf("\n");
    return;
}

//tests 1 copper, 1 silver, 3 villages
void updateCoinsNormalHand(int player, struct gameState* state, int coins) {
    state->coins = 0;    
    updateCoins(player, state, 0);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsNormalHand: PASSED\n");
    else {
        printf("updateCoinsNormalHand: FAILED\n");
    }
    printf("\n");
    return;
}

//tests same as above but with a bonus of 5
void updateCoinsNormalHandBonus(int player, struct gameState* state, int coins, int bonus) {
    state->coins = 0;   
    updateCoins(player, state, bonus);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsNormalHandBonus: PASSED\n");
    else {
        printf("updateCoinsNormalHandBonus: FAILED\n");
    }
    printf("\n");
    return;
}

//tests hand size of 0 but with a bonus of 5
void updateCoinsEmptyHandBonus(int player, struct gameState* state, int coins, int bonus) {
    state->coins = 0;    
    updateCoins(player, state, bonus);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsEmptyHandBonus: PASSED\n");
    else {
        printf("updateCoinsEmptyHandBonus: FAILED\n");
    }
    printf("\n");
    return;
}

//tests 5 card hand with no treasure cards
void updateCoinsNoTreasure(int player, struct gameState* state, int coins) {
    state->coins = 0;    
    updateCoins(player, state, 0);
    int postCoins = state->coins;
    if (coins == postCoins)
        printf("updateCoinsNoTreasure: PASSED\n");
    else {
        printf("updateCoinsNoTreasure: FAILED\n");
    }
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
    //game starts player with 5 card hand.  Change to be 5 copper.
    int i;
    for (i = 0; i < state.handCount[player]; i++) {
        state.hand[player][i] = copper;
    }
    updateCoinsAllCopper(player, &state, 5);

    //test max hand of all gold to check for largest amount.  should be larger than anyone could achieve.
    state.handCount[player] = MAX_HAND;
    for (i = 0; i < state.handCount[player]; i++) {
        state.hand[player][i] = gold;
    }
    updateCoinsMaxHandGold(player, &state, 1500);

    //test hand of all 3 types of coin
    state.handCount[player] = 6;
    state.hand[player][0] = gold;
    state.hand[player][1] = gold;
    state.hand[player][2] = copper;
    state.hand[player][3] = copper;
    state.hand[player][4] = silver;
    state.hand[player][5] = silver;
    updateCoins2OfEach(player, &state, 12);

    //empty hand
    state.handCount[player] = 0;
    updateCoinsEmptyHand(player, &state, 0);

    //hand with coin and non coin cards
    state.handCount[player] = 5;
    state.hand[player][0] = village;
    state.hand[player][1] = village;
    state.hand[player][2] = copper;
    state.hand[player][3] = village;
    state.hand[player][4] = silver;
    updateCoinsNormalHand(player, &state, 3);

    //normal hand with bonus
    int bonus = 5;
    updateCoinsNormalHandBonus(player, &state, 8, bonus);

    //empty hand with bonus
    state.handCount[player] = 0;
    bonus = 5;
    updateCoinsEmptyHandBonus(player, &state, 5, bonus);

    //hand with no treasure cards
    bonus = 0;
    state.handCount[player] = 5;
    state.hand[player][0] = village;
    state.hand[player][1] = village;
    state.hand[player][2] = village;
    state.hand[player][3] = village;
    state.hand[player][4] = village;
    updateCoinsNoTreasure(player, &state, 0);

    return 0;
}