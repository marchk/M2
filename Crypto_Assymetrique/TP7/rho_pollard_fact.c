#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void F(mpz_t xi, mpz_t n){
	mpz_mul(xi, xi,xi);
	mpz_add_ui(xi,xi,1);
	mpz_cdiv_r(xi,xi,n);
}




int rho_pollard_fact(mpz_t n, mpz_t *a, mpz_t *b){ //On cherche à trouver n = ab
	mpz_t i, xi, h, j, xj, d, diffx,un, deux;
	mpz_inits(*b, xi, j, xj,d, diffx,un,deux);
	mpz_set_ui(un,1);
	mpz_set_ui(deux,2);
	mpz_set_ui(i,1);
	mpz_set_ui(h,0);
	do{
	mpz_mul_2exp (j, un, i);
	mpz_add_ui(j,j,1);
	
	mpz_sub(diffx, xi, xj);
	mpz_gcd(d, diffx, n);
	if(mpz_cmp(d,un) != 0){
		mpz_init_set(*a,d);
		mpz_cdiv_q(*b, n, *a);
		mpz_clears(i, xi, h, j, xj, d, diffx,un,deux);
		return 1;	
	}
	F(xi,n);
	//if 2^h = k : h++
	if(
	mpz_add_ui(i,i,1);
	}while(mpz_cmp(i,n) != 0);
	mpz_clears(i, xi, h, j, xj, d, diffx,un,deux,*a,*b);
	return 0;
}

int main(int argc, char** argv){
	mpz_t n1, n2;
	mpz_inits(n1,n2);
	mpz_init_set_ui(n1,52590354472497239257283147);
	mpz_init_set_ui(n2,52590354464570687296135717939981);
	
	return 0;
}
