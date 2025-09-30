#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define STORAGE_SZ 1000
#define KEY_SZ 20
#define VALUE_SZ 100


typedef struct Node
{
    struct Node *next;
    char key[KEY_SZ];
    char value[VALUE_SZ];
} Node;

Node *storage[STORAGE_SZ];



int action();
void printStorage();
unsigned long hash(unsigned char *str);
void addToLinkedList(Node *newNode, int arrIndex);
void freeStorage();


int main(int argc, char* argv[]){
    
    char *userInput[100];
    
    int returnCode = 0;
    
    while (!returnCode)
    {
        returnCode = action();
        // printStorage();
    }
    

    return 0;
}

int action(){

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


    printStorage();


    return 0;
}

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
