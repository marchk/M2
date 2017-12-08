
#include "modulo.h"


#define n 113
#define g 3
#define h 57


int main(){
	int N = n-1;
	printf("Recherche du log discret de %d en base %d dans F(%d)*\n...\n", h, g, n);
	unsigned long long* tab = calloc(N,sizeof(unsigned long long));
	unsigned long long i = 0;
	for(i=0; i<N; i++){ tab[i] = n;}
	
	unsigned long long t = (unsigned long long)(sqrt((double)(N)));
	unsigned long long nt = (N)/t;
	
	//-----Baby step-----
	for(i=0; i<t; i++){
		unsigned long long gi = expm(g,i,n);
		tab[gi] = i;
	}
	
	unsigned long long gt = expm(g,N-t,n);
	
	//-----Giant step-----
	for(i=0; i<=nt; i++){
		unsigned long long r = mult(h, expm(gt,i,n), n);
		if(tab[r] != n){ 
			unsigned long long x = (i*t+tab[r]);
			printf("i = %llu, t = %llu, r = %llu\n", i, t, tab[r]); 
			printf("Trouvé !\nx = %llu\n%d^x = %llu\n", x, g, expm(g,x,n));
			return 0;
		}
	}
	printf("Non trouvé...\n");
	return -1;

}
