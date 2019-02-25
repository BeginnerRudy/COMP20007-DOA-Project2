/* * * *  * * * * * * * * * * * * * *
 * 2018/04.16 18:40 Mon
 * By renjie Meng
 * mrj9990123@gmail.com
 * For practicing and understanding of how Levenshtein edit distance work
 */


#include <stdio.h>
#include <string.h>
#include "LevenshteinEdit.h"
#include "windows.h"
#include <stdlib.h>

int
LevenshteinEdit(char* s1, char* s2){
    int len1 = strlen(s1), len2 = strlen(s2), dp[len1+1][len2+1], p;
    memset(dp, 0, sizeof(dp[0][0])*(len1+1)*(len2+1)); // initialize dp to zero matrix
    // compute string with none respectively
    for (int j=1; j<=len2; j++){
        dp[0][j] = dp[0][j-1] + c;
    }
    for (int i=1; i<=len1; i++){
        dp[i][0] = dp[i-1][0] + c;
    }
    // main part
    for (int i=1; i<=len1; i++){
        for (int j=1; j<=len2; j++){
            if (s1[i-1] == s2[j-1]){
                p = 0;
            }else{
                p = c;
            }

            dp[i][j] = min_opeartion(dp[i-1][j-1]+p,
                                     dp[i-1][j] + c,
                                     dp[i][j-1] + c);
        }
    }

    // print stage
    
    // formatting and edit dist print

    // SetConsoleOutputCP(1253); //"ANSI" Greek
    // printf("\xE3\xE5\xE9\xDC \xF3\xEF\xF5");

    printf("Note: '#' denote the empty string.\n");

    printf(" |%2c|", '#');
    for (int i=0; i<len2; i++){
        printf("%2c|", s2[i]);
    }

    // print_horizontal_line(2+(len2+1)*3); 

    printf("\n%c|", '#');
    for (int j=0; j<=len2; j++){
        printf("%2d|", dp[0][j]);
    }
    for (int i= 1; i<=len1; i++){
        // print_horizontal_line(2+(len2+1)*3); 
        printf("\n");
        printf("%c|", s1[i-1]);
        for (int j=0; j<=len2; j++){
            printf("%2d|", dp[i][j]);
        }
    }
    printf("\n\n");


    // print the alignment out

    // return the edit distance
    return dp[len1][len2];
}

int
min_opeartion(int d1, int d2, int d3){
    int min;
    if ((d1-d2<=0)&&(d1-d3<=0)){
        min = d1;
    }else if ((d2-d1<=0)&&(d2-d3<=0)){
        min = d2;
    }else if ((d3-d1<=0)&&(d3-d2<=0)){
        min = d3;
    }
    return min;
}

void print_horizontal_line(int num){
    printf("\n");
    for (int i=0; i<num; i++){
        printf("=");
    }
}

void print_matrix(int* dp){
    // int width = sizeof(dp[0])/sizeof(dp[0][0]),
    // length = sizeof(dp)/sizeof(dp[0]);

    // for (int i=0; i<length; i++){
    //     printf("\n");
    //     for (int j=0; j<width; j++){
    //         printf("%d", dp[i][j]);
    //     }
    // }
}


int alignment_actioin(int left, int above, int top_left_conner){
    int action;
    if ((left-above<=0)&&(left-top_left_conner<=0)){
        action = DELETE;
    }else if ((above-left<=0)&&(above-top_left_conner<=0)){
        action = INSERT;
    }else if ((top_left_conner-left<=0)&&(top_left_conner-above<=0)){
        action = MODIFY_OR_MATCHED;
    }
    return action;    
}

string_alignment_array_t*
new_string_alignment_array(int size_of_aligned_string){
    string_alignment_array_t* new;
    new = (string_alignment_array_t*)malloc(sizeof(*new));
    new.aligned_string = (char*)malloc*(sizeod(char)*size_of_aligned_string);
    new.curr_size = 0;
    return new;
    }