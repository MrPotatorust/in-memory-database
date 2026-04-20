#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "helpers.h"
#include "../config.h"

Node **storage = NULL;

bool isStorageInitialized = false;

long long int storageSize = 0;

bool isStorageScaling = false;

int initStorage()
{
    if (storage != NULL || isStorageInitialized == true)
    {
        printf("The storage is already initialized \n");
        return 1;
    }
    storage = malloc(BASE_STORAGE_SZ * sizeof(Node *));

    if (storage == NULL)
    {

        printf("Could not initialize storage \n");
        return 1;
    }
    isStorageInitialized = true;
    return 0;
}

void printStorage()
{

    printf("=============================== \n");
    for (int i = 0; i < storageSize; i++)
    {

        Node *curNode = storage[i];

        if (curNode != NULL)
        {
            printf("------------------------ \n");
            printf("%s, %s, %li \n", curNode->key, curNode->value, curNode->expires_at);
            if (curNode->next != NULL)
            {
                while (curNode->next != NULL)
                {
                    curNode = curNode->next;
                    printf("| \n");
                    printf("->");
                    printf(" %s, %s %li \n", curNode->key, curNode->value, curNode->expires_at);
                }
            }
        }
    }
    printf("=============================== \n");
}

int buildNode(char *key, void *value, time_t expires_at)
{
    return 0;
};

int saveNodeToStorage(Node *newNode, bool force)
{
    long unsigned int arrIndex = getStorageIndex(newNode->key);

    if (storage[arrIndex] == NULL)
    {
        storage[arrIndex] = newNode;
        return 0;
    }

    Node *curNode = storage[arrIndex];
    while (curNode->next != NULL && strcmp(curNode->key, newNode->key))
        curNode = curNode->next;

    if (!strcmp(curNode->key, newNode->key))
    {
        if (!force)
        {
            printf("A Node with this key already exists. This action will overwrite it.\n");
            if (!getConfirmation())
                return 1;
        }
        strcpy(curNode->value, newNode->value);
        curNode->expires_at = newNode->expires_at;
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

    for (int i = 0; i < storageSize; i++)
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
        free(valueStr);
        return NULL;
    }

    while (strcmp(curNode->key, key) != 0 && curNode->next != NULL)
    {
        curNode = curNode->next;
    }

    if (isNodeExpired(curNode))
    {
        deleteNode(curNode->key);
        free(valueStr);
        return NULL;
    }

    if (strcmp(curNode->key, key) == 0)
    {

        strcpy(valueStr, curNode->value);
        return valueStr;
    }

    free(valueStr);
    return NULL;
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

bool isNodeExpired(Node *node)
{

    if (node->expires_at == 0)
        return false;

    time_t currentTime;
    time(&currentTime);

    return currentTime < node->expires_at ? false : true;
}

long unsigned int getStorageIndex(char *str)
{
    return hash((unsigned char *)str) % storageSize;
}

int persistStorage(char *path)
{
    if (isStorageEmpty())
    {
        printf("Nothing to save, storage is empty \n");
        return 1;
    }

    FILE *fptr;
    fptr = fopen(path, "w");

    if (fptr == NULL)
    {
        printf("Could not create new storage file \n");
        return 1;
    }

    printf("Successfully created a save file \n");

    for (int i = 0; i < storageSize; i++)
    {

        Node *curNode = storage[i];

        if (curNode != NULL)
        {
            if (curNode->next != NULL)
            {
                while (curNode->next != NULL)
                {
                    curNode = curNode->next;
                }
            }

            fprintf(fptr, "%s %s\n", curNode->key, curNode->value);
        }
    }

    fclose(fptr);

    return 0;
}

bool isStorageEmpty()
{

    for (int i = 0; i < storageSize; i++)
    {
        Node *curNode = storage[i];

        if (curNode != NULL)
        {
            return false;
        }
    }
    return true;
}