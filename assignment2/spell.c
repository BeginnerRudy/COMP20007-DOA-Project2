/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *														   *
 * 			COMP20007 Design of Algorithms 2017 S1		   *
 *  		  Assignment 2 - Spelling correction		   *
 * 														   *
 * 					    Date: 2018-05-20				   *
 * 														   *
 * 			    Student Name: Renjie(Rudy) Meng			   *
 * 				Student ID: 877396						   *
 * 				Email: renjiem@student.unimelb.edu.au	   *
 *  					                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "spell.h"


// additional function which compute Levehshtein edit distance between two words
// Support task 1
// Argument: char* word1, char* word2
// Return: Levenshtein edit distance between word1 and word2
int Levehshtein_Edit_Distance(char *word1, char *word2){
	// Initialization
	int len1 = strlen(word1), len2 = strlen(word2), 
	dp[len1+1][len2+1], p, c = 1, // c is the cost of insertion and deletion operation, p is the penalty
	min, d1, d2, d3; // min stands for minimum cost among all three operation
					 // d1 stands for cost of modify, 
					 // d2 stands for cost of deletion, 
					 // d3 stands for cost of insertion

    memset(dp, 0, sizeof(dp[0][0])*(len1+1)*(len2+1)); // initialize dp to zero matrix


	// Construct Levenstein Edit Distance Matrix

    // compute edit distance of between empty string and word1 and word2 respectively
    for (int j=1; j<=len2; j++){
        dp[0][j] = dp[0][j-1] + c;
    }
    for (int i=1; i<=len1; i++){
        dp[i][0] = dp[i-1][0] + c;
    }
	
    // main part for computing edit distance 
    for (int i=1; i<=len1; i++){
        for (int j=1; j<=len2; j++){
            if (word1[i-1] == word2[j-1]){ // subsitue which cost 0 because of modify
                p = 0;
            }else{
                p = c;// insert and delete with cost 1
            }
			// chose edit operation with min cost
			d1 = dp[i-1][j-1] + p;
			d2 = dp[i-1][j] + c;
			d3 = dp[i][j-1] + c;
			if ((d1-d2<=0)&&(d1-d3<=0)){
				min = d1;
			}else if ((d2-d1<=0)&&(d2-d3<=0)){
				min = d2;
			}else if ((d3-d1<=0)&&(d3-d2<=0)){
				min = d3;
			}
			// assign edit distance for string(0,j) and string(0, i)
            dp[i][j] = min;
        }
    } 
	// return the minimum steps of operation needed
	return dp[len1][len2];
}


// additional function which compute only compute less 3 Levenshtein edit distance and FOUR
// Support task 3
// Argument: char* word1, char* word2
// Return: Levenshtein edit distance less than 3 between word1 and word2 OR FOUR
int Levehshtein_Edit_Distance_Less_T_3(char *word1, char *word2){
	/* * * * *
	 * This function is used for task 4 in order to find Levenshtein edit distance less than 4
	 * between doc_word and dic_word.
	 * 
	 * At first, we can confirm that if two words differ in length more than 3, then the Levenshtein
	 * edit distance would certainly be large than 3, thus return FOUR
	 * 
	 * Then, we if the min of row of dynamic programming matrix is greater, then the edit distance 
	 * will be large than 3 certainly. Since the each entry in next row will be larger than or equal
	 * than the entry above it. Thus, return FOUR
	 * * * * */
 
	// Initialization
	int len1 = strlen(word1), len2 = strlen(word2), 
	dp[len1+1][len2+1], p, c = 1, // c is the cost of insertion and deletion operation, p is the penalty
	min,// min stands for minimum cost among all three operation
	d1, // d1 stands for cost of modify, 
	d2, // d2 stands for cost of deletion, 
	d3, // d3 stands for cost of insertion
	min_cost_per_row = FOUR; // min_cost_per_row stands for the minimum edit distance in each row
    memset(dp, 0, sizeof(dp[0][0])*(len1+1)*(len2+1)); // initialize dp to zero matrix

	// if the difference of length of two words is greater than 3
	// the Levenshteien edit distance is greater than 3 certainly
	if (abs(len1 - len2)>3){
		return FOUR;
	}


	// Construct Levenstein Edit Distance Matrix

    // compute edit distance of between empty string and word1 and word2 respectively
    for (int j=1; j<=len2; j++){
        dp[0][j] = dp[0][j-1] + c;
    }
    for (int i=1; i<=len1; i++){
        dp[i][0] = dp[i-1][0] + c;
    }
	
    // main part for computing edit distance 
    for (int i=1; i<=len1; i++){
		min_cost_per_row = FOUR;
        for (int j=1; j<=len2; j++){
            if (word1[i-1] == word2[j-1]){ // subsitue which cost 0 because of modify
                p = 0;
            }else{
                p = c;// insert and delete with cost 1
            }
			// chose edit operation with min cost
			d1 = dp[i-1][j-1] + p;
			d2 = dp[i-1][j] + c;
			d3 = dp[i][j-1] + c;
			if ((d1-d2<=0)&&(d1-d3<=0)){
				min = d1;
			}else if ((d2-d1<=0)&&(d2-d3<=0)){
				min = d2;
			}else if ((d3-d1<=0)&&(d3-d2<=0)){
				min = d3;
			}
			// assign edit distance for string(0,j) and string(0, i)
            dp[i][j] = min;
			// Find min cost for each row
			if (min < min_cost_per_row){
				min_cost_per_row = min;
			}
        }
		// Decide if terminate or not
		if (min_cost_per_row == FOUR){
			// if the cost of all modify is greater than 3
			// than the edit distance will be larger than 3 
			// we only need dist < = 3
			// thus no need to do further computation
			// return  FOUR
			return FOUR;
		}
    }
	// return the minimum steps of operation needed
	return dp[len1][len2];
}


// A helper function to create a Hash Table of Dictionary
// Support task3 and 4
HashTable *To_Hash_Table_Dictionary(List *dictionary){
	char* dic_word;
	Node* dic_node = dictionary->head;
	HashTable * HashTable;

	// Establish a hash table
	HashTable = new_hash_table((4*dictionary->size)/3);
	while (dic_node != NULL){
		dic_word = dic_node->data;
		dic_node = dic_node->next;
		hash_table_put(HashTable, dic_word, 1);
	}
	free(dic_node);
	free(dic_word);
	return HashTable;
}


// A helper function to generate all Levenshtein edit distance 1 of word
// support task 2
word_list_t* all_edits(char *word){
		/* * * * * * * * * * * *
	 * This function is consisted of three main blocks
	 * In addition, this function mainly use memcpy in string.h to deal with edit operation
	 * Block 1: Delete one char from original string
	 * Block 2: Modify one char from original string
	 * Block 3: Insert one char into original string
	 * * * * */

	// Initialization
	int len = strlen(word),
		// for deletion, 
		// I would split the word into left and right parts
		Left_End_Index, // Index of last char of left part of word
		Right_Start_Index, // Index of first char of right part of word
		count = 0; // count the number of edited word 

	char edit_1_deletion[len - 1],  // string used to store 1-char deleted string
		 edit_1_insertion[len+1],   // string used to store 1-char modified string
		 edit_1_modification[len];  // string used to store 1-char inserted string

	word_list_t *all_edits;
	
	all_edits = (word_list_t*)malloc(sizeof(word_list_t*));
	all_edits->all_words = (char**)malloc(sizeof(char**)*(53*len+26));
	all_edits->size = 53*len+26;
	
	// There will be len words after deletion, 26*len words after modification
	// 26*(len + 1) words after insertion. Thus, overall, there will be
	// 53*len + 26 words in total

	// Block 1:  Deletion of 1 char

	for (int i=len -1; i>= 0 ; i--){
		// Idea:
		// 		delete ith char by skipping it (not copy it)
		// 		then copy left and right part of i th char into edit_1_deletion;

		// Skip the i th char in word
		Left_End_Index = i - 1;
		Right_Start_Index = i + 1;

		// copy chars in the left of i th char
		if (Left_End_Index >= 0){
			memcpy(edit_1_deletion, word, Left_End_Index+1); 
			// Left_End_Index+1 to get the number of chars to copy
		}
		
		// copy chars in the right of i th char
		if (Right_Start_Index <= len){
			memcpy(&edit_1_deletion[Left_End_Index + 1], // offset with Left_End_Index + 1
			&word[Right_Start_Index], // offset with Right_Start_Index
			len -  Right_Start_Index + 1); // +1 to include the null byte
		}else{
			// if the Right_Start_Index larger than the length of word -> REPORT ERROR
			printf("WARNING: SOMETHING WRONG IN DELETING EDIT. INDEX OUT OF RANGE!!!\n");
		}
		
		// store the word
		all_edits->all_words[count] = (char*)malloc(sizeof(char*)*(len));
		memcpy(all_edits->all_words[count], edit_1_deletion, len);
		count++;
	}
	
	
	// Block 2:  Modify 1 char


	for (int i=0; i<len; i++){
		// Modify the i th char with 26 alphabetic letter respectively
		memcpy(edit_1_modification, word, len+1);// +1 to include the null byte
		for (int j=97; j<=122; j++){
			// modify
			edit_1_modification[i] = j;
			// store the word
			all_edits->all_words[count] = (char*)malloc(sizeof(char*)*(len+1));
			memcpy(all_edits->all_words[count], edit_1_modification, len+1);
			count++;
		}
	}


	// Block 3: Insertion of 1 char


	// insert in front of each char
	for (int i=0; i<len; i++){
		Left_End_Index = i;
		Right_Start_Index = i + 1;
		// copy left part of word
		memcpy(edit_1_insertion, word, Left_End_Index);

		// len - Left_End_Index + 1 to copy the null byte
		// Right_Start_Index = Left_End_Index + 1 -aim to - > +1 to make space for insertion
		memcpy(&edit_1_insertion[Right_Start_Index], &word[Left_End_Index], len - Left_End_Index + 1); 

		for (int j=97; j<=122; j++){
			// insert 26 alphabetic letter respectively
			memcpy(&edit_1_insertion[Left_End_Index], &j, 1);
			// store the word
			all_edits->all_words[count] = (char*)malloc(sizeof(char*)*(len + 2));
			memcpy(all_edits->all_words[count], edit_1_insertion, len + 2);
			count++;
		}
	}

	// insert in the back of last char
	memcpy(edit_1_insertion, word, len);
	for (int i=97; i<=122; i++){
		memcpy(&edit_1_insertion[len], &i, 1);
		// store the word
		all_edits->all_words[count] = (char*)malloc(sizeof(char*)*(len + 2));
		memcpy(all_edits->all_words[count], edit_1_insertion, len + 2);
		count++;
	}
	return all_edits;
}


// see Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2) {
	// print out the Levenshtein Edit Distance between word 1 and word 2
	printf("%d\n", Levehshtein_Edit_Distance(word1, word2));
}


// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {
	word_list_t* all_edits_word;
	all_edits_word = all_edits(word);
	for (int i = 0; i < all_edits_word -> size; i++){
		// print edited string
		printf("%s\n", all_edits_word->all_words[i]);
		free(all_edits_word->all_words[i]);
	}
	free(all_edits_word);
}


// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	bool is_in_dic = False; // True for word in dic; False for word not in dic
	char* doc_word;
	Node* doc_node = document->head;
	HashTable * HashTable;

	// Establish a hash table
	HashTable = To_Hash_Table_Dictionary(dictionary);

	// check exitance
	while (doc_node != NULL){
		// traverse all words in the doc
		doc_word = doc_node->data;
		doc_node = doc_node->next;
		if ((is_in_dic = hash_table_has(HashTable, doc_word)) == True){
			// word in the dic
			printf("%s\n", doc_word);
		}else{
			// word not in the dic
			printf("%s?\n", doc_word);
		}
	}
	// free pointers
	free_hash_table(HashTable);
	free(doc_node);
	free(doc_word);
}


// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	// Initialization
	HashTable *HashTable1;

	int distance = 0, // var to store Levenshtein edit distance
	has_edit_1 = 0;   // indicator - 1 indicates word has 1-edit distance word in dic
					  // - 0 stands for does not have

	char* doc_word, *dic_word, 
	*dist_2 = NULL, // var to store first word in dic has 2 edit distance with word in doc
	*dist_3=NULL;   // var to store first word in dic has 3 edit distance with word in doc

	Node* doc_node = document->head, *dic_node = dictionary->head;

	// Establish a HashTable Version of Dictionary
	HashTable1 = To_Hash_Table_Dictionary(dictionary);

	// Spelling Correction
	while (doc_node != NULL){
		// traverse the document
		doc_word = doc_node->data;
		doc_node = doc_node -> next;
		// initialize var to null and 0
		has_edit_1 = 0;
		dist_2 = NULL;
		dist_3 = NULL;

		// Start correction
		if (hash_table_has(HashTable1, doc_word)){
			// the word is in dic, print out
			printf("%s\n", doc_word);
		}else{
			dic_node = dictionary->head;
			while(dic_node!=NULL){
				// traverse the dic to search for correction for each word in doc
				dic_word = dic_node->data;
				dic_node = dic_node->next;
				distance = Levehshtein_Edit_Distance_Less_T_3(dic_word, doc_word);
				if (distance == 1){
					// doc_word has word in dic with edit distance 1, print out then break
					printf("%s\n", dic_word);
					has_edit_1 = 1; // assign indicator to be 1
					break;
				}else if (distance == 2 && dist_2 == NULL){
					// store first word in dic with edit distance of 2
					dist_2 = dic_word;
				}else if (distance == 3 && dist_3 == NULL){
					// store first word in dic with edit distance of 3
					dist_3 = dic_word;
				}
			}
			
			if (has_edit_1){ // already print out
				//pass
			}else if (dist_2 != NULL){
				// print out word with edit distance of 2
				printf("%s\n", dist_2);
			}else if (dist_3 != NULL){
				// print out word with edit distance of 3
				printf("%s\n", dist_3);
			}else{
				// print out word cannot find correction
				printf("%s?\n", doc_word);
			}
		}
	}
	free_hash_table(HashTable1);	
}