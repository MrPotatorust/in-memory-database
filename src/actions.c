#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "helpers.h"
#include "actions.h"

char *action(char *string)
{
    char *message = malloc(sizeof(char) * MAX_MESSAGE_SZ);

    if (message == NULL){
        printf("Return message could not be allocated \n");
        return NULL;
    }

    SplitResult splitAction = splitString(string);
    
    printf("COUNT %i", )

    if(splitAction.count != 3){
        strcpy(message, "Didnt pass enough parameters");
        return message;
    }

    
    printf("TEST ACTION %c \n", splitAction.strings[0][0]);

    // switch (splitAction.strings[0][0])
    // {
    // case 's':
    //     actionSave(splitAction.strings[1], splitAction.strings[2]);
    //     break;
    // case 'e':
    //     break;
    // case 'p':
    //     printStorage();
    //     break;
    // case 'g':
    //     actionGetValue();
    //     break;
    // case 'd':
    //     actionDelete();
    //     break;
    // default:
    //     break;
    // }

    return NULL;
}

int actionSave(char* key, char *value)
{
    printf("test, %s, %s \n", key, value);
    // char *key = getString("Key: ");
    if (strlen(key) > KEY_SZ)
    {
        printf("The provided key is too big \n");
        return 1;
    }
    // char *value = getString("Value: ");

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

    // free(key);
    // free(value);

    return 0;
}

int actionGetValue()
{

    char *keyStr = getString("KEY: ");

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

int actionDelete()
{

    char *keyStr = getString("KEY: ");

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

    free(keyStr);

    return 0;
}