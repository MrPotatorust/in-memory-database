#include <stdbool.h>
#define CONFIG_STRING_SZ 30
#define MAX_CONFIG_LINE_SZ 65
#define MAX_CONFIG_LINES 30

#ifndef CONFIG_PARSER
#define CONFIG_PARSER

union configValue
{
    int integer;
    bool boolean;
    char string[CONFIG_STRING_SZ];
};

enum valueType
{
    integer,
    boolean,
    string
};

typedef struct configItem
{
    char key[CONFIG_STRING_SZ];

    enum valueType valueType;

    union configValue value;

} configItem;

configItem *parse();
char **splitLines(char *bufferLine);
configItem parseConfigItem(char **values);
char *trimString(char *originalString);
bool areCurlyBraces(char **values);
char *stripTags(char *string);

#endif