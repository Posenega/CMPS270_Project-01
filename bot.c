#include <stdlib.h>
#include <string.h>
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

// Function to check if a spell is valid (not used before)
int isValidSpell(char *usedSpells[], int numUsedSpells, const char *spell)
{
    if (spell == NULL || usedSpells == NULL)
    {
        return 0;
    }
    for (int i = 0; i < numUsedSpells; ++i)
    {
        if (strcmp(usedSpells[i], spell) == 0)
        {
            return 0; // Spell is not valid
        }
    }
    return 1; // Spell is valid
}

// Function to check if a spell starts with the given character
int isValidNextSpell(const char *prevSpell, const char *spell)
{
    if (prevSpell == NULL || spell == NULL)
    {
        return 1; // First spell is always valid
    }
    return (prevSpell[strlen(prevSpell) - 1] == spell[0]);
}

// Utility function to evaluate the game state
int evaluate(char *usedSpells[], int numUsedSpells, int maximizingPlayer)
{
    // You can define your own evaluation function based on game state
    // For simplicity, this example just returns 1 if the bot wins and -1 if the player wins.
    return (numUsedSpells % 2 == 0 ? (maximizingPlayer ? 1 : -1) : (maximizingPlayer ? -1 : 1));
}

// Minimax function
int minimax(char *usedSpells[], int numUsedSpells, const char *prevSpell, int depth, int maximizingPlayer, int numSpells)
{
    // Terminal condition: game over or reached maximum depth
    if (numUsedSpells == numSpells || depth == 0)
    {
        return evaluate(usedSpells, numUsedSpells, maximizingPlayer);
    }

    // Initialize the best value based on the player's perspective
    int bestValue = (maximizingPlayer ? -1000 : 1000);

    // Iterate through all possible spells
    for (int i = 0; i < numSpells; ++i)
    {
        if (isValidNextSpell(prevSpell, usedSpells[i]) && isValidSpell(usedSpells, numUsedSpells, usedSpells[i]))
        {
            // Make the move
            usedSpells[numUsedSpells++] = usedSpells[i];

            // Recursively call minimax for the next level
            int value = minimax(usedSpells, numUsedSpells, usedSpells[i], depth - 1, !maximizingPlayer, numSpells);

            // Undo the move
            usedSpells[--numUsedSpells] = NULL;

            // Update the best value based on the player's perspective
            if ((maximizingPlayer && value > bestValue) || (!maximizingPlayer && value < bestValue))
            {
                bestValue = value;
            }
        }
    }

    return bestValue;
}

// Function to find the best move for the bot
char *findBestMove(char *usedSpells[], char *prevSpell, int numSpells)
{
    int numUsedSpells = sizeof(usedSpells) / sizeof(usedSpells[0]);
    int bestValue = -1000;
    const char *bestMove = NULL;

    // Iterate through all possible spells
    for (int i = 0; i < numSpells; ++i)
    {
        if (isValidNextSpell(prevSpell, usedSpells[i]) && isValidSpell(usedSpells, numUsedSpells, usedSpells[i]))
        {
            // Make the move
            usedSpells[numUsedSpells++] = usedSpells[i];

            // Recursively call minimax for the next level
            int moveValue = minimax(usedSpells, numUsedSpells, usedSpells[i], 2, 0, numSpells); // Adjust depth as needed

            // Undo the move
            usedSpells[--numUsedSpells] = NULL;

            // Update the best move
            if (moveValue > bestValue)
            {
                bestValue = moveValue;
                bestMove = usedSpells[i];
            }
        }
    }

    return bestMove;
}
