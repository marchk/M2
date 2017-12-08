#include <stdio.h>
#include <stdlib.h>

#define N 383
#define g 2
#define h 229


unsigned mult(unsigned a, unsigned b){
	return ((a%N)*(b%N))%N;
}


unsigned sqr1(unsigned a){
	return mult(a,a);
}


unsigned expm(unsigned a, unsigned b){
	if(b==0){ return 1;}
	if( (b&1)!=0 ){	return mult(a, expm(a,(b-1))); }
	return sqr1(expm(a,(b/2)));
}



unsigned F(unsigned* y){
	if( ((*y)%3) == 1 ){return (h*(*y))%N;}
	else if( ((*y)%3) == 0 ){return ((*y)*(*y))%N;}
	else/*if( ((*y)%3) == 2 )*/{return (g*(*y))%N;}
}

int main(){
	int i = 0;
	unsigned yi = 1;
	unsigned y2i = yi;
	do{
		yi = F(&yi);
		unsigned tmp = F(&y2i);
		y2i = F(&tmp);
		i++;
		printf("i = %d\n yi = %d --- y2i = %d\n", i, yi, y2i);
	}while(yi != y2i);
	printf("i = %d\n yi = %d --- y2i = %d\n", i, yi, y2i);
	unsigned test = expm(g,i);
	printf("= %d\n", test);
	return 0;
}
	
