#include <stdlib.h>
#include <stdio.h>

void fillR(int** tab, int rows, int* i,  int* j, int* val, int max){
	while((*val)<=max){
		tab[*i][*j] = *val;
		if( (((*j)+1)<rows ) && tab[*i][(*j)+1] == 0){
			*j = (*j)+1; *val = (*val)+1;
		}
		else{break;}
	}
}

void fillL(int** tab, int rows, int* i,  int* j, int* val ,int max){
	while((*val)<=max){
		tab[*i][*j] = *val;
		if( (((*j)-1)>=0 ) && tab[*i][(*j)-1] == 0){
			*j = (*j)-1; *val = (*val)+1;
		}
		else{break;}
	}
}


void fillD(int** tab, int lines, int* i,  int* j, int* val ,int max){
	while((*val)<=max){
		tab[*i][*j] = *val;
		if( (((*i)+1)<lines ) && tab[(*i)+1][(*j)] == 0){
			*i = (*i)+1; *val = (*val)+1;
		}
		else{break;}
	}
}


void fillU(int** tab, int lines, int* i,  int* j, int* val ,int max){
	while((*val)<=max){
		tab[*i][*j] = *val;
		if( (((*i)-1)>=0 ) && tab[(*i)-1][(*j)] == 0){
			*i = (*i)-1; *val = (*val)+1;
		}
		else{break;}
	}
}




int main(int argc, char** argv){
	if(argc <3){
		fprintf(stderr, "Le nombre d'arguments est incorrect !\n%d\n",argc);
		return -1;
	}
	
	int lines = atoi(argv[1]);
	int rows = atoi(argv[2]);
	int max = lines*rows;
	int val = 1;
	
	if(max<0){
		fprintf(stderr, "Les arguments doivent etre positifs !\n");
		return -1;
	}
	if(max == 0){return 0;}
	
	int i,j;
	int **tab = malloc(sizeof(int(*)[lines][rows]));
	for(i=0; i<lines; i++){
		tab[i] = malloc(rows*sizeof(int));
		for(j=0;j<rows;j++){
			tab[i][j] = 0;
		}
	}
	
	i=0;j=0;
	while(val<max){
		fillR(tab, rows, &i,  &j, &val ,max);
		fillD(tab, lines, &i,  &j, &val, max);
		fillL(tab, rows, &i,  &j, &val, max);
		fillU(tab, lines, &i,  &j, &val ,max);
	}
	
	
	for(i=0; i<lines; i++){
			for(j=0;j<rows;j++){
				printf("%2d ", tab[i][j]);
			}
			putchar('\n');
	}
	return 0;
}
