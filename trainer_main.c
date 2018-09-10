#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"

int main(int argc, char const *argv[]) {

    char* files[MAX_NUM_FILES];
    Word* library[MAX_LIBRARY_WORDS];


    int num_files = get_files(argv[DATA_DIRECTORY_ARG_POS], files);


    printf("Hello, World!\n");
    return 0;
}