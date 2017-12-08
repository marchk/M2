#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>

sem_t mutex;

void* thread(){
        sem_wait(&mutex);
        //sched_yield();
        sem_post(&mutex);
    }
} 


int main(){

	struct timeval temps_avant, temps_apres;
    gettimeofday (&temps_avant, NULL);
   	gettimeofday (&temps_apres, NULL);
   	printf("Temps en µs pour 1 fork : %ld µs\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
}
