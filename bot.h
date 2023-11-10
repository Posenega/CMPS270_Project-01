#ifndef BOT_H
#define BOT_H

char *makeMoveLevel1(char **spellsList, int numSpells);

char *makeMoveLevel2(char **spellsList, int numSpells, char lastLetter, char **usedSpells);

char *findBestMove(char *usedSpells[], char *prevSpell, int numSpells);

#endif // !BOT_H