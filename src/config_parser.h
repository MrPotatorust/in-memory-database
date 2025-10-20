#include <stdbool.h>

#ifndef CONFIG_PARSER 
#define CONFIG_PARSER
union configValue {
    int number;
    bool boolean;
    char string[30];
} configValue;

typedef struct configItem
{
    char key[30];

} configItem;



int parse();

#endif