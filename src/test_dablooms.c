#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "dablooms.h"

int test_counting_remove_reopen(void)
{
	counting_bloom_t *bloom;
    int i, j;
   
    
    printf("\n* test counting remove & reopen\n");
 
    if (!(bloom = new_counting_bloom(CAPACITY, ERROR_RATE))) {
        fprintf(stderr, "ERROR: Could not create bloom filter\n");
        return TEST_FAIL;
    }


/*
printf("start bloom add\n");

char s[3][10];
for(i = 0; i < 3; i++) {
	printf("add %d of 3 elements: ", i);
	scanf("%s", s[i]);
	s[i][strlen(s[i])] = '\0';
	printf("length of (%s) = %d", s[i], (int) strlen(s[i]));
	if (!counting_bloom_add(bloom, s[i], strlen(s[i]))) //by xp: add successful
		printf(", add successful.\n");
	else
		printf(".\nError! add failed.");
}

printf("start bloom check\n");

for(i = 0; i < 3; i++) {
	j = counting_bloom_check(bloom, s[i], strlen(s[i]));
	if (j) { //by xp: in this filter
		printf("%s is checked.\n", s[i]);
	}
	else {
		printf("%s is NOT found.\n", s[i]);
	}
	bloom_score(j, 1, & (bloom->counting_stats), s[i]);
}

printf("start bloom remove\n");

for(i = 0; i < 3; i++) {
	if(!counting_bloom_remove(bloom, s[i], strlen(s[i]))) //by xp: remove successful
		printf("%s is removed.\n", s[i]);
	else
		printf("%s is NOT removed.\n", s[i]);
}
*/

char s[20];
int elements_added = 0, elements_removed = 0;

printf("start bloom add\n");
while(scanf("%s", &s), strcmp(s, "END") != 0) {
	printf("length of (%s) = %d", s, (int) strlen(s));

	if (!counting_bloom_add(bloom, s, strlen(s))) {//by xp: add successful
		elements_added++;
		printf(", add successful.\n");
	}
	else
		printf(".\nError! add failed.\n");
}

printf("start bloom check\n");
	while(scanf("%s", &s), strcmp(s, "END") != 0) {
		j = counting_bloom_check(bloom, s, strlen(s));
		if (j) { //by xp: in this filter
			printf("%s is checked.\n", s);
		}
		else {
			printf("%s is NOT found.\n", s);
		}
		bloom_score(j, 1, & (bloom->counting_stats), s);
	}

printf("start bloom remove\n");
	while(scanf("%s", &s), strcmp(s, "END") != 0) {
		j = counting_bloom_check(bloom, s, strlen(s));
		if (j) { //by xp: in this filter
			elements_removed++;
			printf("%s is removed.\n", s);
		}
		else {
			printf("%s is NOT removed.\n", s);
		}
	}



    
    printf("Elements added:   %6d" "\n"
           "Elements removed: %6d" "\n"
           "Total size: %d KiB"  "\n\n",
           elements_added, elements_removed,
           (int) bloom->num_bytes / 1024);
           
    free_counting_bloom(bloom);
    
    return print_results(&(bloom->counting_stats));
}

int main(int argc, char *argv[])
{
    printf("** dablooms version: %s\n", dablooms_version());

    int failures = 0, warnings = 0;
	int retValue;
 /* 
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <bloom_file> <words_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
*/
	retValue = test_counting_remove_reopen ();
    if(retValue== TEST_FAIL) {
		failures++;
    } else if(retValue == TEST_WARN) {
		    warnings++;
	       }
    printf("\n** %d failures, %d warnings\n", failures, warnings);

	
    if (failures) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}
