GCC=gcc -Wall -Wpointer-arith -fPIC

all : colimacon

colimacon : colimacon.so colimacon.a colimacon.o
	$(GCC) -o colimacon colimacon.o 
	
colimacon.a : colimacon.o
	ar -cvq colimacon.a colimacon.o
	
colimacon.so : colimacon.o
	gcc -o colimacon.so -shared colimacon.o

colimacon.o : colimacon.c
	$(GCC) -c colimacon.c
	
clean :
	rm *.o *.a *.so
	
raz: clean
	rm colimacon
