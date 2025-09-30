#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char configPath[] = "../config.json";

struct config
{
    char key[30];
    char value[30];
};


int parse(){
    FILE *configFile = fopen(configPath, "r");

    if(configFile == NULL){
        printf("The config file could not be opened, check that its located in the root of the project");
        return 1;
    }

    char buffer;
    char curVal[30];
    bool inBrackets = false;
    bool readingKey = false;
    bool readingValue = false;


    while (fread(&buffer, sizeof(buffer), 1, configFile))
    {
        if (buffer == '{'){
            inBrackets = true;
        }
        if (buffer == '}'){
            inBrackets = false;
        }

        if (inBrackets){
            printf("%c \n", buffer);
        }
        
    }
    return 0;   
}