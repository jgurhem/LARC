C=gcc
CFLAGS=-Wall -O2 -lm -std=c99

MVOPUTILSDIR=../utils/
MVOPUTILSSO=../utils/libmvoputils.so
MVOPUTILSFLAGS=-L$(MVOPUTILSDIR) -I$(MVOPUTILSDIR) -lmvoputils

all: main

main: main.c
	$(C) -o check_results main.c $(MVOPUTILSFLAGS) $(CFLAGS)

clean:
	rm -f check_results

