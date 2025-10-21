#include <stdbool.h>

#ifndef CONFIG_PARSER
#define CONFIG_PARSER
union configValue
{
    int integer;
    bool boolean;
    char string[30];
} configValue;

enum valueType
{
    integer,
    boolean,
    string
};

typedef struct configItem
{
    char key[30];

    enum valueType valueType;

    union configValue value;

} configItem;

int parse();

#endif