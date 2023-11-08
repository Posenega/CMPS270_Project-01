#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRule(char player1[])
{
    printf("Welcome %s to the game of WHO FINDS THE FIRST WORD BEFORE THE OTHER ONE GAME!\n", player1);
    printf("You will be following these rules to play the game:\n");
    printf("1. You will be given a list of words.\n");
    printf("2. We toss a coin to determine who starts.\n");
    printf("3. Choose a random word to start.\n");
    printf("4. Next player should find a spell exclusively from the set of provided words that starts with the last letter of the previous word and that was not used before.\n");
    printf("5. Repeat till the game ends.\n");
    printf("6. Games ends if one of the two conditions in rule 4 is broken.\n");
    printf("\n");
    printf("Good Luck & Have Fun.");
    printf("\n");
    printf("\n");
    printf("\n");
}

int coinToss()
{
    int a;
    srand(time(NULL));
    a = rand() % 2;
    return a;
}

char *getCurrentPlayer()
{
    int toss_coin_result = coinToss();
    if (toss_coin_result == 1)
    {
        return "You";
    }
    else
    {
        return "Bot";
    }
}

void announceTheLost(char currentPlayer[])
{
    printf("%s have lost.\n", currentPlayer);
}

void shiftPlayer(char **currentPlayer)
{

    if (*currentPlayer[0] == 'Y')
    {
        *currentPlayer = "Bot";
    }
    else
    {
        *currentPlayer = "You";
    }
}
