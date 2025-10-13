#include "../config.h"

void printStorage();
int saveNode(Node *newNode);
void freeStorage();
int getValue(char *key, char *valueStr);
int getStorageIndex(unsigned char *str);
int getString(char *outputStr);
int parseInt(char *inputString, int *outputInt);
int generateRandomString(char *outputString, int strLen);
char generateRandomChar(int *prevRandom);
int getRandNum();
unsigned long hash(unsigned char *str);