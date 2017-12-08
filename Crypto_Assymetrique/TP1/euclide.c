#include<stdio.h>
#include <stdlib.h>

int euclide(int a, int b){
	if(a<b){return euclide(b,a);}
	int r0 = a, r1 = b,i = 2;
	while(r1 > 0){
		int t = r0%r1;
		r0 = r1;
		r1 = t;
		i++;
	}
	fprintf(stdout, "(%d étapes)\n", i);
	return r0;
}

int euclide_modifie(int a, int b){
	if(a<b){return euclide_modifie(b,a);}
	int r0 = a, r1 = b, i = 2;
	while(r1 > 0){
		int t = r0%r1;
		int tmp = -t+r1;
		if(t <= tmp){
			r0 = r1; 
			r1 = t;
		}
		else{
			r0 = r1;
			r1 = tmp;
		}
		i++;
	}
	fprintf(stdout, "(%d étapes)\n", i);
	return r0;
}

int pgcd(int a, int b){
	if(a<b){return pgcd(b,a); }
	if(a<0){a = -a;}
	if(b<0){b = -b;}
	if(a==b){ return a;}
	if( ((a&1)==0) && ((b&1)== 0) ){ return 2*pgcd(a>>1,b>>1); }
	else if((a&1)==0){ return pgcd(a>>1,b); }
	else if((b&1)==0){ return pgcd(a,b>>1); }
	else { return pgcd(a-b,b); }
}

int main(int argc, char** argv){
	int a = atoi(argv[1]), b = atoi(argv[2]);
	int p1 = euclide(a,b), p2 = euclide_modifie(a, b), p3 = pgcd(a,b);
	fprintf(stdout, "pgcd(%d, %d) = \n   %d par Euclide normal\n   %d par Euclide modifie\n   %d par l'autre algo\n", a,b,p1,p2,p3);
}
