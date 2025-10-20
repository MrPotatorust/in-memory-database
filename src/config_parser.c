#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config_parser.h"

char configPath[] = "config.json";

configItem config[1000];

int parse(){
    FILE *configFile = fopen(configPath, "r");

    if(configFile == NULL){
        printf("The config file could not be opened, check that its located in the root of the project. \n");
        return 1;
    }

    char buffer;
    
    char bufferLine[30];


    while (true)
    {
        // fread(&buffer, sizeof(buffer), 1, configFile);
        fgets(bufferLine, 30, configFile);
        

    }
    return 0;   
}

void splitLines(){
    
}