#include "../config.h"

typedef struct
{
    unsigned count;
    char **strings;
} SplitResult;

char *getString(char prompt[]);
char getChar();
// Returns 1 if true and logs Are you sure? to the console
int getConfirmation();
int parseInt(char *inputString, int *outputInt);
int generateRandomString(char *outputString, int strLen);
char generateRandomChar();
unsigned long hash(unsigned char *str);
SplitResult splitString(char *string);
int canAccessDir(char *path);