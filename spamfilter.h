#ifndef SPAMFILTER_H
#define SPAMFILTER_H


#define BUFFER_SIZE 1000
#define MAX_NUM_FILES 500
#define MAX_EMAIL_WORDS 500
#define MAX_LIBRARY_WORDS 1000

#define DATA_DIRECTORY_SPAM_POS 1
#define DATA_DIRECTORY_HAM_POS 2


typedef struct dirent Dirent_t;

typedef struct {
    char* word;
    int spam_count;
    int ham_count;
    int predictive_weight;
} Word;


/**
This function takes a pointer to a directory and creates a list of filenames
that exist in that directory.

param: const char* directory to open and get filenames from.
param: char** files pointer to array of strings we are storing file names in

return: Number of files.
*/
int get_files(const char* directory, char** files);



#endif //SPAMFILTER_H