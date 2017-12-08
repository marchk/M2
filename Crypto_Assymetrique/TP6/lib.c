#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long mult(long long a, long long b, long long N){
	return ((a%N)*(b%N))%N;
}


long long sqr1(long long a, long long N){
	return mult(a,a,N);
}

long long sqrtimes(long long a, long long x, long long N){
	long long i,r=a;
	for(i=0; i<x; i++){
		r = sqr1(r,N);
	}
	return r;
}


long long expm(long long a, long long b, long long N){
	if(b==0){ return 1;}
	if( (b&1)!=0 ){	return mult(a, expm(a,(b-1),N),N); }
	return sqr1(expm(a,(b/2),N),N);
}


long long bezout(long long a, long long b, long long *u, long long *v) {
  long long q, r, s, t, tmp;
  *u = 1;
  *v = 0;
  s = 0;
  t = 1;
  while (b > 0) {
    q = a / b;
    r = a % b;
    a = b;
    b = r;
    tmp = s;
    s = *u - q * s;
    *u = tmp;
    tmp = t;
    t = *v - q * t;
    *v = tmp;
  }
  return a;
}




long long pgcd(long long a, long long b){
	if(a<b){return pgcd(b,a); }
	if(a<0){a = -a;}
	if(b<0){b = -b;}
	if(a==b){ return a;}
	if( ((a&1)==0) && ((b&1)== 0) ){ return 2*pgcd(a>>1,b>>1); }
	else if((a&1)==0){ return pgcd(a>>1,b); }
	else if((b&1)==0){ return pgcd(a,b>>1); }
	else { return pgcd(a-b,b); }
}


void decomp(long long n, long long *s, long long *t){
	*s = 0;
	while((n&1)==0){
		(*s)++;
		n >>= 1;
	}
	(*t) = n;
}

