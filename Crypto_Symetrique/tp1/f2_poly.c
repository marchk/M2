#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "f2_poly.h"
#include <error.h>

#include "arithm.h"
#include <time.h>



f2_deg_t
f2_poly_deg(f2_poly_t P){
	f2_deg_t i = 0;
	P>>=1;
	while(P != 0){
		i++;
		P >>=1;
	}
	return i;
}



int
f2_poly_print(f2_poly_t P, char p, FILE *f){
	f2_deg_t d = f2_poly_deg(P);
	uint8_t i = 0;
	fprintf(f, "%c = ",p);
	for(i=d; i>=0; i--){
		if((i==0) && (d==0)){fprintf(f, "%ld ", P&1);}
		else if((i==0) && ((P&1)!=0)){fprintf(f,"+ %ld ", P&1);}
		else if(i==d){
			if(((P>>i)&1)!=0){
				if(i==1){ fprintf(f, "X "); }
				else{ fprintf(f, "X^%d ",i); }
			}
		}
		else{
			if(((P>>i)&1)!=0){
				if(i==1){ fprintf(f, "+ X "); }
				else{ fprintf(f, "+ X^%d ",i); }
			}
		}
		if(i==0){break;}
	}
	fprintf(f, "\n");
	return 0;
}



f2_poly_t mult(f2_poly_t P, f2_poly_t Q){//multiplication dans F2[X]
	f2_deg_t n = f2_poly_deg(P) + f2_poly_deg(Q);
	uint8_t i; uint8_t j;
	f2_poly_t R = 0;
	for(i = n; i>0; i--){
		uint8_t k = 0;
		for(j=i; j>0; j--){
			k ^= (((P>>j)&1) & (Q>>(i-j)&1));
		}
		R ^= k; R <<=1;
	}
	return R^((P&1)&(Q&1));
}



int
f2_poly_div(f2_poly_t *Q,f2_poly_t *R, f2_poly_t A, f2_poly_t B){
	if(B==0){ *Q = 0; *R = 0; return -1;}
	if(B==1){*Q = A; *R = 0; return 0;}
	*R = A; f2_poly_t Diviseur;
	*R = A; *Q = 0;
	while(f2_poly_deg(*R) > f2_poly_deg(B)){
		Diviseur = 1<<(f2_poly_deg(*R) - f2_poly_deg(B));
		(*R) ^= mult(Diviseur,B);
		(*Q) ^= Diviseur;
	}
	if(f2_poly_deg(*R) == f2_poly_deg(B)){
		*R = *R^B;
		*Q ^=1;
	}
	return 0;
}



f2_poly_t
f2_poly_rem(f2_poly_t A, f2_poly_t B){
	f2_poly_t Q;  f2_poly_t R;
	f2_poly_div(&Q, &R, A, B);
	return R;
}



f2_poly_t
f2_poly_gcd(f2_poly_t P, f2_poly_t Q){
	if(f2_poly_deg(P)<f2_poly_deg(Q)){return f2_poly_gcd(Q,P);}
	f2_poly_t r0 = P;
	f2_poly_t r1 = Q;
	f2_poly_t t = 0;
	f2_poly_t a = 0;
	while(r1 > 0){
		f2_poly_div(&a, &t, r0, r1);
		r0 = r1;
		r1 = t;
		if(t==1){return 1;}
	}
	return r0;
}



f2_poly_t
f2_poly_xtimes(f2_poly_t A, f2_poly_t P){
	return f2_poly_rem(A<<1,P);
}



f2_poly_t
f2_poly_times(f2_poly_t A, f2_poly_t B, f2_poly_t P){
	return f2_poly_rem(mult(A,B),P);
}



f2_poly_t
f2_poly_x2n(f2_deg_t n, f2_poly_t P){ 
	uint8_t i;
	f2_poly_t Q = f2_poly_xtimes(2, P);
	for(i=1; i<n; i++){
		Q = f2_poly_times(Q,Q,P);
	}
	return Q;
}



f2_poly_t
f2_poly_parity(f2_poly_t P){
	P ^= (P>>32);
	P ^= (P>>16);
	P ^= (P>>8);
	P ^= (P>>4);
	P ^= (P>>2);
	P ^= (P>>1);
	return (P&1);
}



f2_poly_t
f2_poly_recip(f2_poly_t P){
	f2_poly_t P2 = 0;
	f2_deg_t d = f2_poly_deg(P);
	uint8_t i;
	for(i=0; i<=d; i++){
		P2^=(P&1);
		P>>=1;
		if(i<d){P2<<=1;}
	}
	return P2;
}



int
f2_poly_irred(f2_poly_t P){
	if((P&1)==0){;return 0;}
	if(f2_poly_parity(P)==0){;return 0;}
	f2_deg_t n = f2_poly_deg(P);
	//f2_poly_t res = f2_poly_x2n(n, P);
	//if(res != 2){ return 0;}
	uint64_t p = pp_diviseur_premier(n);
	if(p==n){return 1;}
	uint64_t m = n/p;
	while(m!=1){
		f2_poly_t S = f2_poly_x2n(m, P)^(1<<1);
		if(f2_poly_gcd(S, P) != 1){ return 0;}
		p = pp_diviseur_premier(m);
		m = m/p;
	}
	return 1;
	/*uint8_t i;
	for(i=1; i<n; i++){
		res = f2_poly_x2n(i, P);
		if(f2_poly_gcd(P,res)!=1){return 0;}
	}
	return 1;*/
}



f2_poly_t
f2_poly_xn(uint8_t n, f2_poly_t P){
	int i;
	f2_poly_t R = 1;
	for(i=1; i<=n; i++){
		R = f2_poly_xtimes(R, P);
	}
	return R;
}



int
f2_poly_primitive(f2_poly_t P){ 
	if(f2_poly_irred(P) == 0){ return 0;}
	f2_deg_t n = f2_poly_deg(P);
	uint64_t qn = (1<<n)-1;
	uint64_t x = qn;
	uint64_t p = pp_diviseur_premier(x);
	while(p!=1){
		uint64_t a = qn/p;
		f2_poly_t Q = f2_poly_xn(a, P);
		if(Q == 1){return 0;}
		x /= p;
		p = pp_diviseur_premier(x);
	}
	return 1;
}



uint8_t
f2_poly_irred_order(f2_poly_t polP){ 
	if(f2_poly_irred(polP) == 0){ return 0;}
	int i = 1;
	f2_poly_t xP = f2_poly_xn(1, polP), x = xP;
	do{
		f2_poly_print(x, 'X', stdout);
		x = f2_poly_times(x, xP, polP);
		i++;
	}while(f2_poly_deg(xP) != f2_poly_deg(x));//(x != xP);
	return i-1;
}



f2_poly_t
f2_poly_random_inf(f2_deg_t n){
	srand(time(NULL));
	f2_poly_t P = rand()%(1<<n);
	return P;
}



f2_poly_t
f2_poly_random(f2_deg_t n){ 
	return f2_poly_random_inf(n)^(1<<n); 
}



f2_poly_t
f2_poly_irred_random(f2_deg_t n){ 
	f2_poly_t P;
	do{
		P = f2_poly_random(n);
	}while(f2_poly_irred(P)==0);
	return P;
}



f2_poly_t
f2_poly_primitive_random(f2_deg_t n){
	f2_poly_t P;
	do{
		P = f2_poly_random(n);
	}while(f2_poly_primitive(P)==0);
	return P;
}



int 
f2_poly_irred_count(f2_deg_t n){
	int i;
	int res = 0;
	for(i=1; i<=n; i++){
		if((n%i)==0){
			res += (mobius(n/i)*(1<<i));
		}
	}
	res /= n;
	return res;
}



int 
f2_poly_primitive_count(f2_deg_t n){
	double x = (1<<n)-1;
	double phiN = x;
	do{
		double p = pp_diviseur_premier(x);
		phiN *= (1-(1/p));
		x /= p;
	}while(x!=1);
	int phi = (int)phiN;
	return phi/n;
}
