
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

void * runner(void *);
void get_fork(int);
void put_fork(int);

int num_of_philo;
sem_t *semaphores;

int main(int argc, char **argv){

	if (argc < 2) {
	printf("ERROR!");
	exit(1);     
	}
	num_of_philo = atoi(argv[1]);
	semaphores = (sem_t*) malloc(num_of_philo * sizeof(sem_t));

	pthread_t tid[num_of_philo];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i = 0;i<num_of_philo;++i){

		pthread_create(&tid[i], &attr, runner , &i);
		sem_init(&semaphores[i],0,1);
	}
	
	for(int i = 0;i<num_of_philo;++i){
		pthread_join(tid[i],NULL);
	}

	return 0;
}

void * runner(void *param){
	int id = *((int*) param);

	while(1){
		//thinking ...
		get_fork(id);
		//eating ...
		put_fork(id);

	}

}
void get_fork(int a){
	if(a%2==0){
		sem_wait(&semaphores[(a+1)%num_of_philo]);  //right
		sem_wait(&semaphores[a]);
	}
	else{
		sem_wait(&semaphores[a]);
		sem_wait(&semaphores[(a+1)%num_of_philo]);
	}
}

void put_fork(int a){
	sem_post(&semaphores[a]);
	sem_post(&semaphores[(a+1)%num_of_philo]);
}
