#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "config_parser.h"

char configPath[] = "config.json";

configItem config[1000];

int parse()
{
    FILE *configFile = fopen(configPath, "r");

    if (configFile == NULL)
    {
        printf("The config file could not be opened, check that its located in the root of the project. \n");
        return 1;
    }

    char buffer;

    char bufferLine[MAX_CONFIG_LINE_SZ];

    configItem curConfigItem;

    while (fgets(bufferLine, MAX_CONFIG_LINE_SZ, configFile))
    {
        char **bufferConfig = splitLines(bufferLine);
        // printf("%s, %s \n", bufferConfig[0], bufferConfig[1]);
        sterilizeConfig(bufferConfig);
    }

    return 0;
}

// returns returnArr[2] first one is a key, second one is the value
char **splitLines(char *bufferLine)
{

    char *res = strtok(bufferLine, ":");

    char *key = malloc(sizeof(char) * CONFIG_STRING_SZ);
    char *value = malloc(sizeof(char) * CONFIG_STRING_SZ);

    if(res){
        strcpy(key, res);
    }

    while (res != NULL)
    {        
        strcpy(value, res);
        res = strtok(NULL, ":");
    }

    char **returnArr = malloc(sizeof(char*) * 2);

    returnArr[0] = key;
    returnArr[1] = value;
    
    return returnArr;
}

// Expects values[2]
configItem sterilizeConfig(char**values){
    char key[CONFIG_STRING_SZ];
    char value[CONFIG_STRING_SZ];

    if(value[0] == '{'){
        printf("TEST \n");
        // strcpy(key+1, values[0]);
    }
    else {
        printf("%c \n", *values[0]);
        // strcpy(key, values[0]);
    }
    
    // if(value[1] == '{'){
    //     strcpy(key, values[0]);
    // }
    // else {
    //     strcpy(key, values[0]);
    // }

    // strcpy(value, values[1]);

    // for (int i; i < strlen(key); i++){

    // }
    
    // printf("%s, %s \n",key, value);
    // printf("%c, %c \n",key[0], value[0]);
}