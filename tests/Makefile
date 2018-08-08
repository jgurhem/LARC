C=gcc
CFLAGS=-Wall -O2 -lm

MVOPUTILSDIR=../utils
MVOPUTILSSO=../utils/libmvoputils.so
MVOPUTILSFLAGS=-L$(MVOPUTILSDIR) -I$(MVOPUTILSDIR) -lmvoputils

SRCS=$(wildcard $(MVOPUTILSDIR)*.c)

all: lu
lu: lu.c $(MVOPUTILSSO)
	$(C) -o lu lu.c $(MVOPUTILSFLAGS) $(CFLAGS)

$(MVOPUTILSSO): $(SRCS)
	$(MAKE) -C $(MVOPUTILSDIR)

clean:
	rm -f lu

cleanall: clean
	$(MAKE) -C $(MVOPUTILSDIR) cleanall
