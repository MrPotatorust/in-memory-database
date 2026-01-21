#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "helpers.h"
#include "../config.h"

void printStorage()
{

    printf("=============================== \n");
    for (int i = 0; i < STORAGE_SZ; i++)
    {

        Node *curNode = storage[i];

        if (curNode != NULL)
        {
            printf("------------------------ \n");
            printf("%s, %s\n", curNode->key, curNode->value);
            if (curNode->next != NULL)
            {
                while (curNode->next != NULL)
                {
                    curNode = curNode->next;
                    printf("| \n");
                    printf("->");
                    printf(" %s, %s\n", curNode->key, curNode->value);
                }
            }
        }
    }
    printf("=============================== \n");
}

int saveNode(Node *newNode)
{

    long unsigned int arrIndex = getStorageIndex(newNode->key);

    if (storage[arrIndex] == NULL)
    {
        storage[arrIndex] = newNode;
        return 0;
    }

    Node *curNode = storage[arrIndex];

    while (curNode->next != NULL && strcmp(curNode->key, newNode->key))
    {
        curNode = curNode->next;
    }

    if (!strcmp(curNode->key, newNode->key))
    {
        printf("A Node with this key already exists. This action will overwrite it. \n");
        if (!getConfirmation())
        {
            return 1;
        }

        strcpy(curNode->value, newNode->value);
        free(newNode);
        return 0;
    }

    curNode->next = newNode;

    return 0;
}

void freeStorage()
{

    Node *curNode;
    Node *nextNode;

    for (int i = 0; i < STORAGE_SZ; i++)
    {
        if (storage[i] != NULL)
        {
            if (storage[i]->next != NULL)
            {

                curNode = storage[i];

                while (curNode->next != NULL)
                {
                    nextNode = curNode->next;

                    free(curNode);
                    curNode = NULL;
                    curNode = nextNode;
                }
            }

            free(storage[i]);
            storage[i] = NULL;
        }
    }
}

char *getValue(char *key)
{

    char *valueStr = malloc(sizeof(char) * VALUE_SZ);

    if (valueStr == NULL)
    {
        return NULL;
    }

    long unsigned int index = getStorageIndex(key);
    Node *curNode = storage[index];

    if (curNode == NULL)
    {
        return NULL;
    }

    if (!strcmp(curNode->key, key))
    {
        strcpy(valueStr, curNode->value);
        return NULL;
    }

    while (strcmp(curNode->key, key) && curNode->next != NULL)
    {
        curNode = curNode->next;
    }

    strcpy(valueStr, curNode->value);
    return valueStr;
}

int deleteNode(char *key)
{
    long unsigned int index = getStorageIndex(key);
    Node *curNode = storage[index];
    Node *prevNode = NULL;

    if (curNode == NULL)
    {
        return 1;
    }

    while (curNode != NULL && strcmp(curNode->key, key))
    {
        prevNode = curNode;
        curNode = curNode->next;
    }

    if (curNode == NULL)
    {
        return 1;
    }

    if (prevNode == NULL)
    {
        storage[index] = curNode->next;
    }
    else
    {
        prevNode->next = curNode->next;
    }

    free(curNode);
    return 0;
}

long unsigned int getStorageIndex(char *str)
{
    return hash((unsigned char *)str) % STORAGE_SZ;
}

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

// This can be written simpler with a for loop but I wanted to try it with a for loop
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