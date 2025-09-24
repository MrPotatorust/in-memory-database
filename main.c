#include <stdlib.h>
#include <stdio.h>


#define STORAGE_SZ 100;

int main(int argc, char* argv[]){
    
    while (1)
    {

    }
    
}




// djb2 hash algorithm
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
