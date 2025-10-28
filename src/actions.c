#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "helpers.h"

int actionSave(){
    char *inputKey = getString("Key: ");
    if(strlen(inputKey) > KEY_SZ){
        printf("The provided key is too big \n");
        return 1;
    }
    char *inputValue = getString("Value: ");
    if(strlen(inputValue) > VALUE_SZ){
        printf("The provided value is too big \n");
        return 1;
    }

    if(!inputKey || !inputValue){
        return 1;
    }


    Node *newNode = malloc(sizeof(Node));
    strncpy(newNode->key, inputKey, KEY_SZ - 1);
    newNode->key[KEY_SZ - 1] = '\0';

    strncpy(newNode->value, inputValue, VALUE_SZ - 1);
    newNode->value[VALUE_SZ - 1] = '\0';

    newNode->next = NULL;


    saveNode(newNode);

    free(inputKey);
    free(inputValue);

    return 0;
}

int actionGetValue(){

    
    char *keyStr = getString("KEY: ");

    if(strlen(keyStr) > KEY_SZ){
        printf("The provided key is too big \n");
        return 1;
    }

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

int actionDelete(){

    char *keyStr = getString("KEY: ");

    if(strlen(keyStr) > KEY_SZ){
        printf("The provided key is too big \n");
        return 1;
    }


    char value[VALUE_SZ];
    int valueCode = getValue(keyStr, value);

    if (value && !valueCode){
        printf("%s \n", value);
    } 
    else {
        printf("Could not find the desired value. \n");
    }

    free(keyStr);
    
    return 0;
}