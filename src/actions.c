#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "helpers.h"
#include "actions.h"

char *action(char *string)
{
    char *message = malloc(sizeof(char) * MAX_MESSAGE_SZ);

    if (message == NULL)
    {
        printf("Return message could not be allocated \n");
        return NULL;
    }

    SplitResult splitAction = splitString(string);

    // printf("COUNT %i", splitAction.count);

    // printf("TEST ACTION %c \n", splitAction.strings[0][0]);
    strcpy(message, "Successfully executed \n");

    switch (splitAction.strings[0][0])
    {
    case 's':
        strcpy(message, actionSave(splitAction.strings[1], splitAction.strings[2]));
        break;
    case 'e':
        break;
    case 'p':
        strcpy(message, printStorage());
        break;
    case 'g':
        strcpy(message, actionGetValue(splitAction.strings[1]));
        break;
    case 'd':
        strcpy(message, actionDelete(splitAction.strings[1]));
        break;
    default:
        break;
    }

    return message;

    return NULL;
}

char *actionSave(char *key, char *value)
{
    if (strlen(key) > KEY_SZ)
    {
        printf("The provided key is too big \n");
        return 1;
    }

    if (strlen(value) > VALUE_SZ)
    {
        printf("The provided value is too big \n");
        return 1;
    }

    if (!key || !value)
    {
        return 1;
    }

    Node *newNode = malloc(sizeof(Node));
    strncpy(newNode->key, key, KEY_SZ - 1);
    newNode->key[KEY_SZ - 1] = '\0';

    strncpy(newNode->value, value, VALUE_SZ - 1);
    newNode->value[VALUE_SZ - 1] = '\0';

    newNode->next = NULL;

    saveNode(newNode);

    return 0;
}

char *actionGetValue(char *keyStr)
{

    if (strlen(keyStr) > KEY_SZ)
    {
        printf("The provided key is too big \n");
        return 1;
    }

    char *value = getValue(keyStr);

    if (value != NULL)
    {
        printf("%s \n", value);
    }
    else
    {
        printf("Could not find the desired value. \n");
    }

    return 0;
}

char *actionDelete(char *keyStr)
{

    if (strlen(keyStr) > KEY_SZ)
    {
        printf("The provided key is too big \n");
        return 1;
    }

    int deleteCode = deleteNode(keyStr);

    if (!deleteCode)
    {
        printf("Successfully deleted node. \n");
    }
    else
    {
        printf("Could not delete node. \n");
    }

    return 0;
}