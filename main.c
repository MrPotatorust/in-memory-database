#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char test[] = "12345";

    for (int i = 0; i < strlen(test); i++)
    {

        printf("Test%i, %i \n", i, test[i]);

        switch (test[i] )
        {
        case 48:
            return 0;
            break;
        case 49:
            return 1;
            break;
        case 50:
            return 2;
            break;
        case 51:
            return 3;
            break;
        case 52:
            return 4;
            break;
        case 53:
            return 5;
            break;
        case 54:
            return 6;
            break;
        case 55:
            return 7;
            break;
        case 56:
            return 8;
            break;
        case 57:
            return 9;
            break;
        default:
            return -1;
            break;
        }
    }

    return 0;
}