/* * * * * * *
 * Module for functions that solve the coding tasks from assignment 2
 * 
 * created for COMP20007 Design of Algorithms - Assignment 2, 2018
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 */

#ifndef SPELL_H
#define SPELL_H
#define False 0
#define True 1
#define FOUR 4


#include "list.h"
#include "hashtbl.h"

/*                         DO NOT CHANGE THIS FILE
 * 
 * DO NOT modify function prototypes: you must implement these functions exactly
 * DO NOT add your own function prototypes or other definitions; put additional
 * definitions in spell.c instead
 *
 * We will test your assignment with an unmodified version of this file. Any
 * changes you make will be lost. This may lead to compile errors.
 */

typedef struct{
    char** all_words;
    int size;
}word_list_t;

// A helper function used to compute Levenshtein edit distance for two words
// Support for task1
// Argument: char* word1, char* word2
// Return: Levenshtein edit distance between word1 and word2
int Levehshtein_Edit_Distance(char *word1, char *word2);

// A helper function used to compute Levenshtein edit distance less than 4 for two words
// Support for task4
int Levehshtein_Edit_Distance_Less_T_3(char *word1, char *word2);

// A helper function to create a Hash Table
// Support task3 and 4
HashTable *To_Hash_Table_Dictionary(List *dictionary);

// A helper function to generate all Levenshtein edit distance 1 of word
// support task 2
word_list_t* all_edits(char *word);

// see Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2);

// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word);

// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document);

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document);

#endif