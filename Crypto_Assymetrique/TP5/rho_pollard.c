
#include "modulo.h"


#define N 383
#define g 2
#define h 229


void F(long long *y, long long *ai, long long *bi){
	int k = (*y)%3;
	if(k==1){
		(*y) = mult(h, (*y), N);
		(*bi)++; 
	}
	else if(k==0){
		(*y) = sqr1((*y), N);
		(*ai)*=2;
		(*bi)*=2;
	}
	else if(k==2){
		(*y) = mult(g, (*y), N);
		(*ai)++; 
	}
}

int main(){
	printf("Recherche du log discret de %d en base %d dans F(%d)*\n...\n", h, g, N);
	int i = 0;
	long long yi = 1, y2i = yi;
	long long ai = 0, bi = 0;
	long long a2i = 0, b2i = 0;
	long long u=0, v=0, p=0;
	long long b = 0, a=0;
	do{
		F(&yi, &ai, &bi);
		F(&y2i, &a2i, &b2i);
		F(&y2i, &a2i, &b2i);
		i++;
		printf("y%d = %lld\n", i, yi);
		if(yi == y2i){
			printf("Collision !\ny%d = y%d = %lld\na%d = %lld --- b%d = %lld\na%d = %lld --- b%d = %lld\n", i, 2*i,yi, i, ai, i, bi, 2*i, a2i, 2*i, b2i);
			b = (bi-b2i);
			if(b<0){ b = N-1+b;}
			printf("b = (b%d - b%d) = %lld mod %d\n", i, 2*i, b, N-1);
			p = bezout(b, N-1, &u, &v);
			if(u<0){ u = N-1+u;}
			if(p==1){
				printf("b^(-1)= %lld mod %d\n",u,N-1);
			}
		}
		printf("----------------------------------------\n");
	}while( !((yi==y2i) && (p==1)) && i<=(N/2));
	
	if((yi==y2i) && (p==1)){
		a = (a2i-ai);
		if(a<0){ a = N-1+a;}
		long long x = mult( a, u, N-1);
		printf("x = %lld mod %d\n", x, N-1);
		long long r = expm(g, x, N);
		printf("%d^x = %lld mod %d\n", g,r,N);	
	}
	else{
		printf("\nNon trouvé...\n");
	}
	return 0;
}
	
