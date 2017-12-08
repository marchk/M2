#include "modulo.h"


int main(int argc, char** argv){
	int N = atoi(argv[1]), g = atoi(argv[2]);
	int i=0;
	int r = 0;
	do{
		r = expm(g,i,N);
		printf("%d^%d = %d\n", g, i, r);
		i++;
	}while(i<=N);
	return 0;
}
