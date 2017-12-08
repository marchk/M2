CC = gcc
CFLAGS = -Wall -Wpointer-arith -O3 -pthread
EXEC = tp5
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)
	
% : %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	rm -rf $(EXEC)
