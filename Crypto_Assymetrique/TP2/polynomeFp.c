#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Polynome Polynome;
struct Polynome{
    unsigned *p;
    int deg;
};


long euclide_etendu(unsigned a, unsigned b, unsigned *u, unsigned *v) {
  unsigned q, r, s, t, tmp;
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


unsigned mulmod(unsigned a, unsigned n, unsigned m){
	return ((a%m)*(n%m))%m;
}


unsigned addmod(unsigned a, unsigned n, unsigned m){
	return ((a%m)+(n%m))%m;
}


unsigned diffmod(unsigned a, unsigned n, unsigned m){
	return ((a%m)-(n%m))%m;
}


unsigned invmod(unsigned a, unsigned m){
	unsigned u,v;
	euclide_etendu(a,m,&u,&v);
	return u;
}

unsigned divmod(unsigned a, unsigned b, unsigned m){
	return mulmod(a,invmod(b,m),m);
}


unsigned coef(int i, Polynome P){
	if( (i>=0) && (i<=(P.deg))){
		return (P.p)[i]; 
	}
	return 0;
}


int deg(Polynome P){ return P.deg; }


void majDeg(Polynome *P){
	int i;
	for(i=deg(*P); i>=0; i--){
		if((P->p)[i] != 0){break;}
		(P->deg)--;
	}
}


void randPol(Polynome *P, int deg, int modulo){
	srand(time(NULL));
	int degP = deg;
	unsigned *c = malloc( (degP+1) *sizeof(unsigned));
	int i;
	for(i=0;i<degP; i++){
		unsigned ci = rand()%modulo;
		c[i]= ci;
	}
	unsigned cn = (rand()%(modulo-1))+1;
	c[degP] = cn;
	P->deg = degP;
	P->p = c;
}


void nulPol(Polynome *P){
	unsigned *c = malloc(sizeof(unsigned));
	unsigned c0 = 0;
	c[0]= c0;
	P->deg = 0;
	P->p = c;
}



Polynome somme(Polynome P, Polynome Q, unsigned m){
	int n = deg(P);
	if(deg(Q)>n){n = deg(Q);}
	unsigned *r = calloc(n+1, sizeof(unsigned));
	int i;
	for(i=0; i<=n; i++){
		r[i] = addmod(coef(i,P), coef(i,Q), m);
	}
	Polynome R;
	R.deg = n; R.p = r;
	majDeg(&R);
	return R;
}


Polynome diff(Polynome P, Polynome Q, unsigned m){
	int n = deg(P);
	if(deg(Q)>n){n = deg(Q);}
	unsigned *r = calloc(n+1, sizeof(unsigned));
	int i;
	for(i=0; i<=n; i++){
		r[i] = diffmod(coef(i,P), coef(i,Q), m);
	}
	Polynome R;
	R.deg = n; R.p = r;
	majDeg(&R);
	return R;
}


Polynome mult(Polynome P, Polynome Q, unsigned m){//multiplication dans F2[X]
	int n = deg(P)+deg(Q);
	int i; int j;
	unsigned *r = calloc(n+1, sizeof(unsigned));
	for(i = n; i>0; i--){
		int k = 0;
		for(j=i; j>=0; j--){
			k = addmod(mulmod(coef(j,P),coef(i-j,Q),m), k, m);
		}
		r[i] = k;
	}
	r[0] = mulmod(coef(0,P), coef(0,Q), m);
	Polynome R;
	R.deg = n; R.p = r;
	majDeg(&R);
	return R;
}


/*void div_eucli(Polynome A, Polynome B, Polynome *Q, Polynome *R, unsigned m){
	//int n = abs(deg(A) - deg(B));
	if((deg(B)==0) && ((B.p)[0]==0)){ return;}
	if((deg(B)==0) && ((B.p)[0]==1)){*Q = A; R->deg = 0; return;}
	*R = A;
	nulPol(Q);
	while(deg(*R) >= deg(B)){
		Polynome Diviseur; unsigned *r = calloc((deg(*R) - deg(B))+1,sizeof(unsigned));
		Diviseur.deg = (deg(*R) - deg(B));
		unsigned a = R->p[deg(*R)], b =B.p[deg(B)] ,u,v;
		euclide_etendu(m,diffmod(m,b,m),&u,&v);
		r[Diviseur.deg] = divmod(a,b,m);
		Diviseur.p = r;
		printf("R = ");affiche(*R);
		printf("\nDiviseur = ");affiche(Diviseur);printf("\n\n");
		*R = diff(*R,mult(Diviseur,B,m),m);
		*Q = somme(*Q,Diviseur, m);
	}
	majDeg(Q);
	majDeg(R);
}


Polynome pgcd(unsigned P, unsigned Q){
	if(deg(P)<deg(Q)){return pgcd(Q,P);}
	Polynome r0 = P, r1 = Q;
	while(deg(r1) > 0){
		Polynome t ,a;
		int dt = deg(r0)-deg(r1),da = dt-1;
		unsigned *ct, *ca;
		t.deg = dt; a.deg = da;
		t.p = ct; a.p = ca;
		div_eucli(r0,r1,&a,&t);
		r0 = r1;
		r1 = t;
		majDeg(&r0);
		majDeg(&r1);
		if((deg(t)==0) && ((t.p)[0]==1)){return t;}
	}
	return r0;
}


unsigned eucli_etendu(unsigned P, unsigned Q, unsigned *U, unsigned *V){
  unsigned q, r, s, t, tmp;
  *U = 1;
  *V = 0;
  s = 0;
  t = 1;
  while (Q > 0) {
    div_eucli(P,Q,&q,&r);
    P = Q;
    Q = r;
    tmp = s;
    s = diff(*U,mult(q,s));
    *U = tmp;
    tmp = t;
    t = diff(*V,mult(q,t));
    *V = tmp;
  }
  return P;
}*/


void affiche(Polynome P){
	int i;
	for(i=deg(P); i>=0; i--){
		if((i==0) && (deg(P)==0)){printf("%d ", (P.p)[0]);}
		else if((i==0) && ((P.p)[0]!=0)){printf("+ %d ", (P.p)[0]);}
		else if(i==deg(P)){
			if((P.p)[i]>1){ printf("%d",(P.p)[i]);}
			if((P.p)[i]!=0){printf("X^%d ",i); }
		}
		else{
			if((P.p)[i]!=0){printf("+ ");}
			if((P.p)[i]>1){ printf("%d",(P.p)[i]);}
			if((P.p)[i]!=0){printf("X^%d ",i); }
		}
	}
}


int main(){
	int modulo = 5;
	Polynome P;
	randPol(&P,7, modulo);
	printf("P = ");affiche(P);printf("\n");
	printf("deg(P) = %d\n\n",P.deg);
	
	Polynome Q;
	randPol(&Q,4, modulo);
	printf("Q = ");affiche(Q);printf("\n");
	printf("deg(Q) = %d\n\n",Q.deg);
	
	Polynome R = somme(P,Q,modulo);
	printf("\nP+Q = ");affiche(R);printf("\n");
	printf("deg(P+Q) = %d\n\n",R.deg);
	free(R.p);
	
	Polynome S = mult(P,Q,modulo);
	printf("P.Q = ");affiche(S);printf("\n");
	printf("deg(P.Q) = %d\n",S.deg);
	free(S.p);
	
	free(P.p);
	free(Q.p);
}
