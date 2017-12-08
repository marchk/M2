#include "f2_poly.h"

int main(){

	f2_poly_t polAES = 0x11b;     //X^8+X^4+X^3+X+1, irréductible non primitif
	f2_poly_t polA51a = 0xe4001;  //X^19+X^18+X^17+X^14+1, irréductible primitif
	f2_poly_t polA51b = 0x600001; //X^22+X^21+1, irréductible primitif
	f2_poly_t polA51c = 0xe00101; //X^23+X^22+X^21+X^8+1, irréductible primitif
	
	//----Test degré----
	printf("-----Test degré------\n");
	f2_deg_t degpolAES = f2_poly_deg(polAES);
	printf("deg(polAES) = %d\n\n", degpolAES);
	printf("\n-------------------------------\n\n");
	
	//----Test print----
	printf("-----Test print------\n");
	printf(" P = polAES\n");
	f2_poly_print(polAES, 'P', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test division----
	printf("-----Test division------\n");
	f2_poly_t A; 
	f2_poly_t B;
	f2_poly_div(&A, &B, polA51c, polAES);
	printf("polA51c = polAES x A + B ou\n");
	f2_poly_print(A, 'A', stdout);
	f2_poly_print(B, 'B', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test modulo----
	printf("-----Test modulo------\n");
	f2_poly_t rest = f2_poly_rem(polA51a,polAES);//Normalement égal à B initialisé précédemment
	printf(" C = polA51a mod polAES\n");
	f2_poly_print(rest, 'C', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test gcd----
	printf("-----Test gcd------\n");
	f2_poly_t GCD = f2_poly_gcd(polA51a, polA51b);
	printf(" G = gcd(polA51a,polA51b)\n");
	f2_poly_print(GCD, 'G', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test x times----
	printf("-----Test xtimes------\n");
	f2_poly_t times = f2_poly_xtimes(polA51b, polA51a);
	printf(" T = X x polA51b mod polA51a\n");
	f2_poly_print(times, 'T', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test times----
	printf("-----Test times------\n");
	f2_poly_t times2 = f2_poly_times(polA51a,polA51b, polA51c);
	printf(" U = polA51a x polA51b mod polA51c\n");
	f2_poly_print(times2, 'U', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test x^{2^n}----
	printf("-----Test x^{2^n}------\n");
	f2_poly_t X2n = f2_poly_x2n(4, POLMAX);
	printf(" X = x^{2^4}\n");
	f2_poly_print(X2n, 'X', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test parity----
	printf("-----Test parity------\n");
	f2_poly_t parite = f2_poly_parity(polAES);
	printf(" Y = parite(polAES)\n");
	f2_poly_print(parite, 'Y', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test reciproque----
	printf("-----Test reciproque------\n");
	f2_poly_t RecipolAES = f2_poly_recip(polAES);
	printf(" R = reciproque(polAES)\n");
	f2_poly_print(RecipolAES, 'R', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	
	//----Test irreductible----
	printf("-----Test irreductible------\n");
	int ir = f2_poly_irred(polAES);
	printf("polAES irreductible ? %d\n", ir);//Doit renvoyer 1
	f2_poly_t n = 7;//= X²+X+1
	f2_poly_print(n, 'N', stdout);
	ir = f2_poly_irred(n);
	printf("N irréductible ? %d\n\n", ir);//Doit renvoyer 1
	f2_poly_t n2 = 6;//= X²+X+1
	f2_poly_print(n2, 'M', stdout);
	ir = f2_poly_irred(n2);
	printf("M irréductible ? %d\n\n", ir);//Doit renvoyer 0
	printf("\n-------------------------------\n\n");
	
	
	//----Test x^{n}----
	printf("-----Test x^n------\n");
	f2_poly_t r2 = f2_poly_xn(33, POLMAX);
	printf(" Z = X^33\n");
	f2_poly_print(r2, 'Z', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");

	
	//----Test primitive----
	printf("-----Test primitive------\n");
	int pri = f2_poly_primitive(polAES);
	printf("polAES primitif ? %d\n", pri);//Doit renvoyer 0
	pri = f2_poly_primitive(polA51a);
	printf("polA51a primitif ? %d\n", pri);//Doit renvoyer 1
	printf("\n-------------------------------\n\n");
	
	/*
	//----Test irred order----
	printf("-----Test irred order------\n");
	int ord = f2_poly_irred_order(6);
	printf("ordre polAES =  %d\n2^n = %d\n", ord, (1<<f2_poly_deg(polA51a)));
	printf("\n-------------------------------\n\n");
	*/
	
	
	//----Test random inf----
	printf("-----Test random inf------\n");
	f2_poly_t randinf = f2_poly_random_inf(5);
	printf(" F polynome aleatoire de degre < 5\n");
	f2_poly_print(randinf, 'F', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test random----
	printf("-----Test random------\n");
	f2_poly_t randi = f2_poly_random(5);
	printf(" I polynome aleatoire de degre = 5\n");
	f2_poly_print(randi, 'I', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	
	//----Test irred random----
	f2_poly_t irrandom = f2_poly_irred_random(4);
	f2_poly_print(irrandom, 'G', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	

	//----Test primitive random----
	f2_poly_t primandom = f2_poly_primitive_random(4);
	f2_poly_print(primandom, 'G', stdout);
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	
	//----Test irred count----
	printf("-----Test irred count------\n");
	uint8_t i;
	for(i=1; i<=20; i++){
		printf("%d irreductibles de degre %d\n", f2_poly_irred_count(i),i);
	}
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	//----Test primitive count----
	printf("-----Test primitive count------\n");
	for(i=1; i<=20; i++){
		printf("%d primitifs de degre %d\n", f2_poly_primitive_count(i),i);
	}
	printf("\n");
	printf("\n-------------------------------\n\n");
	
	
	return 0;
}
