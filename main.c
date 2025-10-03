#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "./src/helpers.h"
#include "./src/actions.h"


int action();
void printStorage();


int main(int argc, char* argv[]){
    
    char *userInput[100];   
    int returnCode = 0;
    

    while (!returnCode)
    {
        returnCode = action();
    }
    
    freeStorage();
    
    return 0;
}

int action(){

    char inputActionStr[20];
    char inputAction;
    
    printf("ACTION: ");
    fgets(inputActionStr, sizeof(inputActionStr), stdin);
    inputActionStr[strcspn(inputActionStr, "\n")] = 0;

    inputAction = inputActionStr[0];
    
    switch (inputAction)
    {
    case 's':
        actionSave();
        break;
    case 'e':
        return 1;
    case 'p':
        printStorage();
        break;
    case 'g':
        actionGetValue();
    default:
        break;
    }

    return 0;
}