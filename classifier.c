//
// Created by collin on 9/12/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "spamfilter.h"

Classification* create_classifiication(Library* lib, char* email_path, int truth) {

    Classification* c = malloc(sizeof(Classification));

//    const char slash[2] = "/";
//    const char period[2] = ".";
//
//
//    strcpy(c->email, strtok(email_path, period));
//
    c-> ham_or_spam_or_test = truth;
    c->spam_value = 0.0;
    c->ham_value = 0.0;

    // Naive-Bayes goes here

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
    for(int i = 0; i < rep->num_classifications; i++) {
        Classification* c = rep->report_repo[i];
        printf("Email: %s Spam Value: %.3f Ham Value: %3f Given: %d Classification %d\n", c->email, c->spam_value,
                c->ham_value, c->ham_or_spam_or_test, c->ham_or_spam_classifier);
    }
}

void write_report(Report* rep, const char* report_path) {

    FILE* fp = fopen(report_path, "w");

    for(int i = 0; i < rep->num_classifications; i++) {
        Classification* c = rep->report_repo[i];
        fprintf(fp, "Email: %s Spam Value: %.3f Ham Value: %3f Given: %d Classification %d\n", c->email, c->spam_value,
               c->ham_value, c->ham_or_spam_or_test, c->ham_or_spam_classifier);
    }

    fclose(fp);
}