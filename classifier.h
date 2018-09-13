//
// Created by collin on 9/12/18.
//

#ifndef SPAMFILTER_CLASSIFIER_H
#define SPAMFILTER_CLASSIFIER_H

#define TOTAL_EMAILS 1000


typedef struct Classification {
    char* email;
    float spam_value;
    float ham_value;
    int ham_or_spam_truth;
    int ham_or_spam_classifier;
} Classification;

Classification* create_classification(int truth);

typedef struct Report {
    Classification* report_repo[TOTAL_EMAILS];
    int num_classifications;
} Report;

Report* init_report();



#endif //SPAMFILTER_CLASSIFIER_H
