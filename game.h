#ifndef GAME_H
#define GAME_H

void printRule(char player1[]);

int coinToss();

char *getCurrentPlayer();

void announceTheLost(char currentPlayer[]);

void shiftPlayer(char **currentPlayer);

#endif // GAME_H