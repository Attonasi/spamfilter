filter_files = spamfilter.c filter_main.c

cFlags = -Wall -Werror

targets = spamfilter

all: $(targets)

spamfilter: spamfilter.h $(filter_files)
	gcc -o spamfilter $(filter_files) $(cFlags)

run_filter: spamfilter
	./spamfilter ./data/spam ./data/ham

clean: rm $(targets)