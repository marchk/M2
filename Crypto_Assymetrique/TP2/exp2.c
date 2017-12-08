#include <stdio.h>
#include <stdlib.h>

#define N 383
#define g 2
#define h 229

int mult(int a, int b){
	return ((a%N)*(b%N))%N;
}


int sqr1(int a){
	return mult(a,a);
}


int expm(int a, int b){
	if(b==0){ return 1;}
	if( (b&1)!=0 ){	return mult(a, expm(a,(b-1))); }
	return sqr1(expm(a,(b/2)));
}

int main(){
	int i=0;
	int r = 0;
	do{
		r = expm(g,i);
		printf("%d^%d = %d\n", g, i, r);
		i++;
	}while(r!=h);
	return 0;
}
