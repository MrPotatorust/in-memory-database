
#define MAX_MESSAGE_SZ 256
#include <time.h>

char *action(char *string);
char *actionSave(char *key, char *value, int expiresInSecons);
char *actionGetValue(char *keyStr);
char *actionDelete(char *keyStr);