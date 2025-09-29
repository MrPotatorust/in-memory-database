#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define STORAGE_SZ 1000
#define KEY_SZ 20
#define VALUE_SZ 100


typedef struct Node
{
    struct Node *next;
    char key[KEY_SZ];
    char value[VALUE_SZ];
} Node;

struct Node *storage[STORAGE_SZ];



int action();
void printStorage();
unsigned long hash(unsigned char *str);

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


    struct Node newItem;
    strncpy(newItem.key, inputKey, KEY_SZ - 1);
    newItem.key[KEY_SZ - 1] = '\0';

    strncpy(newItem.value, inputValue, VALUE_SZ - 1);
    newItem.value[VALUE_SZ - 1] = '\0';


    int arrIndex = hash(inputKey) % STORAGE_SZ;


    if(storage[arrIndex] == NULL){
        newItem.next = NULL;
        *storage[arrIndex] = newItem;
    }

    




    return 0;
}

void printStorage(){
    
    for (int i = 0; i < STORAGE_SZ; i++ ){
        if (storage[i]->key[0] != '\0' && storage[i]->value[0] != '\0') {
            printf("------------------------ \n");
            printf("%s, %s\n", storage[i]->key, storage[i]->value);
        }
    }
}

void addToLinkedList(Node newItem){

    
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
