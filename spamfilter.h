#ifndef SPAMFILTER_H
#define SPAMFILTER_H

#define BUFFER_SIZE 1000
#define MAX_NUM_FILES 500
#define MAX_EMAIL_WORDS 1000
#define MAX_LIBRARY_WORDS 30000
#define MAX_WORD_SIZE 400

#define NEW_LINE 10

#define DATA_DIRECTORY_SPAM_POS 1
#define DATA_DIRECTORY_HAM_POS 2

#define HAM 0
#define SPAM 1

typedef struct dirent Dirent_t;

typedef struct {
    char word[MAX_WORD_SIZE];
    int index;
    int spam_count;
    int spam_num_emails;
    int ham_count;
    int ham_num_emails;
    int email_flag;

} Word;

typedef struct {
    Word* library[MAX_LIBRARY_WORDS];
    int num_lib_words;
    int lib_compare;
} Library;

Library* create_library();

void print_lib(Library* lib);

/**
 * This function creates a pointer to a Word struct with information
 * relevant to the word for purposes of determining if an email is
 * spam.
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

void print_word(Word* word);

void lib_contains(Library* library, char* w);

void lib_update_word(Library* lib, int index, int spam_or_ham);

void lib_update_num_emails(Word* word, int spam_or_ham);

void read_email(char* email, Library* library, int spam_or_ham);

/**
This function takes a pointer to a directory and creates a list of filenames
that exist in that directory.

param: const char* directory to open and get filenames from.
param: char** files pointer to array of strings we are storing file names in

return: Number of files.
*/
int get_files(const char* directory, char** files);




#endif //SPAMFILTER_H