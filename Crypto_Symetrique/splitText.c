#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	if(argc==3){
		int n = atoi(argv[2]);
	    FILE* fichier = fopen(argv[1], "r");
	    FILE** tab_split = malloc(n*sizeof(FILE*));
	    if(fichier != NULL){
			
			int i;
			for(i=0; i<n; i++){
				char* filename = malloc(100*sizeof(char));
				sprintf(filename,"%s", argv[1]);
				char* splitname = ".split";
				sprintf(splitname, "%d",(i+1));
				filename = strcat(filename, splitname);
				tab_split[i] = fopen(filename, "a");
			}
	    
	    
	    	int car = 0;
	    	int file_number = 0;
	    	do{
	    		car = fgetc(fichier);
	    		if( (car>=97) && (car<=122) ){
	    			fputc(car, tab_split[file_number]);
	    			file_number = ((file_number + 1)%n);
	    		}
	    	}while(car != EOF);
	    	
	    	for(i=0; i<n; i++){
	    		fclose(tab_split[i]);
	    	}
	    	fclose(fichier);
	    	
	    }
	}
}
