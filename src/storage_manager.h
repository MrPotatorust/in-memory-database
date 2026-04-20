#include "../config.h"

extern Node *storage;
extern bool isStorageInitialized;
long long int storageSize;
extern bool isStorageScaling;

int initStorage();
void printStorage();
int saveNodeToStorage(Node *newNode, bool force);
int deleteNode(char *key);
bool isNodeExpired(Node *node);
void freeStorage();
char *getValue(char *key);
long unsigned int getStorageIndex(char *str);
int persistStorage(char *path);
bool isStorageEmpty();