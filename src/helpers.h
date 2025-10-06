#include "../config.h"

void printStorage();
void addToLinkedList(Node *newNode, int arrIndex);
void freeStorage();
int getValue(char *key, char *valueStr);
int getStorageIndex(unsigned char *str);
int getString(char *outputStr);
unsigned long hash(unsigned char *str);