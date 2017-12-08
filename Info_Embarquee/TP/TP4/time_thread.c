#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>

sem_t mutex;

void* thread(){
        sem_wait(&mutex);
        sem_post(&mutex);
        return NULL;
}

void *rien(){return NULL;}

void tmps_thread1(){
	pthread_t thread1;
	struct timeval temps_avant, temps_apres;
    gettimeofday (&temps_avant, NULL);
    
    pthread_create(&thread1, NULL, &rien, NULL);
    pthread_join(thread1, NULL);
    
    gettimeofday (&temps_apres, NULL);
    printf("Temps en µs pour 1 thread : %ld µs\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
}


void tmps_thread2(){
	pthread_t thread1, thread2;
	struct timeval temps_avant, temps_apres;
    gettimeofday (&temps_avant, NULL);
    
    pthread_create(&thread1, NULL, &thread, NULL);
    pthread_create(&thread2, NULL, &thread, NULL);
    sem_wait(&mutex);
    gettimeofday (&temps_apres, NULL);
    printf("Temps en µs pour 2 threads en ordonnancecment explicite : %ld µs\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
    sem_post(&mutex);
}



int main(int argc, char** argv){
	int n = atoi(argv[1]);
	if(n==1){tmps_thread1();}
	else if(n==1){tmps_thread2();}
}
