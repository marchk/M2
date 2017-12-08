#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"
#include "f2_poly.h"


int main(){
	int i;
	maxlen_t regist = 80;
  	maxlen_t poly = 71;
  	byte_t zero = 56;
  	byte_t len = 8;
  	
  	container_t* cont = malloc(sizeof(container_t));
  	lfsr_container_init(cont, regist, poly);
  	
  	lfsr_t * lfsr = malloc(sizeof(lfsr_t));
  	lfsr_init(lfsr, zero, len, cont);
  	
  	for(i=0; i<100; i++){
  		printf("Etape %2d :",i);
  		printf(" %lx\n",lfsr->cont->regist);
  		//print_binaire(lfsr->cont->regist);
  		printf("\n");
  		lfsr_inc (lfsr);
  	}

	return 0;
}
