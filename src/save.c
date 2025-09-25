#include <string.h>
#include <stdlib.h>

int saveToStorage(){
    char inputKey[KEY_SZ];
    char inputValue[VALUE_SZ];

    printf("Key: ");
    fgets(inputKey, sizeof(inputKey), stdin);
    inputKey[strcspn(inputKey, "\n")] = 0;
    printf("Value: ");
    fgets(inputValue, sizeof(inputValue), stdin);
    inputValue[strcspn(inputValue, "\n")] = 0;

    if(!inputKey || !inputValue){
        return 1;
    }


    struct storageItem newItem;
    strncpy(newItem.key, inputKey, KEY_SZ - 1);
    newItem.key[KEY_SZ - 1] = '\0';

    strncpy(newItem.value, inputValue, VALUE_SZ - 1);
    newItem.value[VALUE_SZ - 1] = '\0';


    int arrIndex = hash(inputKey) % STORAGE_SZ;



    storage[arrIndex] = newItem;



    return 0;

}