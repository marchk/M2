#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	if(argc==3){
		int n = atoi(argv[2]);
		
		//-----Ouverture du fichier à séparer-----
	    FILE* fichier = fopen(argv[1], "r");
	    FILE* tab_split = malloc(sizeof(FILE*));
	    char* filename = malloc(100*sizeof(char));
		sprintf(filename,"%s", argv[1]);
		char* splitname = malloc(10*sizeof(char));
		sprintf(splitname, ".split%d",n);
		filename = strcat(filename, splitname);
		tab_split = fopen(filename, "w");
	    
	    if(fichier != NULL){
				    
	    	//-----Ecriture dans le fichier-----
	    	int car = 0;
	    	int file_number = 0;
	    	do{
	    		car = fgetc(fichier);
	    		if( file_number==0 ){
	    			fputc(car, tab_split);
	    		}
	    		file_number = ((file_number + 1)%n);
	    	}while(car != EOF);
	    	
	    	//-----Fermeture des fichiers et lbération de la mémoire-----
    		fclose(tab_split);
	    	fclose(fichier);
	    }
	}
}
