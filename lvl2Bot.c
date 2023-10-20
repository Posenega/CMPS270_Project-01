#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPELL_LENGTH 100
int lvl1Bot(int numSpell){
    return rand() % numSpell;
}

int lvl2Bot(char *prevSpell,char **spellList, int numspell){
    if(prevSpell == NULL){
        return lvl1Bot(numspell);
    }
    int longest_spell_index = -1;
    int maxLen = 0;
    for (int i = 0;i<numspell;i++){
        if((strcmp(spellList[i],prevSpell)) !=0 && 
        spellList[i][0] == prevSpell[strlen(prevSpell)-1]
        && strlen(spellList[i]) > maxLen){
            longest_spell_index = i;
            maxLen = strlen(spellList[i]);
        }
    }
    return longest_spell_index;
}

char **loadSpellsFromFile(const char *filePath, int *numSpells)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        perror("Error reading the file");
        return NULL;
    }

    char **spellsList = NULL;
    int capacity = 20;
    int count = 0;

    spellsList = (char **)malloc(sizeof(char *) * capacity);
    if (spellsList == NULL)
    {
        perror("Error allocating memory for spellsList");
        fclose(file);
        free(spellsList);
        return NULL;
    }

    char buffer[MAX_SPELL_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Remove newline character, if present
        buffer[strcspn(buffer, "\n")] = '\0';

        spellsList[count] = (char *)malloc(strlen(buffer) + 1);
        if (spellsList[count] == NULL)
        {
            perror("Error allocating memory for a string in spellsList");
            fclose(file);

            // Free previously allocated memory
            for (int i = 0; i < count; i++)
            {
                free(spellsList[i]);
            }
            free(spellsList);
            return NULL;
        }

        strcpy(spellsList[count], buffer);
        count++;

        if (count == capacity)
        {
            // Resize the spellsList array if it's full
            capacity *= 2;
            char **temp = (char **)realloc(spellsList, sizeof(char *) * capacity);
            if (temp == NULL)
            {
                perror("Error reallocating memory for spellsList");
                fclose(file);
                return NULL;
            }
            spellsList = temp;
        }
    }

    fclose(file);
    *numSpells = count;
    return spellsList;
}

int isSpellInList(const char *spell, char **spellsList, int numSpells)
{
    for (int i = 0; i < numSpells; i++)
    {
        if (spellsList[i] == NULL)
        {
            return 0;
        }
        if (strcmp(spell, spellsList[i]) == 0)
        {
            return 1; // Spell is found in the list
        }
    }
    return 0; // Spell is not found in the list
}

void displayTable(char **spellsList, int numSpells)
{

    for (int i = 1; i <= numSpells; i++)
    {
        printf("%-17s  ", spellsList[i - 1]);
        if (i % 5 == 0)
        {
            printf("\n");
        }
    }
}

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
    return (rand() % 2) + 1;
}

int main()
{

    // Loading Spells from file
    int numSpells;
    char **spellsList = loadSpellsFromFile("spells.txt", &numSpells);

    if (spellsList == NULL)
    {
        printf("Failed to load the spell list.\n");
        return 1;
    }

    // Getting user input

    char player1[10];

    printf("Player 1, enter your name: ");
    scanf("%s", player1);

    printRule(player1);

    // Display the spell list
    displayTable(spellsList, numSpells);

    // DETERMINE WHO STARTS

    int currentPlayer = coinToss();
    if(currentPlayer == 2){
        printf("Bot will starts.\n");
    }
    else{
        printf("Player %d starts.\n", currentPlayer);
    }
    int rounds = 0;
    char lastLetter = ' ';
    char **enteredSpells = NULL;
    enteredSpells = (char **)malloc(sizeof(char *) * numSpells);

    // GAME STARTS
    while (1)
    {
        char spell[MAX_SPELL_LENGTH];
        if(currentPlayer == 2){
            printf("Bot entered a spell.\n");
            int i = lvl2Bot(NULL,spellsList,numSpells);
            char *spell = spellsList[i];
            printf("%s",spell);
        }
        else{
            printf("Player %d enter a spell.\n", currentPlayer);
            scanf("%s", spell);
        }
        if (rounds != 0 && spell[0] != lastLetter)
        {
            printf("Spell does not start with the last letter of the previous word.\n");
            printf("Player %d loses.\n", currentPlayer);
            break;
        }
        if (!isSpellInList(spell, spellsList, numSpells))
        {
            printf("Spell not found in the list.\n");
            printf("Player %d loses.\n", currentPlayer);
            break;
        }
        if (isSpellInList(spell, enteredSpells, numSpells))
        {
            printf("Spell was already used before.\n");
            printf("Player %d loses.\n", currentPlayer);
            break;
        }
        lastLetter = spell[strlen(spell) - 1];
        currentPlayer = (currentPlayer == 1) ? 2 : 1;

        // Enter the spell in enteredSpells
        // spellsList[count] = (char *)malloc(strlen(buffer) + 1);
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
