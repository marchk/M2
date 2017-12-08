#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"



int in(long long x, long long *t, long long l){
	long long i;
	for(i=0; i<l; i++){
		if(x==t[i]){return i;}
	}
	return -1;
}


int miller_rabin(long long n, long long k){
	if(k>n){
		fprintf(stderr, "Arguments invalides ! l'arguent 2 doit être inférieur à l'argument 1 !\n");
		return -2;
	}
	if((n&1)==0){return 0;}
	long long* t = malloc(k*sizeof(long long));
	long long s=0, r=0;
	decomp(n-1, &s, &r);
	printf("%lld = 2^(%lld) x %lld\n", n-1,s,r);
	if(t!=NULL){
		long long i;
		srand(time(NULL)); 
		for(i=0; i<k; i++){
			long long a;
			do{
				a = (rand()%(n-2))+2;
			while(in(a,t,i) != -1);
			t[i] = a;
			printf("Tirage %lld...\na = %lld\n",i+1,a);
			
			long long p = pgcd(a,n);
			printf("pgcd(%lld,%lld) = %lld\n",a,n,p);
			if(p!=1){return 0;}
			long long j=0,x = expm(a,r,n);
			do{
				printf("a^(2^%lld x %lld) = %lld mod %lld\n",j,r,x,n);
				if(x == (n-1)){break;}
				else if(x==1){return 0;}
				x = sqr1(x,n);
				j++;
			}while(j<=s);
			/*for(j=0; j<=s; j++){
				x = expm(sqrtimes(a,j,n), r,n);
				printf("a^(2^%lld x %lld) = %lld mod %lld\n",j,r,x,n);
				if(x == (n-1)){break;}
				else if(x==1){return 0;}
			}*/
			printf("\n------------------------------\n");
		}
		return 1;
	}
	fprintf(stderr, "Mémoire insuffisante !\n");
	return -1;
}


int main(int argc, char** argv){
	long long N = atoi(argv[1]), k = atoi(argv[2]);
	long long r = miller_rabin(N,k);
	if(r==1){
		printf("%lld est probablement premier\n",N);
	}
	else if(r==0){
		printf("%lld est composé\n", N);
	}
	else{return r;}
}
