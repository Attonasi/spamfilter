#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"

int main(int argc, char const *argv[]) {

    const char* spam_dir = argv[DATA_DIRECTORY_SPAM_POS];
    const char* ham_dir = argv[DATA_DIRECTORY_HAM_POS];

    char* spam_files[MAX_NUM_FILES];
    char* ham_files[MAX_NUM_FILES];

//    Word* library[MAX_LIBRARY_WORDS];
    printf("Argv[1]: %s\n", spam_dir);
    printf("Argv[2]: %s\n", ham_dir);
    printf("Argv[0]: %s\n", argv[0]);

    int num_spam_files = get_files(spam_dir, spam_files);
    int num_ham_files = get_files(ham_dir, ham_files);

    printf("Number of Spam Files: %d Number of Ham Files: %d\n", num_spam_files, num_ham_files);
    return 0;
}