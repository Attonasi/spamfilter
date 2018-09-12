#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"

int main(int argc, char const *argv[]) {

    const char* spam_dir = argv[DATA_DIRECTORY_SPAM_POS];
    const char* ham_dir = argv[DATA_DIRECTORY_HAM_POS];
    const char* lib_path = "./library/library.txt";
    const char* report_path = ".library/report.txt";

    char* spam_files[MAX_NUM_FILES];
    char* ham_files[MAX_NUM_FILES];

    Library* lib = create_library();
    Report* rep = create_report();

    int num_spam_files = get_files(spam_dir, spam_files);
    int num_ham_files = get_files(ham_dir, ham_files);

//    char option;

    for(int i = 0; i < 10; i++){
        read_email(spam_files[i], lib, SPAM);
        read_email(ham_files[i], lib, HAM);
        printf("Number of Spam Files: %d Number of Ham Files: %d Num_lib_words: %d i: %d\n", num_spam_files, num_ham_files, lib->num_lib_words, i);
    }

//    read_email(spam_files[0], lib, SPAM);
//    print_lib(lib);
    printf("Number of Spam Files: %d Number of Ham Files: %d Num_lib_words: %d \n", num_spam_files, num_ham_files, lib->num_lib_words);

    rep->report_repo[0] = create_classification(lib, spam_files[0], SPAM);
    rep->num_classifications++;

    print_report(rep);
    write_report(rep, report_path);

    write_library(lib, lib_path);
//    print_lib(lib);
//  FREE STUFF END TRAINER
    for(int i = 0; i < lib->num_lib_words; i++){
        free(lib->library[i]);
    }
    free(lib);
    return 0;
}