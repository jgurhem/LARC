C=gcc
CFLAGS=-Wall -O2 -lm -std=c99

MVOPUTILSDIR=../utils/
MVOPUTILSSO=../utils/libmvoputils.so
MVOPUTILSFLAGS=-L$(MVOPUTILSDIR) -I$(MVOPUTILSDIR) -lmvoputils

SRC= $(wildcard *.c)
EXE= $(SRC:.c=)

all:$(EXE)

%:%.c
	$(C) -o $@ $< $(MVOPUTILSFLAGS) $(CFLAGS)

clean:
	rm -f $(EXE)

