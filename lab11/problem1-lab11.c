#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t lock;

void * runner(void *);

int main(){

    sem_init(&lock, 0, 0);

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, runner, NULL);
    
    sem_wait(&lock);
	    
    return 0;
}

void * runner(void * param){

    printf("Thread is running!\n");
    sem_post(&lock);

    pthread_exit(0);
}
