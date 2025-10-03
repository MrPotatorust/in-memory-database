#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "../config.h"


void printStorage(){    
    
    printf("=============================== \n");
    for (int i = 0; i < STORAGE_SZ; i++ ){

        Node *curNode = storage[i];

        if(curNode != NULL){
            printf("------------------------ \n");
            printf("%s, %s\n", curNode->key, curNode->value);
            if (curNode->next != NULL){
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

void addToLinkedList(Node *newNode, int arrIndex){

    Node *curNode = storage[arrIndex];

    while (curNode->next != NULL)
    {
        curNode = curNode->next;
    }
    curNode->next = newNode;
    
}

void freeStorage(){

    Node *curNode;
    Node *nextNode;

    for (int i = 0; i < STORAGE_SZ; i++ ){
        if(storage[i] != NULL){
            if (storage[i]->next != NULL){
                
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
            storage[i] == NULL;
        }
    }
}

int getValue(char *key, char *valueStr){

    Node *curNode = storage[getStorageIndex(key)];

    if (curNode == NULL){
        return 1;
    }

    while (!strcmp(curNode->key, key) || curNode->next)
    {
        curNode = curNode->next;
    }

    strcpy(valueStr, curNode->value);
    return 0;
}

int getStorageIndex(unsigned char *str){
    return hash(str) % STORAGE_SZ;
}

// djb2 hash algorithm
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
