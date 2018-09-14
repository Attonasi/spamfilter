//
// Created by collin on 9/12/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#include "spamfilter.h"

Classification* create_classification(Library* lib, char* email_path, int truth) {

//    printf("Inside classification: %s\n", email_path);

    Classification* c = malloc(sizeof(Classification));

//    const char slash[2] = "/";
//    const char period[2] = ".";

    strcpy(c->email, email_path);

//    printf("c->email: %s\n", c->email);
    c-> ham_or_spam_or_test = truth;
    c->spam_value = 0.0;
    c->ham_value = 0.0;

    int word_len = 0;
    char word[MAX_WORD_SIZE];

    FILE* fp = fopen((const char*)email_path, "r");
    if(!fp) printf("File not Found\n");

    while(!feof(fp))
    {
        word[word_len] = fgetc(fp);
        if(word[word_len] == NEW_LINE)
        {
            word[word_len] = 0;
            lib_contains(lib, word);

            if(lib->lib_compare)
            {
                c->ham_value += log(1 + lib->library[lib->lib_compare]->ham_ratio);
                c->spam_value += log(1 + lib->library[lib->lib_compare]->spam_ratio);
            }

            memset(word, 0, MAX_WORD_SIZE);
            word_len = 0;
        } else {
            word_len++;
        }
    }
    fclose(fp);

    if(c->spam_value > c->ham_value)
    {
        c->ham_or_spam_classifier = 1;
    } else {
        c->ham_or_spam_classifier = 0;
    }

    return c;
}

Report* create_report(){

    Report* r = malloc(sizeof(Report));

    r->num_classifications = 0;

    for (int i = 0; i < TOTAL_EMAILS; i++){
        r->report_repo[i] = NULL;
    }

    return r;
}

void print_report(Report* rep) {
    printf("print report Num classifications: %d\n", rep->num_classifications);

    for(int i = 0; i < rep->num_classifications; i++) {
        printf("repo[%d]->email is: %s\n", i, rep->report_repo[i]->email);
        printf("Email: %s Spam Value: %.3f Ham Value: %.3f Given: %d Classification %d\n", rep->report_repo[i]->email,
                rep->report_repo[i]->spam_value, rep->report_repo[i]->ham_value,
                rep->report_repo[i]->ham_or_spam_or_test, rep->report_repo[i]->ham_or_spam_classifier);
    }
}

void write_report(Report* rep, const char* report_path) {

    FILE* fp = fopen(report_path, "w");
    if(!fp) printf("Write Report File not Found\n");

    for(int i = 0; i < rep->num_classifications; i++) {
        fprintf(fp, "Spam Value: %.3f Ham Value: %.3f Given: %d Classification %d Email: %s\n",
               rep->report_repo[i]->spam_value, rep->report_repo[i]->ham_value, rep->report_repo[i]->ham_or_spam_or_test,
               rep->report_repo[i]->ham_or_spam_classifier, rep->report_repo[i]->email);
    }

    fclose(fp);
}

void write_assignment_format(Report* rep, const char* assignment_path) {

    FILE* fp = fopen(assignment_path, "w");
    if(!fp) printf("Assignment Report File not Found\n");

    char spam_answer_classification[5];
    char given_classification[5];

    fprintf(fp, "%-25s %-25s %-15s\n", "Email", "Algorithm Classification", "Given Classification");

    for(int i = 0; i < rep->num_classifications; i++) {

        if (rep->report_repo[i]->ham_or_spam_or_test == 0) {
            strcpy(given_classification, "Ham");
        } else if (rep->report_repo[i]->ham_or_spam_or_test == 1) {
            strcpy(given_classification, "Spam");
        } else {
            strcpy(given_classification, "Test");
        }

        if (rep->report_repo[i]->ham_or_spam_classifier == 0) {
            strcpy(spam_answer_classification, "Ham");
        } else if (rep->report_repo[i]->ham_or_spam_classifier == 1) {
            strcpy(spam_answer_classification, "Spam");
        } else {
            strcpy(spam_answer_classification, "Test");
        }

        fprintf(fp, "%-35s %-25s %-15s\n", rep->report_repo[i]->email, spam_answer_classification, given_classification);
    }

    fclose(fp);
}