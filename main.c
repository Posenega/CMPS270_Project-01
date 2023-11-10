#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Local Dependincies

#include "spellsHandler.h"
#include "spellsHandler.c"
#include "game.h"
#include "game.c"
#include "bot.h"
#include "bot.c"

#define MAX_SPELL_LENGTH 100

int main()
{
    // Loading Spells from file
    int numSpells;
    char **spellsList = loadSpellsFromFile("/Users/theokhalil/AUB/AUB/3rd Sem/CMPS 270/projects/CMPS270_Project-01/spells.txt", &numSpells, MAX_SPELL_LENGTH);

    if (spellsList == NULL)
    {
        printf("Failed to load the spell list.\n");
        return 1;
    }

    // // Getting user input

    char player[10];

    printf("Player 1, enter your name: ");
    scanf("%s", player);

    printRule(player);
    int difficulty;
    printf("Coose the level (1, 2 or 3) of difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hardcore\n");
    printf("Enter your choice: ");
    scanf("%d", &difficulty);

    // // Display the spell list
    displayTable(spellsList, numSpells);

    // // DETERMINE WHO STARTS

    // char *currentPlayer = getCurrentPlayer();
    char *currentPlayer = "Bot";

    printf("%s starts.\n", currentPlayer);
    int rounds = 0;
    char lastLetter = ' ';
    char lastSpell[MAX_SPELL_LENGTH] = "";
    char **enteredSpells = NULL;
    enteredSpells = (char **)malloc(sizeof(char *) * numSpells);

    // // GAME STARTS
    while (1)
    {
        printf("%s, enter a spell: ", currentPlayer);
        char spell[MAX_SPELL_LENGTH];
        if (strcmp(currentPlayer, "You") == 0)
        {
            scanf("%s", spell);
        }
        else
        {
            // switch (difficulty)
            // {
            // case 1:
            //     strcpy(spell, makeMoveLevel1(spellsList, numSpells));
            //     break;
            // case 2:
            //     strcpy(spell, makeMoveLevel2(spellsList, numSpells, lastLetter, enteredSpells));
            //     break;
            // default:
            //     strcpy(spell, makeMoveLevel1(spellsList, numSpells));
            //     break;
            // }
            strcpy(spell, findBestMove(enteredSpells, lastSpell, numSpells));
        }

        if (rounds != 0 && spell[0] != lastLetter)
        {
            printf("Spell does not start with the last letter of the previous word.\n");
            announceTheLost(currentPlayer);
            break;
        }

        if (!isSpellInList(spell, spellsList, numSpells))
        {
            printf("Spell not found in the list.\n");
            announceTheLost(currentPlayer);
            break;
        }

        if (isSpellInList(spell, enteredSpells, numSpells))
        {
            printf("Spell was already used before.\n");
            announceTheLost(currentPlayer);
            break;
        }

        lastLetter = spell[strlen(spell) - 1];
        strcpy(lastSpell, spell);

        shiftPlayer(&currentPlayer);

        // Enter the spell in enteredSpells
        enteredSpells[rounds] = (char *)malloc(strlen(spell) + 1);
        strcpy(enteredSpells[rounds], spell);
        rounds++;
    }

    // Free memory allocated for spellsList and enteredSpells
    for (int i = 0; i < numSpells; i++)
    {
        free(spellsList[i]);
    }
    free(spellsList);

    for (int i = 0; i < rounds; i++)
    {
        free(enteredSpells[i]);
    }
    free(enteredSpells);

    return 0;
}
