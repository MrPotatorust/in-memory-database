#include <stdbool.h>
#define CONFIG_STRING_SZ 30
#define MAX_CONFIG_LINE_SZ 65

#ifndef CONFIG_PARSER
#define CONFIG_PARSER

union configValue
{
    int integer;
    bool boolean;
    char *string[CONFIG_STRING_SZ];
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

int parse();
char **splitLines(char *bufferLine);
configItem sterilizeConfig(char **values)

#endif