C=gcc
CFLAGS=-Wall -O2 -fPIC

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LIBNAME=libmvoputils.so

all: build

build: algorithms.o BlockToMatrixUtils.o BlockToVectorUtils.o MatrixUtils.o VectorUtils.o
	$(C) -shared algorithms.o BlockToMatrixUtils.o BlockToVectorUtils.o MatrixUtils.o VectorUtils.o -o $(LIBNAME)

%.o : %.c
	$(C) $(CFLAGS) -o $@ -c $< $(LIBDEP)

clean:
	rm -f *.o

cleanall: clean
	rm -f *.so
