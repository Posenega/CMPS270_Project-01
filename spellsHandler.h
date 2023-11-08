#ifndef SPELLS_HANDLER_H
#define SPELLS_HANDLER_H

char **loadSpellsFromFile(const char *filePath, int *numSpells, int spell_length);

void displayTable(char **spellsList, int numSpells);

int isSpellInList(const char *spell, char **spellsList, int numSpells);

#endif // !SPELLS_HANDLER_H