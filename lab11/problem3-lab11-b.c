
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define ADD_THREADS 2
#define SUB_THREADS 2
#define MULT_THREADS 2
#define DIV_THREADS 2

sem_t lock;
double V;
int  a,b,c,d;

void *runner_add(void *);
void *runner_sub(void *);
void *runner_mult(void *);
void *runner_div(void *);

int main() {

    printf("Please enter the initial value of the shared variable: \n");
    scanf("%lf",&V);

    printf("Please enter the values for a, b, c and d\n");
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);
    scanf("%d",&d);

    printf("READ: V=%.2f - a=%d - b=%d - c=%d - d=%d \n",V,a,b,c,d);

    sem_init(&lock, 0, 1); 
   

    pthread_t tid1[ADD_THREADS];
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);

    for (int i = 0; i < ADD_THREADS; ++i) {
        pthread_create(&tid1[i], &attr1, runner_add, (void *)(intptr_t)i);
    }

    pthread_t tid2[SUB_THREADS];
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);

    for (int i = 2; i < SUB_THREADS+2; ++i) {
        pthread_create(&tid2[i-2], &attr2, runner_sub, (void *)(intptr_t)i);
    }

    for (int i = 0; i < ADD_THREADS; ++i) {
        pthread_join(tid1[i], NULL);
    }

    for (int i = 0; i < SUB_THREADS; ++i) {
        pthread_join(tid2[i], NULL);
    }

    pthread_t tid3[MULT_THREADS];
    pthread_attr_t attr3;
    pthread_attr_init(&attr3);

    for (int i = 4; i < MULT_THREADS+4; ++i) {
        pthread_create(&tid3[i-4], &attr3, runner_mult, (void *)(intptr_t)i);
    }

    pthread_t tid4[DIV_THREADS];
    pthread_attr_t attr4;
    pthread_attr_init(&attr4);

    for (int i = 6; i < DIV_THREADS+6; ++i) {
        pthread_create(&tid4[i-6], &attr4, runner_div, (void *)(intptr_t)i);
    }


    for (int i = 0; i < MULT_THREADS; ++i) {
        pthread_join(tid3[i], NULL);
    }

    for (int i = 0; i < DIV_THREADS; ++i) {
        pthread_join(tid4[i], NULL);
    }


    printf("The final value of V = %.2f",V);


    return 0;
}

void *runner_mult(void *param) {
  int id = (intptr_t)param;

    for (int i = 0; i < 3; ++i) {
        sem_wait(&lock);
        V = V * d;
        printf("Thread with id %d - multiplying shared variable by %d, V= %.2f\n", id,c, V);
        sem_post(&lock);
    }
    pthread_exit(NULL);
}

void *runner_div(void *param) {
   int id = (intptr_t)param;

    for (int i = 0; i < 3; ++i) {
        sem_wait(&lock);
        V = V / d;
        printf("Thread with id %d - dividing shared variable by %d, V= %.2f\n", id,d, V);
        sem_post(&lock);
    }
    pthread_exit(NULL);
}

void *runner_add(void *param) {
    int id = (intptr_t)param;

    for (int i = 0; i < 3; ++i) {
        sem_wait(&lock);
        V = V + a;
        printf("Thread with id %d - adding shared variable by %d , V= %.2f\n", id,a, V);
        sem_post(&lock);
    }
    pthread_exit(NULL);
}

void *runner_sub(void *param) {
    int id = (intptr_t)param;

    for (int i = 0; i < 3; ++i) {
        sem_wait(&lock);
        V = V - b;
        printf("Thread with id %d - subtracting shared variable by %d, V= %.2f\n", id,b, V);
        sem_post(&lock);
    }
    pthread_exit(NULL);
}
