#include "lfsr.h"
#include <stdio.h>
#include <stdlib.h>


unsigned taille(unsigned n){
	unsigned i = 0;
	while(n>0){
		n >>=1;
		i++;
	}
	return i;
}



void print_binaire(unsigned n){
	unsigned l = taille(n);
	int i;
	for(i=0; i<l; i++){
		printf("%u", n>>(l-1-i)&1);
	}
}



unsigned somme(unsigned n){
	n ^= (n>>32);
	n ^= (n>>16);
	n ^= (n>>8);
	n ^= (n>>4);
	n ^= (n>>2);
	n ^= (n>>1);
	n &=1;
	return n;
}


int lfsr_container_init (container_t *c, const maxlen_t r, maxlen_t p){
	c->regist = r;
	c->poly = p;
	return 0;
}

int lfsr_init (lfsr_t * lfsr, const byte_t z, const byte_t l, container_t * c){
	if( (z <= MAXLEN(maxlen_t)) && (l <= MAXLEN(maxlen_t)) && ((z+l-1)<=MAXLEN(maxlen_t)) ){
		lfsr->zero =z;
		lfsr->len = l;
		lfsr->cont = c;
	return 0;
	}
	return -1;
}


void lfsr_inc (lfsr_t *lfsr){
	maxlen_t r = lfsr->cont->regist;
	if( (lfsr->len) < MAXINT ){
		long lmax = Mask(0,MAXINT);//(MAXINT)^(MAXINT>>1);
		int l = length(lmax), last_bit = lmax ^ r;
		if((last_bit>>l)==1){lfsr->cont->regist ^= lmax;}
		lfsr->cont->regist = ((lfsr->cont->regist)<<1) ^ somme( (lfsr->cont->regist)&(lfsr->cont->poly));
		lfsr->len++;
	}		
}
