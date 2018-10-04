C=gcc
CFLAGS=-Wall -O2 -lm

MVOPUTILSDIR=../utils
MVOPUTILSSO=../utils/libmvoputils.so
MVOPUTILSFLAGS=-L$(MVOPUTILSDIR) -I$(MVOPUTILSDIR) -lmvoputils

SRCS=$(wildcard $(MVOPUTILSDIR)*.c)

all: powerIt lu dge

powerIt: powerIt.c $(MVOPUTILSSO)
	$(C) -o powerIt powerIt.c $(MVOPUTILSFLAGS) $(CFLAGS)

lu: lu.c $(MVOPUTILSSO)
	$(C) -o lu lu.c $(MVOPUTILSFLAGS) $(CFLAGS)

dge: dgeaxpxmv.c $(MVOPUTILSSO)
	$(C) -o dgeaxpxmv dgeaxpxmv.c $(MVOPUTILSFLAGS) $(CFLAGS)

$(MVOPUTILSSO): $(SRCS)
	$(MAKE) -C $(MVOPUTILSDIR)

clean:
	rm -f powerIt lu

cleanall: clean
	$(MAKE) -C $(MVOPUTILSDIR) cleanall
