#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "Graph.h"
#include "spellsHandler.h"
#define MINUS_INFINITY_SCORE -1000000
#define INFINITY_SCORE 1000000

// requires: List of the spell to be picked from and the number of spells in the list
// effects: returns a random spell from the list
char *makeMoveLevel1(char **spellsList, int numSpells);
// Testing:
// 1. bot does the first move
// 2. bot does a move after the player have done a move

// requires: List of the spell to be picked from, the number of spells in the list, the last letter of the last spell played and the list of spells already played
// effects: returns a random spell from the list that starts with the last letter of the last spell played and has not been played before
char *makeMoveLevel2(char **spellsList, int numSpells, char lastLetter, char **usedSpells);
// Testing:
// 1. bot does the first move
// 2. bot does a move after the player have done a move

// requires: Graph of the game, a valid vetrtex index
// effects: returns the number of unvisited neighbors of the vertex
int countUnvisitedNeighbors(Graph *gameGraph, int vertexIndex);

// requires: Graph of the game, the last spell played
// effects: returns the weigth of chosing a specific spell
int evaluate(Graph *gameGraph, char *lastSpell);

// requires: graph of the game, spell, the depth to explore, alpha value for the alpha beta prunning, beta value for the alpha beta prunning, boolean to check if it is the maximizing player, the list of spells already played and the number of spells already played
// effects: returns the score of the potential state of the game
int minimax(Graph *gameGraph, char *lastSpell, int depth, int alpha, int beta, bool isMaximizing, char **usedSpells, int numUsedSpells);

// requires: Graph of the game, the last spell played and the list of spells already played and the number of spells already played
// effects: returns the most adequate spell to play based on the minimax algorithm that will be used to play against the player
char *makeMoveLevel3(Graph *gameGraph, char *lastSpell, char **usedSpells, int numUsedSpells);
// Testing:
// 1. bot does the first move
// 2. bot does a move after the player have done a move
// 3. winning move
// 4. blocking oponent's winning move

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

int countUnvisitedNeighbors(Graph *gameGraph, int vertexIndex)
{
    int count = 0;
    gameGraph->visited[vertexIndex] = 1; // Mark the current vertex as visited

    // Iterate through neighbors
    Node *current = gameGraph->adjLists[vertexIndex];
    while (current != NULL)
    {
        int neighborIndex = getVertexIndex(gameGraph, current->vertex);
        if (!gameGraph->visited[neighborIndex])
        {
            count += 1; // Count unvisited neighbors
            count += countUnvisitedNeighbors(gameGraph, neighborIndex);
        }
        current = current->next;
    }

    return count;
}

int evaluate(Graph *gameGraph, char *lastSpell)
{
    int totalWeight = 0;
    for (int i = 0; i < gameGraph->numVertices; ++i)
    {
        gameGraph->visited[i] = 0; // Initialize visited array
    }

    // Find the index of the last spell in the graph
    int lastSpellIndex = getVertexIndex(gameGraph, lastSpell);

    // Criteria: Unvisited neighbors of Spells
    totalWeight += countUnvisitedNeighbors(gameGraph, lastSpellIndex);

    return totalWeight;
}

int minimax(Graph *gameGraph, char *lastSpell, int depth, int alpha, int beta, bool isMaximizing, char **usedSpells, int numUsedSpells)
{
    if (depth == 0)
    {
        return evaluate(gameGraph, lastSpell);
    }
    if (isMaximizing)
    {
        int maxEval = MINUS_INFINITY_SCORE;

        for (int i = 0; i < gameGraph->numVertices; i++)
        {
            char *currentSpell = gameGraph->vertexNames[i];

            if (!isSpellInList(currentSpell, usedSpells, numUsedSpells) && lastSpell[strlen(lastSpell) - 1] == currentSpell[0])
            {
                usedSpells[numUsedSpells++] = currentSpell;

                int eval = minimax(gameGraph, currentSpell, depth, alpha, beta, false, usedSpells, numUsedSpells);

                usedSpells[--numUsedSpells] = NULL;

                alpha = (eval > alpha) ? eval : alpha;
                maxEval = (eval > maxEval) ? eval : maxEval;

                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = INFINITY_SCORE;

        for (int i = 0; i < gameGraph->numVertices; ++i)
        {
            char *currentSpell = gameGraph->vertexNames[i];

            if (!isSpellInList(currentSpell, usedSpells, numUsedSpells) && lastSpell[strlen(lastSpell) - 1] == currentSpell[0])
            {
                usedSpells[numUsedSpells++] = currentSpell;

                int eval = minimax(gameGraph, currentSpell, depth - 1, alpha, beta, true, usedSpells, numUsedSpells);

                usedSpells[--numUsedSpells] = NULL;
                beta = (eval < beta) ? eval : beta;
                minEval = (eval < minEval) ? eval : minEval;

                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return minEval;
    }
}

char *makeMoveLevel3(Graph *gameGraph, char *lastSpell, char **usedSpells, int numUsedSpells)
{

    int bestScore = MINUS_INFINITY_SCORE;
    char *bestMove = NULL;
    char *currentSpell = NULL;

    if (lastSpell[0] == '\0')
    {
        return makeMoveLevel1(gameGraph->vertexNames, gameGraph->numVertices);
    }

    for (int i = 0; i < gameGraph->numVertices; i++)
    {
        currentSpell = gameGraph->vertexNames[i];

        if (!isSpellInList(currentSpell, usedSpells, numUsedSpells) && lastSpell[strlen(lastSpell) - 1] == currentSpell[0])
        {
            usedSpells[numUsedSpells++] = currentSpell;

            int score = minimax(gameGraph, lastSpell, 3, MINUS_INFINITY_SCORE, INFINITY_SCORE, false, usedSpells, numUsedSpells);

            usedSpells[--numUsedSpells] = NULL;

            if (score >= bestScore)
            {
                bestScore = score;
                bestMove = currentSpell;
            }
        }
    }
    if (bestMove == NULL)
    {
        return makeMoveLevel1(gameGraph->vertexNames, gameGraph->numVertices);
    }

    return bestMove;
}