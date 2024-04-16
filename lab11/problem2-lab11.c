
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define MULT_THREADS 2
#define DIV_THREADS 2

sem_t lock;
double shared = 1.0; 

void *runner_mult(void *);
void *runner_div(void *);

int main() {
    printf("please enter the initial value of the shared variable: \n");
    scanf("%f",&shared);
    sem_init(&lock, 0, 1); 

    pthread_t tid1[MULT_THREADS];
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);

    for (int i = 0; i < MULT_THREADS; ++i) {
        pthread_create(&tid1[i], &attr1, runner_mult, (void *)(intptr_t)i);
    }

    pthread_t tid2[DIV_THREADS];
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);

    for (int i = 2; i < DIV_THREADS+2; ++i) {
        pthread_create(&tid2[i-2], &attr2, runner_div, (void *)(intptr_t)i);
    }

    for (int i = 0; i < MULT_THREADS; ++i) {
        pthread_join(tid1[i], NULL);
    }

    for (int i = 0; i < DIV_THREADS; ++i) {
        pthread_join(tid2[i], NULL);
    }

    printf("%.2f\n", shared);

    return 0;
}

void *runner_mult(void *param) {
    int id = (intptr_t)param;

    for (int i = 0; i < 5; ++i) {
        sem_wait(&lock);
        shared = shared * 2;
        printf("Thread with id %d - Multiplying shared variable by 2, curVal:  %.2f\n", id, shared);
        sem_post(&lock);
    }
    pthread_exit(NULL);
}

void *runner_div(void *param) {
    int id = (intptr_t)param;

    for (int i = 0; i < 5; ++i) {
        sem_wait(&lock);
        shared = shared / 2;
        printf("Thread with id %d - Dividing shared variable by 2, curVal:  %.2f\n", id, shared);
        sem_post(&lock);
    }
    pthread_exit(NULL);
}
