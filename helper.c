// Helper functions that are useful in the main file

#include <stdio.h>
#include <string.h>

void displayTable(char *_filePath)
{
    FILE *filePointer;
    char buffer[100];
    filePointer = fopen(_filePath, "r");
    char spellsList[20][100];
    if (filePointer == NULL)
    {
        perror("Error reading the file");
        fclose(filePointer);
    }

    int count = 0;

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        char word[100];
        strcpy(word, buffer);

        // Remove the newline character if it exists
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }

        strcpy(spellsList[count], word);
        printf("%-18s", spellsList[count]);
        if (count == 4)
        {
            printf("\n");
            printf("\n");
            count = 0;
        }
        else
        {
            count++;
        }
    }
    fclose(filePointer);
}