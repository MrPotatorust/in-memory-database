#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#define STORAGE_SZ 1000
#define KEY_SZ 20
#define VALUE_SZ 100
#define USER_INPUT_SZ 100

// Settings
#define DANGER_MODE 0

typedef struct Node
{
    struct Node *next;
    char key[KEY_SZ];
    char value[VALUE_SZ];
} Node;

extern Node *storage[STORAGE_SZ];

#endif