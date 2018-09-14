#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"

int main(int argc, char const *argv[]) {

    const char* spam_dir = argv[DATA_DIRECTORY_SPAM_POS];
    const char* ham_dir = argv[DATA_DIRECTORY_HAM_POS];
    const char* lib_path = "./library/library.txt";
    const char* report_path = "./library/report.txt";
    const char* assignment_path = "./library/assignment1.txt";
    const char* test_assign_path = "./library/test_assignment1.txt";
    const char* test_report_path = "./library/test_report.txt";
    const char* test_dir = argv[DATA_DIRECTORY_TEST_POS];

    char* spam_files[SPAM_EMAILS];
    char* ham_files[HAM_EMAILS];
    char* test_files[TEST_EMAILS];

    Library* lib = create_library();
    Report* rep = create_report();
    Report* test = create_report();

    int num_spam_files = get_files(spam_dir, spam_files);
    int num_ham_files = get_files(ham_dir, ham_files);

    for(int i = 0; i < num_spam_files; i++){
        read_email(spam_files[i], lib, SPAM);
        read_email(ham_files[i], lib, HAM);
    }
    printf("Number of Spam Files: %d Number of Ham Files: %d Num_lib_words: %d \n", num_spam_files, num_ham_files, lib->num_lib_words);

    for(int i = rep->num_classifications; i < num_ham_files; i++){
        rep->report_repo[i] = create_classification(lib, spam_files[i], SPAM);
        rep->num_classifications++;
    }
    printf("Num classifications: %d\n", rep->num_classifications);

    for(int i = rep->num_classifications; i < TOTAL_EMAILS; i++){
        rep->report_repo[i] = create_classification(lib, ham_files[i-num_spam_files], HAM);
        rep->num_classifications++;
    }
    printf("Num classifications: %d\n", rep->num_classifications);

    int num_test_files = get_files(test_dir, test_files);

    for (int j = 0; j < num_test_files; j++) {
        test->report_repo[j] = create_classification(lib, test_files[j], TEST);
        test->num_classifications++;
    }

//    print_report(rep);
    write_report(rep, report_path);
    write_report(test, test_report_path);
    write_assignment_format(rep, assignment_path);
    write_assignment_format(test, test_assign_path);

//    print_lib(lib);
    write_library(lib, lib_path);

//  FREE STUFF END FILTER
    for(int i = 0; i < lib->num_lib_words; i++){
        free(lib->library[i]);
    }
    free(lib);
    for(int i = 0; i < TOTAL_EMAILS; i++){
        free(rep->report_repo[i]);
    }
    free(rep);
    return 0;
}