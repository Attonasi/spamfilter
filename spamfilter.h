#ifndef SPAMFILTER_H
#define SPAMFILTER_H

#define MAX_NUM_FILES 500
#define TOTAL_EMAILS 1000
#define MAX_LIBRARY_WORDS 30000
#define MAX_WORD_SIZE 400
#define EMAIL_PATH_SIZE 30

#define NEW_LINE 10

#define DATA_DIRECTORY_SPAM_POS 1
#define DATA_DIRECTORY_HAM_POS 2

#define HAM 0
#define SPAM 1
#define TEST 2

typedef struct dirent Dirent_t;

typedef struct Word{
    char word[MAX_WORD_SIZE];
    int index;
    int email_flag;
    int spam_count;
    int spam_num_emails;
    int ham_count;
    int ham_num_emails;
    float spam_ratio;
    float ham_ratio;

} Word;

typedef struct Library{
    Word* library[MAX_LIBRARY_WORDS];
    int num_lib_words;
    int lib_compare;
} Library;

typedef struct Classification {
    char email[EMAIL_PATH_SIZE];
    double spam_value;
    double ham_value;
    int ham_or_spam_or_test;
    int ham_or_spam_classifier;
} Classification;

typedef struct Report {
    Classification* report_repo[TOTAL_EMAILS];
    int num_classifications;
} Report;

/**
This function takes a pointer to a directory and creates a list of filenames
that exist in that directory.

param: const char* directory to open and get filenames from.
param: char** files pointer to array of strings we are storing file names in

return: Number of files.
*/
int get_files(const char* directory, char** files);

Library* create_library();

/**
 * This function creates a pointer to a Word struct with information
 * relevant to the word for purposes of determining if an email is
 * spam.
 *
 * Given: string, int, int => Word*
 *
 * param: char* word   The Word being added to the library
 * param: int index    The index in the Word array that represents the current
 *                     library
 * param: int spam_or_ham  0 for Ham and 1 for Spam
 * param: int spam_count the number of spam samples used for determining the
 *                       predictive weight
 *
 * return: Pointer to a Word struct
 */
Word* add_word(char* word, int index, int spam_or_ham);

void lib_update_word(Word* word, int spam_or_ham);

void lib_update_num_emails(Word* word, int spam_or_ham);

void lib_contains(Library* library, char* w);

void print_word(Word* word);

void print_lib(Library* lib);

void read_email(char* email, Library* library, int spam_or_ham);

void write_library(Library* lib, const char* path);

Classification* create_classification(Library* lib, char* email_path, int truth);

Report* create_report();

void print_report(Report* report);

void write_report(Report* report, const char* report_path);

#endif //SPAMFILTER_H