#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long mult(long long a, long long b, long long N);
//donne a*b mod N

long long sqr1(long long a, long long N);
//donne a² mod N

long long sqrtimes(long long a, long long x, long long N);
//donne a^(2^i) mod N

long long expm(long long a, long long b, long long N);
//donne a^b mod N

long long bezout(long long a, long long b, long long *u, long long *v);
//donne l'identité de Bezout au + bv = pgcd(a,b)

long long pgcd(long long a, long long b);
//donne pgcd(a,b)

void decomp(long long n, long long *s, long long *t);
//n = 2^s x t avec t impair
