#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamtrainer.h"

int get_files(const char* directory, char** files){

    Dirent_t* direntPtr;
    DIR* inputFilePtr = opendir(directory);

    if(inputFilePtr != NULL){
        int numberOfFiles = 0;

        while((direntPtr = readdir(inputFilePtr)) != NULL){

            if( !strcmp(direntPtr->d_name, ".") || !strcmp(direntPtr->d_name, "..")){
                // It would seem easy to not need this to get rid of .. and . It isn't.
                // This is the place to add ignore files in the if statement above
            } else {
                files[numberOfFiles] = (char*) calloc(1, sizeof(directory)+sizeof(direntPtr->d_name));
                sprintf(files[numberOfFiles++], "%s/%s", directory, direntPtr->d_name);
            }
        }
        files[numberOfFiles] = NULL;
        closedir(inputFilePtr);
        return numberOfFiles;

    }else{
        printf("\nDirectory Not Found\n");
        return 0;
    }
}

Library* create_library(){
    Library* lib = malloc(sizeof(Library));

    lib->library[0] = add_word("penis enlargment", 0, SPAM);
    lib->num_lib_words = 1;
    lib->lib_compare = 0;

    return lib;
}

Word* add_word(char* word, int index, int spam_or_ham){
    Word* w = malloc(sizeof(Word));

    strncpy(w->word, word, MAX_WORD_SIZE);
    w->index = index;
    w->ham_num_emails = 0;
    w->spam_num_emails = 0;

    if(spam_or_ham){
        w->spam_count = 1;
        w->ham_count = 0;
    } else {
        w->spam_count = 0;
        w->ham_count = 1;
    }
    w->email_flag = 1;

    return w;
}

void lib_update_word(Library* lib, int index, int spam_or_ham)
{
    if(spam_or_ham)
    {
        lib->library[index]->spam_count++;
    } else {
        lib->library[index]->ham_count++;
    }
    lib->library[index]->email_flag = 1;
}

void lib_update_num_emails(Word* word, int spam_or_ham)
{
    if(word->email_flag)
    {
        if(spam_or_ham) {
            word->spam_num_emails++;
        } else {
            word->ham_num_emails++;
        }
        word->email_flag = 0;
    }
}

void lib_contains(Library* lib, char* w)
{
    for (int i = 0; i < lib->num_lib_words; i++)
    {
        if (strcasecmp(lib->library[i]->word, w) == 0) {
            lib->lib_compare = i;
            return;
        }
    }
    lib->lib_compare = 0;
}

void print_word(Word* word){
    printf("Index: %d Spam Count: %d Num Spam Emails: %d Ham Count: %d Num Ham Emails: %d Word: %s \n",
            word->index, word->spam_count, word->spam_num_emails, word->ham_count, word->ham_num_emails,
            word->word);
}

void print_lib(Library* lib){
    for(int i = 0; i < lib->num_lib_words; i++) {
        print_word(lib->library[i]);
    }
}

void read_email(char* email, Library* lib, int spam_or_ham)
{
    int token_counter = 0;
    char token[MAX_WORD_SIZE];

    FILE* fp = fopen((const char*)email, "r");
    if(!fp) printf("File not Found\n");

    while(!feof(fp))
    {
        token[token_counter] = fgetc(fp);
        if(token[token_counter] == NEW_LINE)
        {
            token[token_counter] = 0;
            lib_contains(lib, token);

            if(lib->lib_compare)
            {
                lib_update_word(lib, lib->lib_compare, spam_or_ham);
            } else {
                lib->library[lib->num_lib_words] = add_word(token, lib->num_lib_words, spam_or_ham);
                lib->num_lib_words++;
            }

            memset(token, 0, MAX_WORD_SIZE);
            token_counter = 0;
        } else {
            token_counter++;
        }
    }
    fclose(fp);

    for(int i = 0; i < lib->num_lib_words; i++){
        lib_update_num_emails(lib->library[i], spam_or_ham);
    }
}

void write_library(Library* lib, const char* path){

    FILE* fp = fopen(path, "w");

    for(int i = 0; i < lib->num_lib_words; i++){
        fprintf(fp, "%d, %d, %d, %d, %d, %d, %s\n", lib->library[i]->index, lib->library[i]->spam_count,
                lib->library[i]->spam_num_emails, lib->library[i]->ham_count, lib->library[i]->ham_num_emails,
                lib->library[i]->email_flag, lib->library[i]->word);
    }

    fclose(fp);
}


