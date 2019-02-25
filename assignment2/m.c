#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char* argv[]){
    char* s1 = "international";
    char *cpy[20];

    memcpy(cpy, s1, 5);
    memcpy(cpy+1, s1+7, 4);
    cpy[9] = '\0';
    printf("%s\n", cpy);
    return 0;
}