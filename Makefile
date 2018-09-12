filter_files = spamfilter.h filter_main.c classifier.c spamfilter.c

cFlags = -Wall -Werror

targets = spamfilter

all: $(targets)

spamfilter: $(filter_files)
	gcc -o spamfilter $(filter_files) $(cFlags)

run_filter: spamfilter
	./spamfilter ./data/spam ./data/ham

clean: rm $(targets)