#include "config_parser.h"

#ifndef CONFIG
#define CONFIG

struct config
{
    configItem *items;
    int itemNum;
};

struct config initConfig();



#endif