#include "../config.h"

typedef struct
{
    unsigned count;
    char **strings;
} SplitResult;

void printStorage();
int saveNode(Node *newNode);
int deleteNode(char *key);
void freeStorage();
char *getValue(char *key);
long unsigned int getStorageIndex(char *str);
char *getString(char prompt[]);
char getChar();
// Returns 1 if true and logs Are you sure? to the console
int getConfirmation();
int parseInt(char *inputString, int *outputInt);
int generateRandomString(char *outputString, int strLen);
char generateRandomChar();
unsigned long hash(unsigned char *str);
SplitResult splitString(char *string);