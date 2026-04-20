#include <time.h>

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#define BASE_STORAGE_SZ 1000
#define STORAGE_SCALE_FACTOR 2
#define SCALE_STORAGE_AT_PERCENT_FULL 50
#define KEY_SZ 20
#define VALUE_SZ 100
#define USER_INPUT_SZ 100

// Settings
#define DANGER_MODE 0

typedef struct Node
{
    struct Node *next;
    char key[KEY_SZ];
    void *value;
    enum type
    {
        INT, // Default long int
        STRING,
        CHAR,
        FLOAT // Default double
    };
    time_t expires_at;
} Node;

#endif