#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_SIZE 100


char readChar()
{
    char letter;
    letter = getchar();

    while (getchar() != '\n')
        ; // Empty buffer

    return letter;
}


int chooseWord(char dictName[], char word[])
{
    char letter;
    int Nword = 0;
    int wordIndex = 0;
    int lineIndex = 0;

    srand(time(NULL));

    // Open file
    FILE *file = NULL;
    file = fopen(dictName, "r");
    if (file == NULL)
    {
        printf("L'ouverture du fichier %s a échoué.", dictName);
        exit(0);
    }

    // Count words in file
    do
    {
        letter = fgetc(file);
        if (letter == '\n')
        {
            Nword++;
        }
    } while (letter != EOF);
    rewind(file);

    // Choose word randomly
    wordIndex = rand() % (Nword+1);
    while (lineIndex != wordIndex)
    {
        letter = fgetc(file);
        if (letter == '\n')
        {
            lineIndex++;
        }
    }
    fgets(word, MAX_SIZE, file);

    // Get rid of line break
    char *firstLineBreak = NULL;
    firstLineBreak = strchr(word, '\n');
    if (firstLineBreak != NULL)
    {
        firstLineBreak[0] = '\0';
    }

    fclose(file);
    return strlen(word);
}

int chooseDifficulty()
{
    char index, errEasy = 10, errMedium = 8, errHard = 6;
    printf("Veuillez choisir une difficulté :\n");
    printf("\t1) %d erreurs permises\n", errEasy);
    printf("\t2) %d erreurs permises\n", errMedium);
    printf("\t3) %d erreurs permises\n", errHard);
    printf("Votre choix ? ");
    index = readChar();

    switch (index)
    {
    case '1':
        return errEasy;
        break;
    case '2':
        return errMedium;
        break;
    case '3':
        return errHard;
        break;
    default:
        return errMedium;
        break;
    }
}

void displayWord(char word[], char lettersFound[])
{
    int i = 0;
    for (i = 0; i < strlen(word); i++)
    {
        if (strchr(lettersFound, word[i]) != NULL)
        {
            printf("%c", word[i]);
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}

int checkWordFound(char word[], char lettersFound[])
{
    int i = 0;
    for (i = 0; i < strlen(word); i++)
    {
        if (strchr(lettersFound, word[i]) == NULL)
        {
            return 0;
        }
    }
    return 1;

}