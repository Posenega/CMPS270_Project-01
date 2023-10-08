#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    char **list = NULL;
    list = (char **)malloc(sizeof(char *) * 20);

    for (int i = 0; i < 5; i++)
    {
        printf("start\n");
        char buffer[20];
        scanf("%s", buffer);
        if (isSpellInList(buffer, list, 5))
        {
            printf("spell is in list\n");
            break;
        }
        list[i] = (char *)malloc(sizeof(char) * 20);
        strcpy(list[i], buffer);
        printf("\n");
    }

    for (int i = 0; i < 5; i++)
    {
        free(list[i]);
    }
    free(list);

    return 0;
}