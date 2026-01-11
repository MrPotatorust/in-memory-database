#include <stdbool.h>
#include "config.h"

#ifndef CONFIG_PARSER
#define CONFIG_PARSER

typedef struct parsedConfig
{
    int numOfItems;
    configItem *configItems;
} parsedConfig;

parsedConfig *parse();
char **splitLines(char *bufferLine);
configItem parseConfigItem(char **values);
char *trimString(char *originalString);
bool areCurlyBraces(char **values);
char *stripTags(char *string);

#endif