#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "helpers.h"
#include "actions.h"

char *action(char *string)
{

    char *message = malloc(sizeof(char) * MAX_MESSAGE_SZ);
    char *actionMessage = NULL;

    if (message == NULL)
    {
        printf("Return message could not be allocated \n");
        return NULL;
    }

    if (string == NULL || strlen(string) == 0)
    {
        strcpy(message, "No action \n");
        return message;
    }

    SplitResult splitAction = splitString(string);

    switch (splitAction.strings[0][0])
    {
    case 's':
        if (!(splitAction.count == 3 || splitAction.count == 4))
        {
            strcpy(message, "Didnt pass correct amount of arguments, [action] [key] [value] [?expires] \n");
            return message;
        }

        int expiresInSeconds = 0;
        if (splitAction.count == 4)
        {
            expiresInSeconds = atoi(splitAction.strings[3]);
        }

        printf("Seconds %i \n", expiresInSeconds);

        actionMessage = actionSave(splitAction.strings[1], splitAction.strings[2], expiresInSeconds);
        break;
    case 'g':
        if (splitAction.count != 2)
        {
            strcpy(message, "Didnt pass correct amount of arguments, [action] [key] \n");
            return message;
        }
        actionMessage = actionGetValue(splitAction.strings[1]);
        break;
    case 'd':
        if (splitAction.count != 2)
        {
            strcpy(message, "Didnt pass correct amount of arguments, [action] [key] \n");
            return message;
        }
        actionMessage = actionDelete(splitAction.strings[1]);
        break;
    default:
        break;
    }

    if (actionMessage != NULL)
    {
        strcpy(message, actionMessage);
        free(actionMessage);
    }
    else
    {
        strcpy(message, "No action \n");
    }
    return message;
}

char *actionSave(char *key, char *value, int expiresInSeconds)
{
    size_t messageSize = sizeof(char) * MAX_MESSAGE_SZ;
    char *message = malloc(messageSize);
    time_t currentTime;
    time(&currentTime);

    if (message == NULL)
    {
        printf("Could not allocate memory for message in actionSave \n");
        return NULL;
    }

    if (strlen(key) > KEY_SZ)
    {
        strcpy(message, "The provided key is too big \n");
        return message;
    }

    if (strlen(value) > VALUE_SZ)
    {
        strcpy(message, "The provided value is too big \n");
        return message;
    }

    if (!key || !value)
    {
        strcpy(message, "Didnt provide key or value \n");
        return message;
    }

    Node *newNode = malloc(sizeof(Node));
    strncpy(newNode->key, key, KEY_SZ - 1);
    newNode->key[KEY_SZ - 1] = '\0';

    strncpy(newNode->value, value, VALUE_SZ - 1);
    newNode->value[VALUE_SZ - 1] = '\0';

    newNode->expires_at = expiresInSeconds ? currentTime + expiresInSeconds : 0;

    newNode->next = NULL;

    saveNode(newNode, 1);

    snprintf(message, messageSize, "saved %s, %s \n", key, value);
    return message;
}

char *actionGetValue(char *keyStr)
{
    size_t messageSize = sizeof(char) * MAX_MESSAGE_SZ;
    char *message = malloc(messageSize);

    if (message == NULL)
    {
        printf("Could not allocate memory for message in actionGetValue \n");
        return NULL;
    }

    if (strlen(keyStr) > KEY_SZ)
    {
        strcpy(message, "The provided key is too big \n");
        return message;
    }

    char *value = getValue(keyStr);

    if (value == NULL)
    {
        strcpy(message, "Could not find the desired value. \n");
        return message;
    }

    snprintf(message, messageSize, "%s\n", value);

    free(value);

    return message;
}

char *actionDelete(char *keyStr)
{
    size_t messageSize = sizeof(char) * MAX_MESSAGE_SZ;
    char *message = malloc(messageSize);

    if (message == NULL)
    {
        printf("Could not allocate memory for message in actionGetValue \n");
        return NULL;
    }

    if (strlen(keyStr) > KEY_SZ)
    {
        strcpy(message, "The provided key is too big \n");
        return message;
    }

    int deleteCode = deleteNode(keyStr);

    if (deleteCode == 0)
    {

        snprintf(message, messageSize, "deleted %s\n", keyStr);
    }
    else
    {
        strcpy(message, "Could not delete node. \n");
    }

    return message;
}