filter_files = spamfilter.h classifier.c spamfilter.c filter_main.c

cFlags = -Wall -Werror

targets = spamfilter

all: $(targets)

spamfilter: $(filter_files)
	gcc -o spamfilter $(cFlags) $(filter_files) -lm

run_filter: spamfilter
	./spamfilter ./data/spam ./data/ham ./data/test/Spam ./data/test/Ham

clean: rm $(targets)