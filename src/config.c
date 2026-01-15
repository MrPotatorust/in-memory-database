#include "config.h"
#include "config_parser.h"

ConfigT initConfig()
{
    parsedConfigT *parsedConfig = parse();

}

union configValue getFromConfig(ConfigT config, char *key)
{

}