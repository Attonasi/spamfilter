trainer_files = spamtrainer.c trainer_main.c

filter_files = spamfilter.c filter_main.c

cFlags = -Wall -Werror

targets = spamfilter spamtrainer

all: $(targets)

spamtrainer: spamfilter.h $(trainer_files)
    gcc -o spamtrainer $(trainer_files) $(cFlags)

spamfilter: spamfilter.h $(filter_files)
    gcc -o spamfilter $(filter_files) $(cFlags)

clean: rm $(targets)