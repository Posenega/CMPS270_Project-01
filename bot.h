#ifndef BOT_H
#define BOT_H

char *makeMoveLevel1(char **spellsList, int numSpells);

char *makeMoveLevel2(char **spellsList, int numSpells, char lastLetter, char **usedSpells);

#endif // !BOT_H