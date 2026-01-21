#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../config.h"
#include "seeder.h"
#include "helpers.h"

int seedStorage(int nodeNumber)
{

    for (int i = 0; i < nodeNumber; i++)
    {
        Node *newNode = generateNode();

        saveNode(newNode);
    }

    return 0;
}

Node *generateNode()
{
    Node *newNode = malloc(sizeof(Node));
    if (!newNode)
    {
        perror("malloc");
        return NULL;
    }

    char randomKey[KEY_SZ];
    char randomValue[VALUE_SZ];

    generateRandomString(randomKey, KEY_SZ);
    generateRandomString(randomValue, VALUE_SZ);

    newNode->next = NULL;

    strncpy(newNode->key, randomKey, KEY_SZ);
    newNode->key[KEY_SZ - 1] = '\0';
    strncpy(newNode->value, randomValue, VALUE_SZ);
    newNode->value[VALUE_SZ - 1] = '\0';

    return newNode;
}