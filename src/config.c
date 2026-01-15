#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "config.h"

char configPath[] = "config.json";

configT *initConfig()
{
    configItem *configItems = malloc(sizeof(configItem) * MAX_CONFIG_LINES);

    configT *config = malloc(sizeof(configT));

    config->itemNum = MAX_CONFIG_LINES;
    config->items = configItems;

    FILE *configFile = fopen(configPath, "r");

    if (configFile == NULL)
    {
        printf("The config file could not be opened, check that its located in the root of the project. \n");
        return NULL;
    }

    char buffer;

    char bufferLine[MAX_CONFIG_LINE_SZ];

    int size = 0;

    while (fgets(bufferLine, MAX_CONFIG_LINE_SZ, configFile))
    {
        char **bufferConfig = splitLines(bufferLine);

        if (!areCurlyBraces(bufferConfig))
        {
            configItem *item = malloc(sizeof(configItem));
            *item = parseConfigItem(bufferConfig);

            // Assigns the next config item to the config array (Note to self)
            config->items[size] = *item;

            size++;
        }

        free(bufferConfig[0]);
        free(bufferConfig[1]);
        free(bufferConfig);
        bufferConfig = NULL;
    }

    config->itemNum = size;

    return config;
}

// returns returnArr[2] first one is a key, second one is the value
char **splitLines(char *bufferLine)
{

    char *res = strtok(bufferLine, ":");

    char *key = malloc(sizeof(char) * CONFIG_STRING_SZ);
    char *value = malloc(sizeof(char) * CONFIG_STRING_SZ);

    if (res)
    {
        strcpy(key, res);
    }

    while (res != NULL)
    {
        strcpy(value, res);
        res = strtok(NULL, ":");
    }

    char **returnArr = malloc(sizeof(char *) * 2);

    returnArr[0] = key;
    returnArr[1] = value;

    return returnArr;
}

// Expects values[2]
configItem parseConfigItem(char **values)
{
    char *key = malloc(sizeof(char) * CONFIG_STRING_SZ);
    char *value = malloc(sizeof(char) * CONFIG_STRING_SZ);

    enum valueType type;

    strcpy(key, values[0]);
    strcpy(value, values[0]);

    key = trimString(values[0]);
    value = trimString(values[1]);

    configItem item;

    item.valueType = string;

    strcpy(item.key, stripTags(key));
    strcpy(item.value.string, stripTags(value));

    free(key);
    free(value);

    return item;
}

char *trimString(char *originalString)
{

    if (originalString == NULL || originalString[0] == '\0')
    {
        return NULL;
    }

    // char *newString = malloc(sizeof(char) * CONFIG_STRING_SZ);
    char *newString = malloc(sizeof(char) * CONFIG_STRING_SZ);

    if (newString == NULL)
    {
        return NULL;
    }

    int index = 0;
    int lastLetter = 0;
    int newStringIndex = 0;

    while (*(originalString + index) != '\0' || index > CONFIG_STRING_SZ)
    {
        if (lastLetter || !isspace(*(originalString + index)))
        {
            newString[newStringIndex] = *(originalString + index);
            newStringIndex++;
        }
        if (!isspace(*(originalString + index)))
        {
            lastLetter = newStringIndex;
        }

        index++;
    }
    if (lastLetter)
    {
        newString[lastLetter] = '\0';
    }
    else
    {
        newString[newStringIndex + 1] = '\0';
    }

    return newString;
}

// Used to check if the current line is the beginning or the end of the json (so only curly braces)
bool areCurlyBraces(char **values)
{
    if (*values[0] == '{' && *values[1] == '{')
        return true;

    if (*values[0] == '}' && *values[1] == '}')
        return true;

    return false;
}

char *stripTags(char *string)
{
    char *newString = malloc(sizeof(char) * CONFIG_STRING_SZ);

    if (newString == NULL)
    {
        return NULL;
    }

    char *iter = newString;

    while (*string != '\0')
    {
        if ((*string) != '"')
        {
            *iter = *string;
            iter++;
        }
        string++;
    }

    *iter = '\0';

    return newString;
}
union configValue getFromConfig(configT config, char *key)
{
}