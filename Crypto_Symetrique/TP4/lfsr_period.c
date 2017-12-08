#include "lfsr.h"
#include "f2_poly.h"
#include <stdio.h>
#include <stdlib.h>




int in(unsigned x, unsigned *t, unsigned l){
	unsigned i;
	for(i=0; i<l; i++){
		if(x==t[i]){return i;}
	}
	return -1;
}



unsigned period(lfsr_t* lfsr){
	f2_poly_t P = lfsr->cont->poly;
	f2_deg_t d = f2_poly_deg(P);
	unsigned* steps = calloc(((1<<d)-1),sizeof(unsigned));
	unsigned i=0;
	steps[i] = lfsr->cont->regist;
	do{
		lfsr_inc(lfsr);
		unsigned r = lfsr->cont->regist;
		if(in(r,steps,i)!=-1){return i;}
		i++;
		steps[i] = lfsr->cont->regist;
	}while(i<((1<<d)-1));
	return -1;
}
