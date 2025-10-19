
typedef struct configItem
{
    char key[30];
    char value[30];


    // 0 = string, 1 = int, 2 = float, 3 = bool
    int dataType;
} configItem;


int parse();
