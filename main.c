#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "./src/helpers.h"


int action();
void printStorage();


int main(int argc, char* argv[]){
    
    char *userInput[100];
    
    int returnCode = 0;
    
    while (!returnCode)
    {
        returnCode = action();
        printStorage();
    }
    
    freeStorage();
    
    return 0;
}

int action(){

    char inputAction[20];
    
    printf("ACTION: ");
    fgets(inputAction, sizeof(inputAction), stdin);
    inputAction[strcspn(inputAction, "\n")] = 0;
    
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

    int arrIndex = hash(inputKey) % STORAGE_SZ;


    if(storage[arrIndex] == NULL){
        storage[arrIndex] = newNode;
    }
    else {
        addToLinkedList(newNode, arrIndex);
    }

    return 0;
}