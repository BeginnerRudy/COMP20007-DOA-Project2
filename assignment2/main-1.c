#include <stdio.h>
#include "LevenshteinEdit.h"

#define MAXCHARLENGTH 20

int
main(int argc, char* argv[]){
    char s1[MAXCHARLENGTH], s2[MAXCHARLENGTH];
    int editDist;
    printf("What are the two strings you want to compute Levenshtein distance? Please enter. \n");
    scanf("%s%s", s1, s2);
    editDist = LevenshteinEdit(s1, s2);
    printf("The Leveshtein Edit distance between %s and %s is %d.", s1, s2, editDist);
    return 0;
}