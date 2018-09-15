#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"

int main(int argc, char const *argv[]) {

    const char* spam_dir = argv[DATA_DIRECTORY_SPAM_POS];
    const char* ham_dir = argv[DATA_DIRECTORY_HAM_POS];
    const char* test_spam_dir = argv[DATA_DIRECTORY_TEST_SPAM_POS];
    const char* test_ham_dir = argv[DATA_DIRECTORY_TEST_HAM_POS];
    const char* lib_path = "./library/library.txt";
    const char* assignment_path = "./library/assignment_trainer.txt";
    const char* test_assign_path1 = "./library/test_assignment_spam.txt";
    const char* test_assign_path2 = "./library/test_assignment_ham.txt";
    const char* report_path = "./library/report_trainer.txt";
    const char* test_report_path1 = "./library/test_report_spam.txt";
    const char* test_report_path2 = "./library/test_report_ham.txt";

    char* spam_files[SPAM_EMAILS];
    char* ham_files[HAM_EMAILS];
    char* test_spam_files[TEST_EMAILS];
    char* test_ham_files[TEST_EMAILS];

    Library* lib = create_library();
    Report* rep = create_report();
    Report* test_ham = create_report();
    Report* test_spam = create_report();

    int num_spam_files = get_files(spam_dir, spam_files);
    int num_ham_files = get_files(ham_dir, ham_files);

    for(int i = 0; i < num_spam_files; i++){
        read_email(spam_files[i], lib, SPAM);
        read_email(ham_files[i], lib, HAM);
    }
    printf("Number of Spam Files: %d Number of Ham Files: %d Num_lib_words: %d \n", num_spam_files, num_ham_files, lib->num_lib_words);

    for(int i = rep->num_classifications; i < num_ham_files; i++){
        rep->report_repo[i] = create_classification(lib, spam_files[i], SPAM);

        if(rep->report_repo[i]->classification_code == CORRECT_HAM){
            rep->correct_ham++;
        } else if (rep->report_repo[i]->classification_code == CORRECT_SPAM){
            rep->correct_spam++;
        } else if (rep->report_repo[i]->classification_code == HAM_MARKED_SPAM){
            rep->spam_marked_ham++;
        } else if (rep->report_repo[i]->classification_code == SPAM_MARKED_HAM){
            rep->spam_marked_ham++;
        } else {
            printf("damnit");
        }

        rep->num_classifications++;
    }
    printf("Num spam classifications: %d\n", rep->num_classifications);

    for(int i = rep->num_classifications; i < TOTAL_EMAILS; i++){
        rep->report_repo[i] = create_classification(lib, ham_files[i-num_spam_files], HAM);

        if(rep->report_repo[i]->classification_code == CORRECT_HAM){
            rep->correct_ham++;
        } else if (rep->report_repo[i]->classification_code == CORRECT_SPAM){
            rep->correct_spam++;
        } else if (rep->report_repo[i]->classification_code == HAM_MARKED_SPAM){
            rep->spam_marked_ham++;
        } else if (rep->report_repo[i]->classification_code == SPAM_MARKED_HAM){
            rep->spam_marked_ham++;
        } else {
            printf("ugh");
        }

        rep->num_classifications++;
    }
    printf("Num ham classifications: %d\n", rep->num_classifications);

    int num_test_spam_files = get_files(test_spam_dir, test_spam_files);

    for (int j = 0; j < num_test_spam_files; j++) {
        test_spam->report_repo[j] = create_classification(lib, test_spam_files[j], SPAM);

        if(test_spam->report_repo[j]->classification_code == CORRECT_HAM){
            test_spam->correct_ham++;
        } else if (test_spam->report_repo[j]->classification_code == CORRECT_SPAM){
            test_spam->correct_spam++;
        } else if (test_spam->report_repo[j]->classification_code == HAM_MARKED_SPAM){
            test_spam->spam_marked_ham++;
        } else if (test_spam->report_repo[j]->classification_code == SPAM_MARKED_HAM){
            test_spam->spam_marked_ham++;
        } else {
            printf("...");
        }
        test_spam->num_classifications++;
    }
    printf("Num test spam classifications: %d\n", test_spam->num_classifications);

    int num_test_ham_files = get_files(test_ham_dir, test_ham_files);

    for (int j = 0; j < num_test_ham_files; j++) {
        test_ham->report_repo[j] = create_classification(lib, test_ham_files[j], HAM);

        if(test_ham->report_repo[j]->classification_code == CORRECT_HAM){
            test_ham->correct_ham++;
        } else if (test_ham->report_repo[j]->classification_code == CORRECT_SPAM){
            test_ham->correct_spam++;
        } else if (test_ham->report_repo[j]->classification_code == HAM_MARKED_SPAM){
            test_ham->spam_marked_ham++;
        } else if (test_ham->report_repo[j]->classification_code == SPAM_MARKED_HAM){
            test_ham->spam_marked_ham++;
        } else {
            printf("!!!");
        }

        test_ham->num_classifications++;
    }
    printf("Num test ham classifications: %d\n", test_ham->num_classifications);

//    print_report(rep);
    write_report(rep, report_path);
    printf("Trainer data report written\n");
    write_report(test_spam, test_report_path1);
    printf("Test spam report written\n");
    write_report(test_ham, test_report_path2);
    printf("Test spam report written\n");

    write_assignment_format(rep, assignment_path);
    printf("Assignment trainer data report written\n");
    write_assignment_format(test_spam, test_assign_path1);
    printf("Assignment test spam report written\n");
    write_assignment_format(test_ham, test_assign_path2);
    printf("Assignment test ham report written\n");

//    print_lib(lib);
    write_library(lib, lib_path);
    printf("Library Written\n");

//  FREE STUFF END FILTER
    for(int i = 0; i < lib->num_lib_words; i++){
        free(lib->library[i]);
    }
    free(lib);
    for(int i = 0; i < TOTAL_EMAILS; i++){
        free(rep->report_repo[i]);
    }
    free(rep);
    for(int i = 0; i < TEST_EMAILS; i++){
        free(test_ham->report_repo[i]);
        free(test_spam->report_repo[i]);
    }
    free(test_ham);
    free(test_spam);
    return 0;
}