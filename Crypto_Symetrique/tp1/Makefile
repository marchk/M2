CC = gcc
CFLAGS = -Wall -O3

.SUFFIXES: .c .o

PRGS = f2_poly_test arithm_test

all:\
	$(PRGS)

f2_poly_test:\
	f2_poly_test.o f2_poly.o arithm.o error.o
	$(CC) f2_poly_test.o f2_poly.o arithm.o error.o -o $@

arithm_test:\
	arithm_test.o arithm.o
	$(CC)  arithm_test.o arithm.o -o $@

.c.o: \
	$*.h $*.c
	@echo $*
	$(CC) $(CFLAGS) -c $< 

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	-rm -rf $(PRGS)
