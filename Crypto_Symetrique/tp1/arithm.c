#include "arithm.h"
#include "f2_poly.h"

uint64_t
pp_diviseur_premier(uint64_t p){
	if(p == 1){ return 1; }
	if(p==0){return 2;}
	uint64_t i;
	for(i=2; i<=p; i++){
		if( (p%i)==0 ){ return i;}
	}
	return 1;
}



int mobius(uint64_t n){
	if(n==1){return	1;}
	int nb = 0;
	uint64_t p; uint64_t pp = 0;
	while(n!=1){
		p = pp_diviseur_premier(n);
		if(p==pp){return 0;}
		nb++;
		pp = p;
		n /= p;
	}
	if((nb%2)==0){return 1;}
	return -1;
}
