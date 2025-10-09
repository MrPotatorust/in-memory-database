#include "../config.h"

void printStorage();
int saveNode(Node *newNode, int arrIndex);
void freeStorage();
int getValue(char *key, char *valueStr);
int getStorageIndex(unsigned char *str);
int getString(char *outputStr);
int parseInt(char *inputString, int *outputInt);
unsigned long hash(unsigned char *str);