/* * * *  * * * * * * * * * * * * * *
 * 2018/04.16 18:40 Mon
 * By renjie Meng
 * mrj9990123@gmail.com
 * For practicing and understanding of how Levenshtein edit distance work
 */

// constant define
#define c 1 //cost per operation
#define ALIGNMENT_SIGN '_'
#define INSERT 1
#define DELETE 2
#define MODIFY_OR_MATCHED 3
typedef struct{
    int coordinate[2]; // [horizontal coordinate, vertical coordinate]
}coordinate_t;

typedef struct{
    char* aligned_string; // the string which has been modifief to align
    int curr_size;
    // int max_size;
}string_alignment_array_t;

// Function prototype
int LevenshteinEdit(char* s1, char* s2);
int min_opeartion(int d1, int d2, int d3);
void print_matrix(int*);
void print_horizontal_line(int num);
int alignment_actioin(int left, int above, int top_left_conner);
string_alignment_array_t* new_string_alignment_array(int size_of_aligned_string);