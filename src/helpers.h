#include "../config.h"

int getValue(char *key, char *valueStr);
int getStorageIndex(unsigned char *str);
unsigned long hash(unsigned char *str);
void addToLinkedList(Node *newNode, int arrIndex);
void freeStorage();