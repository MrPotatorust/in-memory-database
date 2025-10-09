#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "helpers.h"

int actionSave(){
    char inputKey[KEY_SZ];
    char inputValue[VALUE_SZ];

    printf("Key: ");
    fgets(inputKey, sizeof(inputKey), stdin);
    inputKey[strcspn(inputKey, "\n")] = 0;
    printf("Value: ");
    fgets(inputValue, sizeof(inputValue), stdin);
    inputValue[strcspn(inputValue, "\n")] = 0;

    if(!inputKey || !inputValue){
        return 1;
    }


    Node *newNode = malloc(sizeof(Node));
    strncpy(newNode->key, inputKey, KEY_SZ - 1);
    newNode->key[KEY_SZ - 1] = '\0';

    strncpy(newNode->value, inputValue, VALUE_SZ - 1);
    newNode->value[VALUE_SZ - 1] = '\0';

    newNode->next = NULL;

    int arrIndex = getStorageIndex(inputKey);


    if(storage[arrIndex] == NULL){
        storage[arrIndex] = newNode;
    }
    else {
        saveNode(newNode, arrIndex);
    }

    return 0;
}

int actionGetValue(){

    char keyStr[KEY_SZ];

    printf("KEY: ");
    fgets(keyStr, sizeof(keyStr), stdin);
    keyStr[strcspn(keyStr, "\n")] = 0;

    char value[VALUE_SZ];
    int valueCode = getValue(keyStr, value);

    if (value && !valueCode){
        printf("%s \n", value);
    } 
    else {
        printf("Could not find the desired value. \n");
    }
    
    return 0;
}