
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 10


typedef struct item{
    int id;
}ITEM;

typedef struct counter{
    int in;
    int out;
}COUNTER;

void produce(COUNTER *, ITEM *);
void consume(COUNTER *, ITEM *);
void cleanup(COUNTER *, ITEM *);


int main(){

    COUNTER* C = (COUNTER*) mmap(NULL,sizeof(COUNTER), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    C->in=0;
    C->out=0;

    ITEM* M = (ITEM*) mmap(NULL,sizeof(ITEM)*BUFFER_SIZE, PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t child = fork();


    if(child<0){
        printf("ERROR");
        return 1;
    }
    else if(child == 0){
        consume(C,M);
    }
    else{
        produce(C,M);
    }

    cleanup(C,M);

    return 0;

}

void produce(COUNTER *C, ITEM *M){

    int first_id = 2023001;

    while(1){  

        while((C->in+1)%BUFFER_SIZE == C->out);

        M[C->in].id = first_id;
        printf("Produced item: %d\n",M[C->in].id);
        first_id++;


        C->in = (C->in+1)%BUFFER_SIZE;
    }

}

void consume(COUNTER *C, ITEM *M){

    while(1){  

        while(C->in == C->out);

        ITEM next_consumed = M[C->out];
        printf("Consumed item: %d\n",next_consumed.id);

        C->out = (C->out+1)%BUFFER_SIZE;
    }

}

void cleanup(COUNTER *C, ITEM * M){
    munmap(M,sizeof(ITEM)*BUFFER_SIZE);
    munmap(C,sizeof(COUNTER));
}
