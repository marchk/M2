GCC=gcc  -m32 -Wall -Wpointer-arith -m32

all : hello_32 hello_32_dyn

hello_32 : hello.c
	$(GCC) hello.c -o hello_32 -static
	
hello_32_dyn: hello.c
	$(GCC) hello.c -o hello_32_dyn
	
cleanstatic :
	rm hello_32
	
cleandyn :
	rm hello_32_dyn
	
clean : cleanstatic cleandyn
