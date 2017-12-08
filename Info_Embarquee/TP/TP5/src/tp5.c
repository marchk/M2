#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>


pthread_mutex_t mutex, mutex2;
pthread_cond_t condition, condition2;
pthread_t A, B, C;


void* fa(){
	printf("Thread A commencée\n");
	pthread_cond_wait(&condition, &mutex);
	printf("Thread A finie\n");
	pthread_exit(NULL);
}


void* fb(){
	printf("Thread B commencée\n");
	pthread_cond_wait(&condition2, &mutex2);
	pthread_setschedprio(A, 2);
	pthread_setschedprio(B,1);
	pthread_setschedprio(C, 0);
	printf("Thread B finie\n");
	pthread_exit(NULL);
}


void* fc(){
	printf("Thread C commencée\n");
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex2);
	pthread_cond_signal(&condition2);
	pthread_yield();
	pthread_mutex_unlock(&mutex2);
	pthread_mutex_unlock(&mutex);
	printf("Thread C finie\n");
	pthread_exit(NULL);
}


int main(){
	pthread_attr_t attr;
	
	struct sched_param param = {.sched_priority = 0 };
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setschedparam(&attr, &param);
	
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex2, NULL);
	
	pthread_cond_init(&condition, NULL);
	pthread_cond_init(&condition2, NULL);

	pthread_create(&A, &attr, &fa, NULL);
	pthread_create(&B, &attr, &fb, NULL);
	pthread_create(&C, &attr, &fc, NULL);
	
	pthread_join(A, NULL);
	pthread_join(B, NULL);
	pthread_join(C, NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condition);
	pthread_attr_destroy(&attr);
}
