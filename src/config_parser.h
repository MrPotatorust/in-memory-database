
typedef struct configItem
{
    char key[30];
    char value[30];
    __uint8_t dataType;
} configItem;


int parse();
