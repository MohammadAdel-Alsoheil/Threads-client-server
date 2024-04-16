#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000

typedef struct {
    int thread_id;
    int* array;
    int start;
    int end;
} ThreadArgs;

void *runner(void *arg);
bool isPrime(int a);

int main() {
    int array[ARRAY_SIZE];

    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 101;
    }

    printf("Initial Array:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i < NUM_THREADS; ++i) {
        ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs));

        args->thread_id = i;
        args->array = array;
        args->start = i * (ARRAY_SIZE / NUM_THREADS);
        args->end = (i + 1) * (ARRAY_SIZE / NUM_THREADS);

        pthread_create(&threads[i], &attr, runner, (void *)args);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("After all threads finished:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

bool isPrime(int a) {
    if (a <= 1) {
        return false;
    }

    bool flag = true;

    for (int i = 2; i * i <= a; ++i) {
        if (a % i == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}

void *runner(void* arg) {
    ThreadArgs *A = (ThreadArgs *)arg;

    int ID = A->thread_id;
    int start = A->start;
    int end = A->end;

    printf("This is thread of ID: %d, with start = %d and end = %d\n", ID, start, end);

    int *array = A->array;

    for (int i = start; i < end; ++i) {
        if (isPrime(array[i])) {
            array[i] = 0;
        }
    }

    free(arg);
    pthread_exit(0);
}
