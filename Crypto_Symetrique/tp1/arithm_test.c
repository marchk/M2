#include "arithm.h"

int main(){
	uint64_t p = 3*3*5*7*11;
	uint64_t pp;
	printf("liste des diviseurs de %lu : \n", p);
	do{
		pp = pp_diviseur_premier(p);
		printf("-%lu-", pp);
		p /= pp;
		if(!pp){return -1;}
	}while(pp>1);
	printf("\n");
	
	int i;
	for(i=1; i<=20; i++){
		printf("µ(%d) = %d\n", i, mobius(i));
	}	
	
	return 0;
}
