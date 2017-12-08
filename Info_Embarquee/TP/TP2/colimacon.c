#include "colimacon.h"


void fillR(int** tab, int cols, int* i,  int* j, int* val, int max){
	while( ((*val)<=max) && ((*j)<cols) ){
		if(tab[*i][*j] != 0){ (*j) -= 1; return;}
		tab[*i][*j] = *val;
		*val += 1;
		*j += 1;
	}
	if((*j)<=cols){ 
		*j -= 1;
	}
}



void fillD(int** tab, int rows, int* i,  int* j, int* val, int max){
	while( ((*val)<=max) && ((*i)<rows) ){
		if(tab[*i][*j] != 0){ (*i) -= 1; return;}
		tab[*i][*j] = *val;
		*val += 1;
		*i += 1;
	}
	if((*i)<=rows){ 
		*i -= 1;
	}
}



void fillL(int** tab, int cols, int* i,  int* j, int* val, int max){
	while( ((*val)<=max) && ((*j)>=0) ){
		if(tab[*i][*j] != 0){ (*j) += 1; return;}
		tab[*i][*j] = *val;
		*val += 1;
		*j -= 1;
	}
	if((*j)<0){ 
		*j = 0;
	}
}



void fillU(int** tab, int rows, int* i,  int* j, int* val, int max){
	while( ((*val)<=max) && ((*i)>=0) ){
		if(tab[*i][*j] != 0){ (*i) += 1; return;}
		tab[*i][*j] = *val;
		*val += 1;
		*i -= 1;
	}
	if((*i)<0){ 
		*i = 0;
	}
}




void affiche(int** tab, int rows, int cols){
	int i; int j;
	for(i=0; i<rows; i++){
			for(j=0;j<cols;j++){
				printf("%2d ", tab[i][j]);
			}
			putchar('\n');
	}
}


void free_tab(int** tab, int rows){
	int i;
	for(i = 0; i<rows; i++){ free(tab[i]);}
	free(tab);
}




void colimacon(int **tab, int rows, int cols){
	clock_t time_start = clock();
	if(cols*rows <= 0){return;}
	int i,j;
	tab = calloc(rows,sizeof(int*));
	for(i=0; i<rows; i++){
		tab[i] = calloc(cols,sizeof(int));
	}
	int max = cols*rows;
	int val = 1;
	i=0;j=0;
	while(val<=max){
		fillR(tab, cols, &i,  &j, &val ,max);
		i++;
		fillD(tab, rows, &i,  &j, &val, max);
		j--;
		fillL(tab, cols, &i,  &j, &val, max);
		i--;
		fillU(tab, rows, &i,  &j, &val ,max);
		j++;
	}
	clock_t time_end = clock();
	double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
	
	affiche(tab, rows, cols);
	printf("---Time spent : %lf seconds---\n", time_spent);
	free_tab(tab,rows);
	
}

	
	
void testcoli(int **tab, int n){
	srand(time(NULL));
	int i;
	int rows;
	int cols;
	for(i=0; i<n; i++){
		rows = rand()%31;
		cols = rand()%31;
		printf("%d rows and %d columns :\n", rows, cols);
		colimacon(tab, rows, cols);
		printf("\n\n");
	}
}


	



int main(int argc, char** argv){
	int** tab = NULL;
	if(argc==1){//pas d'arguments
		printf("\nTest sur 10 valeurs...\n");
		testcoli(tab,10);
		free(tab);
		return 0;
	}
	
	if((argc <3) || (argc>3)){
		fprintf(stderr, "Le nombre d'arguments est incorrect !\n(%d argument(s) au lieu de 3 ou 0)\n",argc-1);
		return -1;
	}
	
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int m = rows*cols;
	if(m<0){
		fprintf(stderr, "Les arguments doivent etre positifs !\n");
		return -1;
	}
	if(m == 0){return 0;}
	
	colimacon(tab, rows, cols);

	return 0;
}
