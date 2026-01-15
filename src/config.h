#include <stdbool.h>

#ifndef CONFIG
#define CONFIG

#define CONFIG_STRING_SZ 30
#define MAX_CONFIG_LINE_SZ 65
#define MAX_CONFIG_LINES 30

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

typedef struct config
{
    configItem *items;
    int itemNum;
} ConfigT;

ConfigT initConfig();

union configValue getFromConfig(ConfigT config, char *key);

#endif