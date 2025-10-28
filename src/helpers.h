#include "../config.h"

void printStorage();
int saveNode(Node *newNode);
int deleteNode(char *key);
void freeStorage();
int getValue(char *key, char *valueStr);
int getStorageIndex(unsigned char *str);
char *getString(char prompt[]);
char getChar();
// Returns 1 if true and logs Are you sure? to the console
int getConfirmation();
int parseInt(char *inputString, int *outputInt);
int generateRandomString(char *outputString, int strLen);
char generateRandomChar(int *prevRandom);
unsigned long hash(unsigned char *str);