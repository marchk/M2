#include <stdlib.h>
#include <stdio.h>

void mov(int** tab, int lines, int rows, int i, int j, int n, int max, int dir){
	if(n<=max){
		tab[i][j] = n;
		int x = i; int y = j;
		
		switch(dir){
			case 1:
				if( ((j+1)<rows) && (tab[i][j+1]==0) ){
				 	x = i; y = j+1;
				 	mov(tab,lines,rows,x,y,n+1,max,dir);
				 	break;
				 }
				 else{dir++;}
				 
			case 2:
				 if( ((i+1)<lines) && (tab[i+1][j]==0) ){
				 	x = i+1; y = j;
				 	mov(tab,lines,rows,x,y,n+1,max,dir);
				 	break;
				 }
				 else{dir++; }
				 
			case 3:
				 if( ((j-1)<=0) && (tab[i][j-1]==0) ){
				 	x = i; y = j-1;
				 	mov(tab,lines,rows,x,y,n+1,max,dir);
				 	break;
				 }
				 else {dir++;}
				 
			case 4:
				 if( ((i-1)<=0) && (tab[i-1][j]==0) ){
				 	x = i-1; y = j;
				 	mov(tab,lines,rows,x,y,n+1,max,dir);
				 	break;
				 }
				 else{dir++;}
				 
			default:
				 return;
				 break;
		
		}
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
	
	if(max<0){
		fprintf(stderr, "Les arguments doivent etre positifs !\n");
		return -1;
	}
	
	int i,j;
	int **tab = malloc(sizeof(int(*)[lines][rows]));//[lines][rows];
	for(i=0; i<lines; i++){
		tab[i] = malloc(rows*sizeof(int));
		for(j=0;j<rows;j++){
			tab[i][j] = 0;
		}
	}
	mov(tab,lines,rows,0,0,1,max,1);
	if(max>0){
		for(i=0; i<lines; i++){
			for(j=0;j<rows;j++){
				printf("%2d ", tab[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;
}
