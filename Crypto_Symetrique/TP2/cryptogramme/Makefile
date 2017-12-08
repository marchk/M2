GCC=gcc -Wall -Wpointer-arith -O3

all : splitText

splitText : splitText.o
	$(GCC) -o splitText splitText.o
	
splitText.o : splitText.c
	$(GCC) -c splitText.c
	
clean :
	rm *.o
	
cleanExec :
	rm splitText
	
cleanSplit :
	rm *.split?
	
mrproper : clean cleanExec cleanSplit
