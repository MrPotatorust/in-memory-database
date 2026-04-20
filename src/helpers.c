#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>

#include "helpers.h"
#include "../config.h"

char *getString(char prompt[])
{
    printf("%s", prompt);

    char *userInput = malloc(sizeof(char) * USER_INPUT_SZ);

    fgets(userInput, USER_INPUT_SZ, stdin);
    userInput[strcspn(userInput, "\n")] = 0;

    return userInput;
}

char getChar()
{
    char userInput[3];

    fgets(userInput, sizeof(userInput), stdin);

    return userInput[0];
}

int getConfirmation()
{
    printf("Are you sure? (y/n) ");
    if (getChar() == 'y')
    {
        return 1;
    }

    return 0;
}

// This can be written simpler with a for loop but I wanted to try it without a for loop
int parseInt(char *inputString, int *outputInt)
{

    if (inputString == NULL || outputInt == NULL)
    {
        printf("Tried to pass NULL pointer/s into parseInt(). \n");
        return 1;
    }

    int charIndex = 0;
    char curChar = inputString[charIndex];

    if (curChar == '\0')
    {
        printf("First char is null in parseInt(). \n");
        return 1;
    }

    while (curChar != '\0')
    {
        if (!isdigit(curChar))
        {
            return 3;
        };

        charIndex++;
        curChar = inputString[charIndex];
    }

    *outputInt = atoi(inputString);

    return 0;
}

int generateRandomString(char *outputString, int strLen)
{
    int i;

    int prevRandom = 1;

    for (i = 0; i < strLen - 1; i++)
    {
        outputString[i] = generateRandomChar(&prevRandom);
    }
    outputString[i] = '\0';

    return 0;
}

char generateRandomChar()
{
    int offset = rand() % 26;
    char randomletter = (char)('a' + offset);

    return randomletter;
}

// djb2 hash algorithm
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    unsigned long c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

//? This could be optimized further by only mallocing one block with the length of the string and then just assigning pointers
//? But I dont know if its really that viable and I just want to get this done
SplitResult splitString(char *string)
{
    SplitResult splitResult = {};

    splitResult.count = 0;
    splitResult.strings = NULL;

    size_t stringLen = strlen(string) + 1;

    char *copy = malloc(sizeof(char) * stringLen);
    strcpy(copy, string);

    char *token = strtok(copy, " ");

    while (token != NULL)
    {
        splitResult.count++;
        token = strtok(NULL, " ");
    }

    strcpy(copy, string);

    splitResult.strings = malloc(sizeof(char *) * splitResult.count);

    token = strtok(copy, " ");

    int count = 0;
    while (token != NULL)
    {
        splitResult.strings[count] = token;
        count++;
        token = strtok(NULL, " ");
    }

    return splitResult;
}

int canAccessDir(char *path)
{
    DIR *storageDir = opendir(path);

    if (storageDir)
    {
        closedir(storageDir);
        return 0;
    }
    if (ENOENT == errno)
    {
        printf("The directory at path %s does not exist \n", path);
        return errno;
    }
    printf("The directory at %s is not accessible \n", path);
    return errno;
}