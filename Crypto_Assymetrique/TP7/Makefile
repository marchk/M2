CC = gcc
CFLAGS = -Wall -Wpointer-arith -O3
EXEC = rho_pollard_fact
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
GMPLIBINCLUDE = -I /usr/lib/sagemath/local/include -L/usr/lib/sagemath/local/lib


#--gcc -Wall -Wpointer-arith -o rho_pollard_fact -I /usr/lib/sagemath/local/include -L/usr/lib/sagemath/local/lib rho_pollard_fact.c -lgmp -static


all: $(EXEC)

	
rho_pollard_fact: rho_pollard_fact.c
	$(CC) -o $@ $(GMPLIBINCLUDE) $^ -lgmp -static


clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
