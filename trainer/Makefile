trainer_files = spamtrainer.c trainer_main.c

filter_files = spamfilter.c filter_main.c

cFlags = -Wall -Werror

targets = spamtrainer

all: $(targets)

spamtrainer: spamtrainer.h $(trainer_files)
	gcc -o spamtrainer $(trainer_files) $(cFlags)

spamfilter: spamfilter.h $(filter_files)
	gcc -o spamfilter $(filter_files) $(cFlags)

run_trainer: spamtrainer
	./spamtrainer ./data/spam ./data/ham

clean: rm $(targets)