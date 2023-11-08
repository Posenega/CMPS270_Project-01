#include <stdlib.h>
#include <time.h>
#include "spellsHandler.h"

char *makeMoveLevel1(char **spellsList, int numSpells)
{
    srand(time(NULL));
    int randomIndex = rand() % numSpells;
    char *spell = spellsList[randomIndex];
    return spell;
}

char *makeMoveLevel2(char **spellsList, int numSpells, char lastLetter, char **usedSpells)
{

    srand(time(NULL));
    int randomIndex = rand() % numSpells;
    char *spell = spellsList[randomIndex];
    int count = 0;
    while (spell[0] != lastLetter || isSpellInList(spell, usedSpells, numSpells))
    {
        randomIndex = rand() % numSpells;
        spell = spellsList[randomIndex];
        if (count == numSpells)
        {
            break;
        }
        count++;
    }
    return spell;
}