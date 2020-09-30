#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gamefunc.h"
#define MAX_SIZE 100

int main()
{
    char dictName[] = "dico.txt";
    char letter;
    int flagReplay, flagWordFound = 0, wordSize = 0, maxShot = 0, Nshot = 0;

    do
    {
        // Init
        char *word = NULL, *lettersFound = NULL;
        word = malloc(MAX_SIZE * sizeof(char));
        lettersFound = malloc(MAX_SIZE * sizeof(char));
        if ((word == NULL) || (lettersFound == NULL))
        {
            printf("Error during memory allocation.");
            exit(0);
        }

        // Randomly choose word and ask for difficulty
        chooseWord(dictName, word);
        maxShot = chooseDifficulty();
        printf("The word %s is %d characters long.\nYou must find it in under %d errors.\n", word, strlen(word), maxShot);
        
        // The game begins here
        do
        {
            flagWordFound = 0;

            printf("\n");
            displayWord(word, lettersFound);
            printf("Il vous reste %d erreurs. ", maxShot - Nshot);
            printf("Choisissez une lettre : ");
            letter = toupper(readChar());
            if (strchr(word, letter) != NULL && strchr(lettersFound, letter) == NULL)
            {
                strcat(lettersFound, &letter);
                flagWordFound = checkWordFound(word, lettersFound);
            }
            else
            {
                Nshot++;
            }
        } while ((maxShot > Nshot) && (flagWordFound != 1));

        // End of the loop : did the player win ?
        if (flagWordFound)
        {
            printf("\n%s\n",word);
            printf("Bravo ! Vous avez trouvé.\n");
        }
        else
        {
            printf("Perdu !\n");
        }

        // Replay ?
        flagReplay = 0;
        printf("\nVoulez-vous rejouer (Y/N)? ");
        letter = readChar();
        if (toupper(letter) == 'Y')
        {
            flagReplay = 1;
        }

        // Flush
        free(lettersFound);
        free(word);
    } while (flagReplay == 1);
    return 0;
}