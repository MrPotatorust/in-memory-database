#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "config.h"
#include "./src/helpers.h"
#include "./src/actions.h"
#include "./src/seeder.h"


int action();


int main(int argc, char* argv[]){

    srand(time(NULL));
    
    int returnCode = 0;
    

    if (argc > 1){
        int seedNumber;

        if(parseInt(argv[1], &seedNumber) == 3){
            printf("Usage: ./main [int seedNumber?]");
            return 1;
        }

        seedStorage(seedNumber);
    }

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
        return 0;
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