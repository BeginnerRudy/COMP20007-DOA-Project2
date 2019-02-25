
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 128

int
main(int argc, char *argv[]) {
	// receive and read file from command line
	FILE *t1 = fopen(argv[1], "r");
	FILE *t2 = fopen(argv[2], "r");
	assert(t1);
	assert(t2);

	char *w1 = malloc(MAX*sizeof(*w1));
	char *w2 = malloc(MAX*sizeof(*w2));
	int found_diff = 0;
	while(1) {
		if (fgets(w1, MAX, t1) == NULL  || fgets(w2, MAX, t2) == NULL) {
			if (fgets(w1, MAX, t1)  == NULL && fgets(w2, MAX, t2) == NULL){
				break;
			}
			if (fgets(w1, MAX, t1)  == NULL){
				if (fgets(w2, MAX, t2) != NULL){
					found_diff = 1;
					printf("Different!!!!!!\n");
					printf("Two text files are not of the same length.\n");
					printf("Text2 is longer than text1.\n");
					break;
				}
			}
			if (fgets(w2, MAX, t2) == NULL){
				if (fgets(w1, MAX, t1) != NULL){
					found_diff = 1;
					printf("Different!!!!!!\n");
					printf("Two text files are not of the same length.\n");
					printf("Text1 is longer than text2.\n");
					break;
				}
			}
		}
		if (strcmp(w1, w2) != 0) {
			found_diff = 1;
			printf("%s", w1);
			printf("!= %s\n", w2);
			printf("different!!!\n");
			break;
		}
	}
	if (!found_diff) {
		printf("all the same!!\n");
	}
	free(w1);
	free(w2);
	fclose(t1);
	fclose(t2);
	return 0;
}