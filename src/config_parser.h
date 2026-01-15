#include <stdbool.h>
#include "config.h"

#ifndef CONFIG_PARSER
#define CONFIG_PARSER

typedef struct parsedConfigT
{
    int numOfItems;
    configItem *configItems;
} parsedConfigT;

parsedConfigT *parse();
char **splitLines(char *bufferLine);
configItem parseConfigItem(char **values);
char *trimString(char *originalString);
bool areCurlyBraces(char **values);
char *stripTags(char *string);

#endif