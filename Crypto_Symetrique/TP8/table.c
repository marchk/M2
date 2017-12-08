#include "heys.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


sbox_t sbox2 = {0xe, 0x4, 0xd, 0x1, 0x2, 0xf, 0xb, 0x8,
	       0x3, 0xa, 0x6, 0xc, 0x5, 0x9, 0x0, 0x7};


//----EXERCICE 1----
int** table(sbox_t sb){
	int** tab = calloc(16,sizeof(int*));
	int i;
	for(i=0; i<16; i++){tab[i] = calloc(16,sizeof(int));}
	block_t x1, x2;
	for(x1=0; x1<16; x1++){
		for(x2=0; x2<16; x2++){
			block_t difx = x1^x2;
			block_t y1 = heys_subst(x1, sb), y2 = heys_subst(x2, sb);
			block_t dify = y1^y2;
			tab[difx][dify]++;
		}
	}
	return tab;
}

void aff(int** tab){
	int i=0,j=0;
	printf("    ");
	for(i=0;i<16; i++){printf(" %4x  ",i);}
	printf("\n    ");
	for(i=0;i<16; i++){printf("-------");}
	printf("\n");
	for(i=0;i<16; i++){
		printf("%2x |",i);
		for(j=0;j<16; j++){
			printf(" %4d  ",tab[i][j]);
		}
		printf("\n");
	}
}




/*
----EXERCICE 2----
	De = [0000 1011 0000 0000] = 0x0b00
	Ds = [0000 0110 0000 0110] = 0x0606
	

----EXERCICE 3----
	p = (8/16) x (6/16) x (6/16) x (6/16) = 0,026367187 = 2.6%
	    p(S12)   p(S23)   p(S32)   p(S33)
*/




//----EXERCICE 4----
void rand_block(block_t diff, int n){
	int i = 0;
	block_t b1 = 0,b2 = 0;
	int fd = open("rand_bytes", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
	
	if(fd<0){return;}
	while(i<n){
		int fp = open("/dev/urandom", O_RDONLY);
		if(fp>0){
			int r1 = read(fp,&b1, 2);
			if(r1>0){
				b2 = b1^diff;
				int r2 = write(fd,&b1,2);
				int r3 = write(fd,&b2,2);
				if(r2>0 && r3>0){i++;}
			}
			close(fp);
		}	
	}
	close(fd);
}



//----EXERCICE 5----
void cle_part(){	
	double p = 2.6/100;
	printf("On veut pour une certaine clé k que p(k) = %3f Soit environ 130 couples\n", p);
	byte_t k1 = 0, k2 = 0;
	int fd = open("chiffre", O_RDWR, S_IRUSR|S_IWUSR|S_IXUSR);
	if(fd<0){
		fprintf(stderr, "Impossible d'ouvrir le fichier\n");
		return;
	}
	
	for(k1=0; k1<=0xf; k1++){
		for(k2=0; k2<=0xf; k2++){
			//Création de clé
			rkey_t k = (k1<<8)^(k2);
			//Recherche des couples dans le fichier
			int i, nb = 0;
			for(i=0; i<5000; i++){
				block_t c1 = 0, c2 = 0,c3=0,c4=0;
				int r1 = read(fd,&c1,2);
				int r2 = read(fd,&c2,2);
				if(r1>0 && r2>0){
					c3 = heys_subst(c1^k, isbox);
					c4 = heys_subst(c2^k, isbox);
					block_t d = c3^c4;
					if(d==0x606){nb++;}
				}
				else{ fprintf(stderr, "Impossible de lire le fichier pour la clé k=%3x\n", k);	break; }
			}
			//Test de fréqunence d'apparition
			if(nb>100){ printf("k = %3x --- nb = %3d\n",k,nb); }
			lseek(fd,0,SEEK_SET);
		}
	}
	close(fd);
}


//----EXERCICE 5----
ckey_t brute_force(rkey_t k){
	ckey_t b1,b2;
	ckey_t ck = k;
	int fd = open("chiffre", O_RDWR, S_IRUSR|S_IWUSR|S_IXUSR);
	int fp = open("rand_bytes", O_RDWR, S_IRUSR|S_IWUSR|S_IXUSR);
	if(fd<0 || fp<0){
		fprintf(stderr, "Impossible d'ouvrir les fichiers\n");
		return 0;
	}
	for(b1=0x8637a4393d; b1>0; b1--){
		for(b2=0; b2<=0xf; b2++){	
			ck = (b1<<12)^(k)^(b2<<4);
			int i; int egal = 1;
			lseek(fd,0,SEEK_SET);
			lseek(fp,0,SEEK_SET);
			for(i=0; i<20; i++){
				block_t c1 = 0, c2 = 0;
				int r1 = read(fd,&c1, 2);
				int r2 = read(fp,&c2, 2);
				if(r1>0&&r2>0){
					block_t c3 = heys_encrypt(c2, ck);
					egal &= (c3==c1);
					if(egal==0){printf("k = %10lx --- > NOPE\n",ck);i=0;break;}
				}
			}
			if(egal==1){return ck;}
		}
	}
		return 0;
	}




int main(int argc, char** argv){
	int f = atoi(argv[1]);
	if(f==0){
		int** t = table(sbox2);
		aff(t);
	}
	else if(f==1){ rand_block(0x0b00,5000); }
	else if(f==2){ cle_part(); }
	else if(f==3){
		ckey_t k = brute_force(0x90d);
		printf("la clé finale vaut %10lx\n", k);
	}	
	return 0;
}
