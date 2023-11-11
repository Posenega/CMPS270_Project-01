#ifndef BOT_H
#define BOT_H

#include "Graph.h"
char *makeMoveLevel1(char **spellsList, int numSpells);

char *makeMoveLevel2(char **spellsList, int numSpells, char lastLetter, char **usedSpells);

int countNonVisitedNeighbors(Graph *gameGraph, int vertexIndex, int *visited);

char *makeMoveLevel3(Graph *gameGraph, char *lastSpell, char **usedSpells, int numUsedSpells);

#endif // !BOT_H