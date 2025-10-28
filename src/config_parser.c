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

    strcpy(key, values[0]);
    strcpy(value, values[0]);

    trimString(values[0]);
    trimString(values[1]);
}

char *trimString(char *originalString){
    
    if(originalString == NULL || originalString[0] == '\0') {
        return NULL;
    }
    
    // char *newString = malloc(sizeof(char) * CONFIG_STRING_SZ);
    char *newString = malloc(sizeof(char) * CONFIG_STRING_SZ);

    int index = 0;
    int lastLetter = 0;
    int newStringIndex = 0;

    while (*(originalString+index) != '\0' || index > CONFIG_STRING_SZ)
    {
        // printf("%c \n", *(originalString+index));
        if (lastLetter || !isspace(*(originalString+index))){
            newString[newStringIndex] = *(originalString+index);
            newStringIndex++;
        }
        if(!isspace(*(originalString+index))){
            lastLetter = newStringIndex;
        }

        index++;
    }   
    if (lastLetter){
        newString[lastLetter] = '\0';
    }
    else {
        newString[newStringIndex+1] = '\0';
    }

    return newString;
}