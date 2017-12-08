#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long mult(unsigned long long a, unsigned long long b, unsigned long long N){
	return ((a%N)*(b%N))%N;
}


unsigned long long sqr1(unsigned long long a, unsigned long long N){
	return mult(a,a,N);
}


unsigned long long expm(unsigned long long a, unsigned long long b, unsigned long long N){
	if(b==0){ return 1;}
	if( (b&1)!=0 ){	return mult(a, expm(a,(b-1),N),N); }
	return sqr1(expm(a,(b/2),N),N);
}


unsigned long long bezout(unsigned long long a, unsigned long long b, unsigned long long *u, unsigned long long *v) {
  unsigned long long q, r, s, t, tmp;
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
