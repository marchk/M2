GCC=gcc -Wall -Wpointer-arith

all : colimacon

colimacon : colimacon.o
	$(GCC) -o colimacon colimacon.o
colimacon.o : colimacon.c
	$(GCC) -c colimacon.c
clean :
	rm *.o
