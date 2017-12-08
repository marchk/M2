#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int i;
	for(i=0; i<10; i++){
		sleep(1);
		printf("Hello World !\n");
	}
	return 0;
}
