#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void process(){
struct timeval temps_avant, temps_apres;
    gettimeofday (&temps_avant, NULL);
    
    pid_t id = fork();
    
    if(id==0){}
    
    else{
    	wait(NULL);
    	gettimeofday (&temps_apres, NULL);
    	printf("Temps en µs pour 1 fork : %ld us\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
    }
}

void process2(){
	struct timeval temps_avant, temps_apres;
    gettimeofday (&temps_avant, NULL);
    
 	int tube[3];
	pipe(tube);
    pid_t id = fork(), id2 = fork();;
    
    if(id==0){}
    else if(id2==0){}
    
    else{
    	wait(NULL);
    	gettimeofday (&temps_apres, NULL);
    	printf("Temps en µs pour 2 fork en ordonnancement explicite : %ld us\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
    }
}


int main(int argc, char** argv){
	int n = atoi(argv[1]);
	if(n==1){process();}
	else if(n==2){process2();}
}
