
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **loadSpellsFromFile(const char *filePath, int *numSpells, int spell_length)
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

    char buffer[spell_length];
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