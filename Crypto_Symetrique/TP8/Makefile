CC = gcc
CFLAGS = -Wall -Wpointer-arith -O3
EXEC = table
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

	
table: heys.o table.o
	$(CC) -o $@ $^


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
	
clean_files : 
	rm -rf rand_bytes ';'
	rm -rf chiffre ';'

mrproper: clean clean_files
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	rm -rf $(EXEC)
