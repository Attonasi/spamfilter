//
// Created by collin on 9/11/18.
//

#ifndef SPAMFILTER_SPAMFILTER_H
#define SPAMFILTER_SPAMFILTER_H

#define NUM_HAM 500
#define NUM_SPAM 500
#define MAX_LIBRARY_WORDS 30000
#define MAX_WORD_SIZE 400

#define NEW_LINE 10


typedef struct {
    char word[MAX_WORD_SIZE];
    int index;
    int spam_count;
    int spam_num_emails;
    int ham_count;
    int ham_num_emails;
    float ham_score;
    float spam_score;

} Word;

typedef struct {
    Word* library[MAX_LIBRARY_WORDS];
    int num_lib_words;
    int lib_compare;
} Library;

Library* create_library(const char* path);

void print_lib(Library* lib);



#endif //SPAMFILTER_SPAMFILTER_H
