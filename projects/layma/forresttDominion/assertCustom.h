//
// Created by Tyler on 7/14/2017.
//

#ifndef DOMINION_ASSERTCUSTOM_H
#define DOMINION_ASSERTCUSTOM_H

void assertCustom(int boolean, char * message);

void assertGameState(int player, struct gameState * oldG, struct gameState * newG);

#endif //DOMINION_ASSERTCUSTOM_H
