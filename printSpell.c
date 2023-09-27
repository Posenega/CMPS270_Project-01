#include <stdio.h>

void printSpell(char spellName[][50], int numStr) {
    int i = 0, count = 0;

    while (i < numStr) {
        if (count == 5) {
            printf("\n");
            count = 0;
        }
        printf("%s ", spellName[i]);
        i++;
        count++;
    }
}

//test
int main() {
    char strings[6][50] = {
        "First string",
        "Second string",
        "Third string",
        "Fourth string",
        "Fifth string",
        "Sixth string"
    };
    printSpell(strings, 6);
    return 0;
}
