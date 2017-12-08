GCC=gcc -Wall -Wpointer-arith

all : time_fork time_thread

time_fork : time_fork.c
	$(GCC) time_fork.c -o time_fork
	
time_thread : time_thread.c
	$(GCC) -pthread time_thread.c -o time_thread
	
clean : cleanstatic cleandyn
