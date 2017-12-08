GCC=gcc -Wall -Wpointer-arith

all : polynomeF2 polynomeFp

polynomeF2 : polynomeF2.o
	$(GCC) -o polynomeF2 polynomeF2.o
polynomeF2.o : polynomeF2.c
	$(GCC) -c polynomeF2.c
olynomeFp : polynomeFp.o
	$(GCC) -o polynomeFp polynomeFp.o
polynomeFp.o : polynomeFp.c
	$(GCC) -c polynomeFp.c
clean :
	rm *.o
cleanExec :
	rm polynome??
mrproper : clean cleanExec
	
