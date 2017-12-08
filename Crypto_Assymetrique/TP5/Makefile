CC = gcc
CFLAGS = -Wall -Wpointer-arith -O3
EXEC = shanks rho_pollard
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

shanks: shanks.o modulo.o
	$(CC) -o $@ $^
	
rho_pollard: rho_pollard.o modulo.o
	$(CC) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
