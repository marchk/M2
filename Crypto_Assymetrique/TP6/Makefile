CC = gcc
CFLAGS = -Wall -Wpointer-arith -O3
EXEC = miller_rabin
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

	
miller_rabin: miller_rabin.o lib.o
	$(CC) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
