#include <stdio.h>
#include <stdlib.h>


unsigned coef(int i, unsigned P){ return ((P>>i)&1); }//retourne le i-eme coefficient du polynome P


int deg(unsigned P){//determine le degré de P
	int i = 0;
	unsigned Q = P>>1;
	while(Q != 0){
		i++;
		Q >>=1;
	}
	return i;
}


void affiche(unsigned P){
	int d = deg(P); int i;
	int c = P&1;
	printf("%d ",c);
	for(i = 0; i<=d; i++){
		int c = P&1;
		if((c==1) && (i==1)){ printf("+ X");}
		if((c==1) && (i>1)){ printf("+ X^%d ",i);}
		P >>=1;
	}
}


unsigned somme(unsigned P, unsigned Q){ return P^Q; }//Somme de P et Q dans F2


unsigned diff(unsigned P, unsigned Q){ return P^Q; }


unsigned mult(unsigned P, unsigned Q){//multiplication dans F2[X]
	int n = deg(P) + deg(Q);
	int i; int j;
	unsigned R = 0;
	for(i = n; i>0; i--){
		int k = 0;
		for(j=i; j>=0; j--){
			k ^= (coef(j,P)&coef(i-j,Q));
		}
		R ^= k; R <<=1;
	}
	return R^(coef(0,P)&coef(0,Q));
}


void div_eucli(unsigned A, unsigned B, unsigned *Q, unsigned *R){ // division euclidienne
	if(B==0){ *Q = -1; *R = 0; return;}
	if(B==1){*Q = A; *R = 0; return;}
	*R = A; unsigned Diviseur;
	*R = A; *Q = 0;
	while(deg(*R) >= deg(B)){
		Diviseur = 1<<(deg(*R) - deg(B));
		*R = diff(*R,mult(Diviseur,B));
		*Q = somme(*Q,Diviseur);
	}
}


unsigned pgcd(unsigned P, unsigned Q){
	if(deg(P)<deg(Q)){return pgcd(Q,P);}
	unsigned r0 = P, r1 = Q;
	while(r1 > 0){
		unsigned t = 0, a = 0;
		div_eucli(r0,r1,&a,&t);
		r0 = r1;
		r1 = t;
		if(t==1){return 1;}
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
}


unsigned modulo(unsigned P, unsigned N){
	unsigned R; unsigned Q;
	div_eucli(P, N, &Q,&R);
	return R;
}


unsigned addmod(unsigned P, unsigned Q, unsigned N){
	unsigned R; unsigned S;
	div_eucli(somme(P,Q), N, &S,&R);
	return R;
}

unsigned diffmod(unsigned P, unsigned Q, unsigned N){
	unsigned R; unsigned S;
	div_eucli(diff(P,Q), N, &S,&R);
	return R;
}

unsigned multmod(unsigned P, unsigned Q, unsigned N){
	unsigned P2 = modulo(P,N);
	unsigned Q2 = modulo(Q,N);
	unsigned R; unsigned S;
	div_eucli(mult(P2,Q2), N, &S,&R);
	return R;
}


unsigned inverse(unsigned P, unsigned N){
	unsigned U,V;
	eucli_etendu(P,N,&U,&V);
	return modulo(U,N);
}

unsigned divmod(unsigned P, unsigned Q, unsigned N){
	return multmod(P,inverse(Q,N),N);
}


int main(){
	unsigned int P = 0xc9;// 1 + X³ + X⁶ + X⁷
	printf("P = ");affiche(P);printf("\n");
	printf("deg(P) = %d\n\n", deg(P));
	
	unsigned int Q = 0x901;// 1 + x⁸ +x¹¹
	printf("Q = ");affiche(Q);printf("\n");
	printf("deg(Q) = %d\n\n", deg(Q));
	
	unsigned R = somme(P,Q);
	printf("P+Q = ");affiche(R);printf("\n");
	
	unsigned S = mult(Q,P);
	printf("Q.P = ");affiche(S);printf("\n");
	
	unsigned A,B;
	div_eucli(Q,P,&A,&B);
	printf("Q/P = A.P+B ou\n");
	printf("A = ");affiche(A);printf("\n");
	printf("B = ");affiche(B);printf("\n");
	
	unsigned GCD = pgcd(P,S);
	printf("pgcd(P,P.Q) = ");affiche(GCD);printf("\n");
	
	unsigned U,V;
	unsigned GCD2 = eucli_etendu(P,Q,&U,&V);
	printf("( ");affiche(P);printf(") (");affiche(U); printf(") + ( ");affiche(Q);printf(") (");affiche(V);printf(") = ");affiche(GCD2);printf("\n\n");
	
}
	
